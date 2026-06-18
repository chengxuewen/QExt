import QtQuick 2.12
import QtQuick.Window 2.2

import QExtQuick.Controls 1.4

Window {
    id: root
    visible: true
    width: 640
    height: 480
    color: "#2b2b2b"
    title: "QExtQuickWidgetItem Example"

    Rectangle {
        id: bg
        anchors.fill: parent
        anchors.margins: 40
        color: '#e90e0e'
        border.color: "#555"
        border.width: 1
        radius: 4

        Text {
            anchors.centerIn: parent
            text: "QML Background\n(widget will overlay here)"
            color: "#888"
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
        }

        QExtQuickWidgetItem {
            id: widgetItem
            objectName: "widgetItem"
            anchors.fill: parent
            anchors.margins: 20
            anchors.leftMargin: 40
            anchors.rightMargin: 40
            rootWindow: root
            widgetHideEnabled: true

            onRootWindowChanged: console.log("rootWindow changed:", rootWindow)
        }
    }
}