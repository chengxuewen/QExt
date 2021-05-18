import QtQuick 2.12
import QEXTQuick 1.2

Item {
    id: qextAvatar
    width: mSourceImage.sourceSize.width
    height: mSourceImage.sourceSize.height

    property bool asynchronous: true
    property bool smooth: true
    property color borderColor: QEXTQuickPalette.borderLevel1Color
    property real borderWidth: 0
    property real radius: 0

    property alias source: mSourceImage.source
    property alias fillMode: mSourceImage.fillMode

    Image {
        id: mSourceImage
        visible: false
        enabled: false
        anchors.fill: parent
        antialiasing: qextAvatar.smooth
        smooth: qextAvatar.smooth
        asynchronous: qextAvatar.asynchronous
    }

    Rectangle {
        id: mMaskRect
        anchors.fill: parent
        color: "black"
        radius: qextAvatar.radius
        visible: false
        antialiasing: true
        smooth: true
        enabled: false
    }

    Rectangle {
        id: mMaskBorder
        anchors.fill: parent
        color: "transparent"
        radius: qextAvatar.radius
        border.width: qextAvatar.borderWidth
        border.color: qextAvatar.borderColor
    }

    QEXTMask {
        anchors.fill: parent
        sourceItem: mSourceImage
        maskItem: mMaskRect
    }
}
