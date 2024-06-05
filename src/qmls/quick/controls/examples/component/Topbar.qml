import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    signal showMenu()
    color: "#F8F8F8"

    property string title: ""

    Label {
        text: title
        anchors.centerIn: parent
        font.pixelSize: 16
        font.bold: true
    }

//    Rectangle {
//        width: parent.width
//        height: 1
//        anchors.bottom: parent.bottom
//    }

}
