import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQuick.Controls 1.2

Item {
    id: root
    width: contentLayout.width + padding
    height: contentLayout.height + padding

    signal closed()

    property int padding: 14
    property int spacing: 8
    property bool closable: false

    property alias icon: closeIcon
    property alias label: contentLabel
    property alias background: backgroundRect

    property alias clickable: root.enabled

    Rectangle {
        id: backgroundRect
        anchors.fill: parent

        color: "#ECF5FF"
        radius: 2
        border.width: 1
        border.color: Qt.darker("#409EFF", 1.1)
    }

    Row {
        id: contentLayout
        anchors.centerIn: root
        spacing: root.spacing

        Label {
            id: contentLabel
            anchors.verticalCenter: parent.verticalCenter

            text: "QExtQuickTag"
            color: "#409EFF"
        }

        QExtQuickSvgImage {
            id: closeIcon
            anchors.verticalCenter: parent.verticalCenter
            visible: root.closable
            width: 15
            height: 15
            color: "#409EFF"
            source: "qrc:/QExtQuickControls/resource/image/close_px.svg"

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onClicked: root.closed()
                cursorShape: Qt.ClosedHandCursor
            }
        }
    }
}
