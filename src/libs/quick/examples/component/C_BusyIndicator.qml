import QtQuick 2.12
import QtQuick.Controls 2.12
import QEXTQuick 1.2

Item{
    width: 350
    height: 180
    Label {
        wrapMode :Text.WordWrap
        anchors.fill: parent
        text:"With QEXTQuick becoming more popular every day, there is the constant need to be different. There are millions of users. If QEXTQuick layouts are chosen well, then you can enhance your profile a great deal.\n
        With QEXTQuick becoming more popular every day, there is the constant need to be different. There are millions of users. If QEXTQuick layouts are chosen well, then you can enhance your profile a great deal."
    }

    Rectangle {
        anchors.fill: parent
        opacity: 0.9
    }

    QEXTBusyIndicator {
        id:tbi
        anchors.centerIn: parent
    }

    Row {
        spacing: 50
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        QEXTButton {
            width: 200
            background: null
            text: "Change in circles"
            onClicked: tbi.contentItem = tbi.contentIconAnimatorItem
        }

        QEXTButton {
            width: 200
            background: null
            text: "Change in dot"
            onClicked: tbi.contentItem = tbi.contentDotAnimatorItem
        }
    }


}
