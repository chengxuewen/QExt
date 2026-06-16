import QtQuick 2.12
import QtQuick.Window 2.2

import QExtQuick.Controls 1.4

Window {
    id: root
    visible: true
    width: 640
    height: 480
    color: "#1e1e1e"
    title: "QExtQuickIpcWidgetItem â IPC Test"

    Rectangle {
        anchors.fill: parent
        anchors.margins: 20
        color: "#2d2d2d"
        border.color: "#444"
        border.width: 1

        Text {
            anchors.centerIn: parent
            text: "Child widget will appear here\n(via IPC WId embedding)"
            color: "#666"
            font.pixelSize: 14
            horizontalAlignment: Text.AlignHCenter
        }
    }

    QExtQuickIpcWidgetItem {
        id: ipcItem
        objectName: "ipcItem"
        anchors.fill: parent
        anchors.margins: 50

        processPath: "QExtExpQuickIpcWidgetChild"
        processArgs: []

    }
}