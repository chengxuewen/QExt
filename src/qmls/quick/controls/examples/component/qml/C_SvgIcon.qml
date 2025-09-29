import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQuick.Controls 1.4

Flickable {
    Column {
        spacing: 10
        Grid {
            id: mGrid
            columns: 6
            spacing: 20
            Repeater {
                model: [
                    "#46A0FC",
                    "#46A0FC",
                    "#46A0FC",
                    "#6AC044",
                    "#6AC044",
                    "#6AC044",
                    "#E4A147",
                    "#E4A147",
                    "#E4A147",
                    "#F36D6F",
                    "#F36D6F",
                    "#F36D6F",
                ]

                delegate: QExtQuickSvgIcon {
                    width: 40
                    height: 40
                    color: modelData
                    source: "qrc:/images/svg"+index+".svg"
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
