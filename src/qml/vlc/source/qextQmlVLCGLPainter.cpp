#include <qextQmlVLCGLPainter.h>

QEXTQmlVLCGlPainter::QEXTQmlVLCGlPainter()
    : m_frame(0)
    , m_inited(false)
    , m_context(0)
    , m_texturesInited(false) { }

QEXTQmlVLCGlPainter::~QEXTQmlVLCGlPainter() { }

void QEXTQmlVLCGlPainter::setContext(QOpenGLContext *context)
{
    m_context = context;
}

void QEXTQmlVLCGlPainter::initYv12()
{
    Q_ASSERT(m_frame->planeCount == 3);
    m_textureCount = m_frame->planeCount;

    m_texDescriptor.target = GL_TEXTURE_2D;
    m_texDescriptor.internalFormat = GL_LUMINANCE;
    m_texDescriptor.format = GL_LUMINANCE;
    m_texDescriptor.type = GL_UNSIGNED_BYTE;
}

void QEXTQmlVLCGlPainter::initColorMatrix()
{
    m_colorMatrix = QMatrix4x4(1.0, 0.0, 0.0, 0.0,
                               0.0, 1.0, 0.0, 0.0,
                               0.0, 0.0, 1.0, 0.0,
                               0.0, 0.0, 0.0, 1.0);
    QMatrix4x4 colorSpaceMatrix;
    if (m_frame->height > 576)
        colorSpaceMatrix =
            QMatrix4x4(
                1.164383561643836,  0.000000000000000,  1.792741071428571, -0.972945075016308,
                1.164383561643836, -0.213248614273730, -0.532909328559444,  0.301482665475862,
                1.164383561643836,  2.112401785714286,  0.000000000000000, -1.133402217873451,
                0.000000000000000,  0.000000000000000,  0.000000000000000,  1.000000000000000);
    else
        colorSpaceMatrix =
            QMatrix4x4(
                1.164383561643836,  0.000000000000000,  1.596026785714286, -0.874202217873451,
                1.164383561643836, -0.391762290094914, -0.812967647237771,  0.531667823499146,
                1.164383561643836,  2.017232142857142,  0.000000000000000, -1.085630789302022,
                0.000000000000000,  0.000000000000000,  0.000000000000000,  1.000000000000000);
    m_colorMatrix = m_colorMatrix * colorSpaceMatrix;
}

void QEXTQmlVLCGlPainter::initTextures()
{
    if (!m_texturesInited)
    {
        for (unsigned i = 0; i < m_frame->planeCount; ++i)
        {
            m_glF->glBindTexture(m_texDescriptor.target, m_textureIds[i]);
            m_glF->glTexImage2D(m_texDescriptor.target,
                                0,
                                m_texDescriptor.internalFormat,
                                m_frame->visiblePitch[i],
                                m_frame->visibleLines[i],
                                0,
                                m_texDescriptor.format,
                                m_texDescriptor.type,
                                0);
            // Scale appropriately so we can change to target geometry without
            // much hassle.
            m_glF->glTexParameterf(m_texDescriptor.target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            m_glF->glTexParameterf(m_texDescriptor.target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            m_glF->glTexParameterf(m_texDescriptor.target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            m_glF->glTexParameterf(m_texDescriptor.target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            m_texturesInited = true;
        }
    }

    for (unsigned i = 0; i < m_frame->planeCount; ++i)
    {
        m_glF->glBindTexture(m_texDescriptor.target, m_textureIds[i]);

// Based on vlc/src/video_output/opengl.c
#ifndef GL_UNPACK_ROW_LENGTH
#define ALIGN(x, y) (((x) + ((y) - 1)) & ~((y) - 1))
        int dst_pitch = ALIGN(m_frame->visiblePitch[i], 4);
        char *new_plane = (char *) malloc(dst_pitch * m_frame->visibleLines[i]);
        const char *source = m_frame->plane[i].data();
        char *destination = new_plane;
        for (int y = 0; y < m_frame->visibleLines[i]; y++)
        {
            memcpy(destination, source, m_frame->visiblePitch[i]);
            source += m_frame->pitch[i];
            destination += dst_pitch;
        }

        m_glF->glTexSubImage2D(m_texDescriptor.target, 0,
                               0, 0,
                               m_frame->visiblePitch[i],
                               m_frame->visibleLines[i],
                               m_texDescriptor.format,
                               m_texDescriptor.type,
                               new_plane);
        free(new_plane);
#else
        m_glF->glPixelStorei(GL_UNPACK_ROW_LENGTH, m_frame->pitch[i]);
        m_glF->glTexSubImage2D(m_texDescriptor.target, 0,
                               0, 0,
                               m_frame->visiblePitch[i],
                               m_frame->visibleLines[i],
                               m_texDescriptor.format,
                               m_texDescriptor.type,
                               m_frame->plane[i].data());
        m_glF->glPixelStorei(GL_UNPACK_ROW_LENGTH, 0); // reset to default
#endif
    }
}
