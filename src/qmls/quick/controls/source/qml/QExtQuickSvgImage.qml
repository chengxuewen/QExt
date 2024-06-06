import QtQuick 2.9

/* default is async load mode */
Item {
    id: root
    width: 16
    height: 16

    property alias source: image.source
    property alias mipmap: image.mipmap
    property alias smooth: image.smooth
    property alias status: image.status
    property alias color: shaderItem.color
    property alias asynchronous: image.asynchronous

    Image {
        id: image
        asynchronous: true
        autoTransform: true
        anchors.fill: root
        mipmap: true
        smooth: true
        visible: false
        enabled: false
    }

    ShaderEffect {
        id: shaderItem
        property variant source: image
        property color color: "#000000"

        enabled: false
        fragmentShader: "qrc:/QExtQuickControls/resource/cso/svg.cso"
        anchors.fill: parent
        visible: root.status === Image.Ready
    }
}
