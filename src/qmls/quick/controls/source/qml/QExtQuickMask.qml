import QtQuick 2.9

Item {
    id: root

    property bool live: true
    property bool smooth: true
    property bool hideSource: true

    property alias maskItem: maskShaderEffect.sourceItem
    property alias sourceItem: sourceShaderEffect.sourceItem

    ShaderEffectSource {
        id: sourceShaderEffect
        live: root.live
        visible: false
        hideSource: root.hideSource
        smooth: root.smooth
        sourceItem: sourceItem
    }

    ShaderEffectSource {
        id: maskShaderEffect
        live: root.live
        visible: false
        hideSource: root.hideSource
        smooth: root.smooth
        sourceItem: maskItem
    }

    ShaderEffect {
        id: shaderItem
        anchors.fill: parent
        fragmentShader: "qrc:/QExtQuickControls/resource/cso/mask.cso"

        property variant source: sourceShaderEffect
        property variant maskSource: maskShaderEffect
    }

}
