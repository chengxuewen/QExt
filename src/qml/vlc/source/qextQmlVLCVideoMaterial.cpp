#include <qextQmlVLCVideoMaterial.h>
#include <qextQmlVLCVideoMaterialShader.h>
#include <qextVLCYUVVideoFrame.h>

QEXTQmlVLCVideoMaterial::QEXTQmlVLCVideoMaterial()
    : m_frame(0)
{
    memset(m_planeTexIds, 0, sizeof(m_planeTexIds));
    setFlag(Blending, false);

#if QT_VERSION < 0x050300
#if defined(QT_OPENGL_ES_2)
    m_glF = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_ES2>();
#else
    m_glF = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_1_3>();
#endif
    Q_ASSERT(m_glF);

    m_glF->initializeOpenGLFunctions();
#else
    m_glF = QOpenGLContext::currentContext()->functions();
#endif
}

QEXTQmlVLCVideoMaterial::~QEXTQmlVLCVideoMaterial()
{
    if (m_planeTexIds[0] || m_planeTexIds[1] || m_planeTexIds[2])
    {
        m_glF->glDeleteTextures(3, m_planeTexIds);
    }
}

QSGMaterialType *QEXTQmlVLCVideoMaterial::type() const
{
    static QSGMaterialType theType;
    return &theType;
}

QSGMaterialShader *QEXTQmlVLCVideoMaterial::createShader() const
{
    return new QEXTQmlVLCVideoMaterialShader;
}

int QEXTQmlVLCVideoMaterial::compare(const QSGMaterial *other) const
{
    const QEXTQmlVLCVideoMaterial *material = static_cast<const QEXTQmlVLCVideoMaterial *>(other);
    const unsigned texCount = sizeof(m_planeTexIds) / sizeof(m_planeTexIds[0]);

    for (unsigned i = 0; i < texCount; ++i)
    {
        if (m_planeTexIds[i] != material->m_planeTexIds[i])
        {
            return m_planeTexIds[i] - material->m_planeTexIds[i];
        }
    }

    return 0;
}

void QEXTQmlVLCVideoMaterial::setFrame(const QSharedPointer<const QEXTVLCYUVVideoFrame> &frame)
{
    m_frame = frame;
}

void QEXTQmlVLCVideoMaterial::bindPlanes()
{
    if (m_planeTexIds[0] == 0 && m_planeTexIds[1] == 0 && m_planeTexIds[2] == 0)
    {
        m_glF->glGenTextures(3, m_planeTexIds);
    }

    QSharedPointer<const QEXTVLCYUVVideoFrame> tmpFrame;
    m_frame.swap(tmpFrame);

    if (tmpFrame)
    {
        Q_ASSERT((tmpFrame->width & 1) == 0 && (tmpFrame->height & 1) == 0); // width and height should be even
        const quint16 tw = tmpFrame->width;
        const quint16 th = tmpFrame->height;

        bindPlane(GL_TEXTURE1, m_planeTexIds[1], tmpFrame->planes[1], tw / 2, th / 2);
        bindPlane(GL_TEXTURE2, m_planeTexIds[2], tmpFrame->planes[2], tw / 2, th / 2);
        bindPlane(GL_TEXTURE0, m_planeTexIds[0], tmpFrame->planes[0], tw, th);
    }
    else
    {
        bindPlane(GL_TEXTURE1, m_planeTexIds[1], 0, 0, 0);
        bindPlane(GL_TEXTURE2, m_planeTexIds[2], 0, 0, 0);
        bindPlane(GL_TEXTURE0, m_planeTexIds[0], 0, 0, 0);
    }
}

void QEXTQmlVLCVideoMaterial::bindPlane(GLenum texUnit, GLuint texId, const void *plane,
                                        quint16 width, quint16 height)
{
    m_glF->glActiveTexture(texUnit);
    m_glF->glBindTexture(GL_TEXTURE_2D, texId);
    if (plane)
    {
        m_glF->glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE,
                            width, height, 0,
                            GL_LUMINANCE, GL_UNSIGNED_BYTE, plane);
        m_glF->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        m_glF->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        m_glF->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        m_glF->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
}
