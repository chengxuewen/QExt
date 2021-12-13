/*************************************************************************************
*
* Library: QEXT
*
* Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
*
* License: MIT License
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*************************************************************************************/

#ifndef _QEXTQMLVLCGLPAINTER_H
#define _QEXTQMLVLCGLPAINTER_H

#include <qextVLCVideoFrame.h>

#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLContext>
#include <QtGui/QPainter>

#if QT_VERSION < 0x050300
    #if defined(QT_OPENGL_ES_2)
        #include <QtGui/QOpenGLFunctions_ES2>
    #else
        #include <QtGui/QOpenGLFunctions_1_1>
    #endif
#else
    #include <QtGui/QOpenGLFunctions>
#endif


class QEXTQmlVLCGlPainter
{
    typedef struct
    {
        GLenum target;
        GLint internalFormat;
        GLenum format;
        GLenum type;
    } GlTextureDescriptor;

    typedef struct
    {
        GLsizei width;
        GLsizei height;
    } GlTextureSize;

public:
    virtual ~QEXTQmlVLCGlPainter();

    void setFrame(const QEXTVLCVideoFrame *frame)
    {
        m_frame = frame;
    }
    bool inited() const
    {
        return m_inited;
    }

    void setContext(QOpenGLContext *context);

    void initColorMatrix();
    void initTextures();
    void initYv12();

protected:
    QEXTQmlVLCGlPainter();

    const QEXTVLCVideoFrame *m_frame;
    bool m_inited;

    QOpenGLContext *m_context;
    QOpenGLFunctions *m_gl;
#if QT_VERSION < 0x050300
#if defined(QT_OPENGL_ES_2)
    QOpenGLFunctions_ES2 *m_glF;
#else
    QOpenGLFunctions_1_1 *m_glF;
#endif
#else
    QOpenGLFunctions *m_glF;
#endif

    int m_textureCount;
    GLuint m_textureIds[3];

    GlTextureDescriptor m_texDescriptor;
    GlTextureSize m_texSize[3];

    QMatrix4x4 m_colorMatrix;

    bool m_texturesInited;
};

#endif // _QEXTQMLVLCGLPAINTER_H
