/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
*
* Based on Phonon multimedia library
* Copyright (C) 2011 Harald Sitter <sitter@kde.org>
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>

#include "qextVLCVideoFrame.h"
#include "qextQmlVLCGLSLPainter.h"

QEXTQmlVLCGLSLPainter::QEXTQmlVLCGLSLPainter()
    : m_program(0) { }

QEXTQmlVLCGLSLPainter::~QEXTQmlVLCGLSLPainter()
{
    if (m_program && QOpenGLContext::currentContext()) {
        m_program->removeAllShaders();
        m_program->deleteLater();
    }
}

void QEXTQmlVLCGLSLPainter::init()
{
    m_context = const_cast<QOpenGLContext *>(QOpenGLContext::currentContext());
    Q_ASSERT(m_context);

    m_gl = m_context->functions();
#if QT_VERSION < 0x050300
    #if defined(QT_OPENGL_ES_2)
        m_glF = _context->versionFunctions<QOpenGLFunctions_ES2>();
    #else
        m_glF = _context->versionFunctions<QOpenGLFunctions_1_1>();
    #endif
        Q_ASSERT(m_glF);

        m_glF->initializeOpenGLFunctions();
#else
    m_glF = m_gl;
#endif

    if (!m_program)
        m_program = new QOpenGLShaderProgram();

    const char *vertexProgram =
            "attribute highp vec4 targetVertex;\n"
            "attribute highp vec2 textureCoordinates;\n"
            "uniform highp mat4 positionMatrix;\n"
            "varying highp vec2 textureCoord;\n"
            "void main(void)\n"
            "{\n"
            "    gl_Position = positionMatrix * targetVertex;\n"
            "    textureCoord = textureCoordinates;\n"
            "}\n";

    static const char *vertexShader =
            "uniform sampler2D texY;\n"
            "uniform sampler2D texU;\n"
            "uniform sampler2D texV;\n"
            "uniform mediump mat4 colorMatrix;\n"
            "varying highp vec2 textureCoord;\n"
            "uniform lowp float opacity;"
            "void main(void)\n"
            "{\n"
            "    highp vec4 color = vec4(\n"
            "           texture2D(texY, textureCoord.st).r,\n"
            "           texture2D(texV, textureCoord.st).r,\n" // !!!! mind the swp
            "           texture2D(texU, textureCoord.st).r,\n"
            "           1.0);\n"
            "    gl_FragColor = colorMatrix * color * opacity;\n"
            "}\n";

    initYv12();
    initColorMatrix();

    if (!m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexProgram))
        qFatal("couldnt add vertex shader");
    else if (!m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, vertexShader))
        qFatal("couldnt add fragment shader");
    else if (!m_program->link())
        qFatal("couldnt link shader");

    m_glF->glGenTextures(m_textureCount, m_textureIds);

    m_inited = true;
}

void QEXTQmlVLCGLSLPainter::paint(QPainter *painter,
                        QRectF target,
                        QQuickItem *quickItem)
{
    // Need to reenable those after native painting has begun, otherwise we might
    // not be able to paint anything.
    bool stencilTestEnabled = m_glF->glIsEnabled(GL_STENCIL_TEST);
    bool scissorTestEnabled = m_glF->glIsEnabled(GL_SCISSOR_TEST);

    painter->beginNativePainting();

    if (stencilTestEnabled)
        m_glF->glEnable(GL_STENCIL_TEST);
    if (scissorTestEnabled)
        m_glF->glEnable(GL_SCISSOR_TEST);

    //////////////////////////////////////////////////////////////
    initTextures();
    //////////////////////////////////////////////////////////////

    const float textureCoordinates[] = {
        0, 1, // bottom left
        1, 1, // bottom right
        0, 0, // top left
        1, 0, // top right
    };

    const GLfloat targetVertex[] =
    {
        GLfloat(target.left()), GLfloat(target.bottom()),
        GLfloat(target.right()), GLfloat(target.bottom()),
        GLfloat(target.left()) , GLfloat(target.top()),
        GLfloat(target.right()), GLfloat(target.top())
    };
    //

    const int width = quickItem->width();
    const int height = quickItem->height();

    const QTransform transform = painter->deviceTransform();

    const GLfloat wfactor = 2.0 / width;
    const GLfloat hfactor = -2.0 / height;

    const GLfloat positionMatrix[4][4] = {
        {
            GLfloat(wfactor * transform.m11() - transform.m13()),
            GLfloat(hfactor * transform.m12() + transform.m13()),
            0.0,
            GLfloat(transform.m13())
        }, {
            GLfloat(wfactor * transform.m21() - transform.m23()),
            GLfloat(hfactor * transform.m22() + transform.m23()),
            0.0,
            GLfloat(transform.m23())
        }, {
            0.0,
            0.0,
            -1.0,
            0.0
        }, {
            GLfloat(wfactor * transform.dx() - transform.m33()),
            GLfloat(hfactor * transform.dy() + transform.m33()),
            0.0,
            GLfloat(transform.m33())
        }
    };

    m_program->bind();

    m_program->enableAttributeArray("targetVertex");
    m_program->enableAttributeArray("textureCoordinates");
    m_program->setAttributeArray("targetVertex", targetVertex, 2);
    m_program->setAttributeArray("textureCoordinates", textureCoordinates, 2);
    m_program->setUniformValue("positionMatrix", positionMatrix);

    if (m_textureCount == 3) {
        m_gl->glActiveTexture(GL_TEXTURE0);
        m_glF->glBindTexture(GL_TEXTURE_2D, m_textureIds[0]);
        m_gl->glActiveTexture(GL_TEXTURE1);
        m_glF->glBindTexture(GL_TEXTURE_2D, m_textureIds[1]);
        m_gl->glActiveTexture(GL_TEXTURE2);
        m_glF->glBindTexture(GL_TEXTURE_2D, m_textureIds[2]);
        m_gl->glActiveTexture(GL_TEXTURE0);

        m_program->setUniformValue("texY", 0);
        m_program->setUniformValue("texU", 1);
        m_program->setUniformValue("texV", 2);
    }
    m_program->setUniformValue("colorMatrix", m_colorMatrix);
    m_program->setUniformValue("opacity", GLfloat(painter->opacity()));

    m_glF->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    m_program->release();
    painter->endNativePainting();

    calculateFPS();
}

void QEXTQmlVLCGLSLPainter::calculateFPS()
{
    if (m_fps.lastTime.isNull())
        m_fps.lastTime = QTime::currentTime();
    QTime time = QTime::currentTime();

    int delta = m_fps.lastTime.msecsTo(time);
    if (delta > 2000) {
        m_fps.value = 1000.0 * m_fps.frames / qreal(delta);
        if (m_fps.value < 20.0)
            qWarning() << "Drawing less than 20 frames per second!";
        m_fps.lastTime = time;
        m_fps.frames = 0;
    }

    ++m_fps.frames;
}
