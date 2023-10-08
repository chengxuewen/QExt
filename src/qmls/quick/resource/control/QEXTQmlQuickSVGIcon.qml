import QtQuick 2.9

/*https://www.iconfont.cn
 default is async load mode
*/
Item {
    id: qextSVGIcon
    width: 16
    height: 16

    property alias color: mShaderItem.color
    property alias asynchronous: mImage.asynchronous
    property alias source: mImage.source
    property alias mipmap: mImage.mipmap
    property alias smooth: mImage.smooth
    property alias status: mImage.status

    Image {
        id: mImage
        asynchronous: true
        autoTransform: true
        anchors.fill: qextSVGIcon
        mipmap: true
        smooth: true
        visible: false
        enabled: false
    }

    ShaderEffect {
        id: mShaderItem
        property variant source: mImage
        property color color: "#000000"

        enabled: false
        fragmentShader: "qrc:/QEXTQmlQuick/font/svg.cso"
        anchors.fill: parent
        visible: qextSVGIcon.status === Image.Ready
    }
}
