import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    anchors.bottom: parent.bottom
    color: "#43CEE6"

    Row {
        spacing: 10
        anchors.centerIn: parent

        Label{
            text: "Powered by QExtQuick"
            color: "#FFF"
            font.bold: true
            font.pixelSize: 15
        }

    }
}
