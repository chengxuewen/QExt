import QtQuick 2.6

Item {
    id: mControl
    anchors.fill: parent

    property color color
    property string source
    property bool smooth: true
    property bool asynchronous: true

    property alias status: mImage.status

    Image {
        id: mImage
        asynchronous: mControl.asynchronous
        anchors.fill: mControl
        source:  mControl.source
        smooth: mControl.smooth
        visible: false
        enabled: false
    }

    ShaderEffect {
        id: mShaderItem
        enabled: false
        anchors.fill: parent
        visible: mControl.status === Image.Ready
        fragmentShader: "qrc:/QExtQuickControls/resources/cso/svg.cso"

        property variant source: mImage
        property color color: mControl.color
    }
}
