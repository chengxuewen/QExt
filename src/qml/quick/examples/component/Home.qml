import QtQuick 2.9
import QtQuick.Controls 2.9

Item {

    Column{
        spacing: 30
        anchors.centerIn: parent
        Label{
            text: "Hello QEXTQmlQuick"
            font.pixelSize: 30
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
