import QtQuick 2.12
import QtQuick.Window 2.2

import QExtQuick.Controls 1.4

Window {
    id: root
    visible: true
    width: 640
    height: 480
    color: "#1e1e1e"
    title: "QExtQuickIpcWidgetItem IPC Test"

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
        
        Rectangle {
            anchors.left: parent.left
            anchors.top: parent.top
            width: parent.width / 3 * 2
            height: parent.height / 3 * 2
            color: '#ec1102'
            QExtQuickIpcWidgetItem {
                id: ipcItemA
                objectName: "ipcItemA"
                anchors.fill: parent
                anchors.margins: 50

                processPath: "QExtExpQuickIpcWidgetChild"
                processArgs: []

                Rectangle {
                    anchors.fill: parent
                    color: '#b5ec02'
                }
            }
        }
    
        Rectangle {
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: parent.width / 3 * 2
            height: parent.height / 3 * 2
            color: '#0e02ec'
            QExtQuickIpcWidgetItem {
                id: ipcItemB
                objectName: "ipcItemB"
                anchors.fill: parent
                anchors.margins: 50

                processPath: "QExtExpQuickIpcWidgetChild"
                processArgs: []

                Rectangle {
                    anchors.fill: parent
                    color: '#02c9ec'
                }
            }
        }
    }
}