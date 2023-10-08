import QtQuick 2.12
import QtQuick.Controls 2.12
import QEXTQmlQuick 1.0

Item{
    id: page

    GridView{
        id: gview
        clip: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.fill: parent
        cellWidth: 120
        cellHeight: 60

        model: QEXTQmlQuickFontAwesome.awesomelist()

        delegate: Item{
            clip: true
            width: 110
            height: 60
            QEXTQmlQuickAwesomeIcon {
                source: modelData
                width: 30
                height: 30
                anchors.centerIn: parent
            }

            Label {
                text: modelData
                font.pixelSize: 10
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                onContentWidthChanged: {
                    if (contentWidth > parent.width) {
                        text = text.slice(0,10) + ".."
                    }
                }
            }
        }
        ScrollBar.vertical: ScrollBar {
            parent: parent
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
        }
    }
}
