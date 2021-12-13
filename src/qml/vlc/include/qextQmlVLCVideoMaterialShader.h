#ifndef _QEXTQMLVLCVIDEOMATERIALSHADER_H
#define _QEXTQMLVLCVIDEOMATERIALSHADER_H

#include <QtQuick/QSGMaterial>

class QEXTQmlVLCVideoMaterialShader : public QSGMaterialShader
{
public:
    virtual char const *const *attributeNames() const;
    virtual const char *vertexShader() const;
    virtual const char *fragmentShader() const;
    virtual void initialize();

    virtual void updateState(const RenderState &state, QSGMaterial *newMaterial, QSGMaterial *oldMaterial);

private:
    int m_positionMatrixId;
    int m_colorMatrixId;
    int m_opacityId;
    int m_texYId;
    int m_texUId;
    int m_texVId;
};

#endif // _QEXTQMLVLCVIDEOMATERIALSHADER_H
