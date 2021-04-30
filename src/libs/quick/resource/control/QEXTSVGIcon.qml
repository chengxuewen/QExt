import QtQuick 2.7

/*https://www.iconfont.cn
 default is async load mode
*/
Item {
    id: qextSVGIcon
    width: 16
    height: 16

    property bool asynchronous: true
    property bool smooth: true
    property bool mipmap: true
    property color color
    property string source

    property alias status: mImage.status

    Image {
        id: mImage
        asynchronous: qextSVGIcon.asynchronous
        autoTransform: true
        anchors.fill: qextSVGIcon
        source: qextSVGIcon.source
        mipmap: qextSVGIcon.mipmap
        smooth: qextSVGIcon.smooth
        visible: false
        enabled: false
    }

    ShaderEffect {
        id: mShaderItem
        property variant source: mImage
        property color color: qextSVGIcon.color
        enabled: false
        fragmentShader: "qrc:/QEXTQuick/font/svg.cso"
        anchors.fill: parent
        visible: qextSVGIcon.status === Image.Ready
    }
}
