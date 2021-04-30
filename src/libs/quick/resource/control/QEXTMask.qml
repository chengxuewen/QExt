import QtQuick 2.7

Item {
    id: qextMask

    property bool smooth: true
    property bool hideSource: true
    property bool live: true

    property alias sourceItem: mSourceShaderEffect.sourceItem
    property alias maskItem: mMaskShaderEffect.sourceItem

    ShaderEffectSource {
        id: mSourceShaderEffect
        live: qextMask.live
        visible: false
        hideSource: qextMask.hideSource
        smooth: qextMask.smooth
        sourceItem: sourceItem
    }

    ShaderEffectSource {
        id: mMaskShaderEffect
        live: qextMask.live
        visible: false
        hideSource: qextMask.hideSource
        smooth: qextMask.smooth
        sourceItem: maskItem
    }

    ShaderEffect {
        id: shaderItem
        anchors.fill: parent
        fragmentShader: "qrc:/QEXTQuick/font/mask.cso"

        property variant source: mSourceShaderEffect
        property variant maskSource: mMaskShaderEffect
    }

}
