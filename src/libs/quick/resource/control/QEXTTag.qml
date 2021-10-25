import QtQuick 2.12
import QtQuick.Controls 2.12
import QEXTQuick 1.2

Item {
    id: qextTag
    width: mContentLayout.width + padding
    height: mContentLayout.height + padding

    signal closed()

    property int padding: 14
    property int spacing: 8
    property bool closable: false

    property alias icon: mCloseIcon
    property alias label: mContentLabel
    property alias background: mBackgroundRect

    property alias clickable: qextTag.enabled

    Rectangle {
        id: mBackgroundRect
        anchors.fill: parent

        color: "#ECF5FF"
        radius: 2
        border.width: 1
        border.color: Qt.darker("#409EFF", 1.1)
    }

    Row {
        id: mContentLayout
        anchors.centerIn: qextTag
        spacing: qextTag.spacing

        Label {
            id: mContentLabel
            anchors.verticalCenter: parent.verticalCenter

            text: "QEXTTag"
            color: "#409EFF"
        }

        QEXTIcon {
            id: mCloseIcon
            anchors.verticalCenter: parent.verticalCenter

            visible: qextTag.closable
            width: 15
            height: 15
            color: "#409EFF"
            source: "qrc:/QEXTQuick/svg/close-px.svg"

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onClicked: qextTag.closed()
                cursorShape: Qt.ClosedHandCursor
            }
        }
    }
}
