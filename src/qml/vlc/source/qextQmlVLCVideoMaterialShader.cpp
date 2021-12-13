#include <qextQmlVLCVideoMaterial.h>
#include <qextQmlVLCVideoMaterialShader.h>

char const *const *QEXTQmlVLCVideoMaterialShader::attributeNames() const
{
    static const char *names[] =
    {
        "targetVertex",
        "textureCoordinates",
        0
    };
    return names;
}

const char *QEXTQmlVLCVideoMaterialShader::vertexShader() const
{
    return "attribute highp vec4 targetVertex;"
           "attribute highp vec2 textureCoordinates;"
           "uniform highp mat4 positionMatrix;"
           "varying highp vec2 textureCoord;"
           "void main(void)"
           "{"
           "    gl_Position = positionMatrix * targetVertex;"
           "    textureCoord = textureCoordinates;"
           "}";
}

const char *QEXTQmlVLCVideoMaterialShader::fragmentShader() const
{
    return "uniform sampler2D texY;"
           "uniform sampler2D texU;"
           "uniform sampler2D texV;"
           "uniform mediump mat4 colorMatrix;"
           "varying highp vec2 textureCoord;"
           "uniform lowp float opacity;"
           "void main(void)"
           "{"
           "    highp vec4 color = vec4("
           "           texture2D(texY, textureCoord.st).r,"
           "           texture2D(texU, textureCoord.st).r,"
           "           texture2D(texV, textureCoord.st).r,"
           "           1.0);"
           "    gl_FragColor = colorMatrix * color * opacity;"
           "}";
}

void QEXTQmlVLCVideoMaterialShader::initialize()
{
    m_positionMatrixId = program()->uniformLocation("positionMatrix");
    m_colorMatrixId = program()->uniformLocation("colorMatrix");
    m_opacityId = program()->uniformLocation("opacity");
    m_texYId = program()->uniformLocation("texY");
    m_texUId = program()->uniformLocation("texU");
    m_texVId = program()->uniformLocation("texV");
}

void QEXTQmlVLCVideoMaterialShader::updateState(const RenderState &state,
                                                QSGMaterial *newMaterial,
                                                QSGMaterial *oldMaterial)
{
    Q_UNUSED(oldMaterial)

    if (state.isOpacityDirty())
    {
        program()->setUniformValue(m_opacityId, GLfloat(state.opacity()));
    }

    if (state.isMatrixDirty())
    {
        program()->setUniformValue(m_positionMatrixId, state.combinedMatrix());
    }

    static const QMatrix4x4 colorMatrix(
                1.164383561643836, 0.000000000000000, 1.792741071428571, -0.972945075016308,
                1.164383561643836, -0.213248614273730, -0.532909328559444, 0.301482665475862,
                1.164383561643836, 2.112401785714286, 0.000000000000000, -1.133402217873451,
                0.000000000000000, 0.000000000000000, 0.000000000000000, 1.000000000000000);

    program()->setUniformValue(m_colorMatrixId, colorMatrix);

    QEXTQmlVLCVideoMaterial *material = static_cast<QEXTQmlVLCVideoMaterial *>(newMaterial);

    program()->setUniformValue(m_texYId, 0);
    program()->setUniformValue(m_texUId, 1);
    program()->setUniformValue(m_texVId, 2);

    material->bindPlanes();
}
