import QtQuick 2.12
import QtQuick.Controls 2.12

Item {

    Column{
        spacing: 30
        anchors.centerIn: parent
        Label{
            text: "Hello QEXTQuick"
            font.pixelSize: 30
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
