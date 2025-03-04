import QtQuick 2.9

import QExtQuick.Controls 1.3

Item {
    id: root
    width: sourceImage.sourceSize.width
    height: sourceImage.sourceSize.height

    property bool asynchronous: true
    property bool smooth: true
    property color borderColor: QExtQuickPalette.borderLevel1Color
    property real borderWidth: 0
    property real radius: 0

    property alias source: sourceImage.source
    property alias fillMode: sourceImage.fillMode

    Image {
        id: sourceImage
        visible: false
        enabled: false
        anchors.fill: parent
        antialiasing: root.smooth
        smooth: root.smooth
        asynchronous: root.asynchronous
    }

    Rectangle {
        id: maskRect
        anchors.fill: parent
        color: "black"
        radius: root.radius
        visible: false
        antialiasing: true
        smooth: true
        enabled: false
    }

    Rectangle {
        id: maskBorder
        anchors.fill: parent
        color: "transparent"
        radius: root.radius
        border.width: root.borderWidth
        border.color: root.borderColor
    }

    QExtQuickMask {
        anchors.fill: parent
        maskItem: maskRect
        sourceItem: sourceImage
    }
}
