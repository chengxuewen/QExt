import QtQuick 2.12
import QtQuick.Controls 2.12

Item {

    Column {
        spacing: 30
        anchors.centerIn: parent
        Label {
            text: "Hello QExtQuickControls"
            font.pixelSize: 30
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Button {
            width: 100
            height: 30
            onPressed: {
                popup.x = pressX
                popup.y = pressY
                popup.open();
            }
            Popup {
                id: popup
                x: 100
                y: 100
                width: 100
                height: 300
                background: Rectangle {
                    anchors.fill: parent
                    color: "red"
                    opacity: 0.5
                }
            }
        }
    }
}
