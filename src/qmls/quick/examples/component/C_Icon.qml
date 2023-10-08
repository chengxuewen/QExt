import QtQuick 2.12
import QtQuick.Controls 2.12
import QEXTQmlQuick 1.0

Flickable {

    Column {
        spacing: 10
        Row {
            id:layout
            spacing: 18
            Repeater{
                model: [
                    {s:QEXTQmlQuickFontAwesome.FA_bus,c:"#46A0FC"},
                    {s:QEXTQmlQuickFontAwesome.FA_cog,c:"#46A0FC"},
                    {s:QEXTQmlQuickFontAwesome.FA_qq,c:"#6AC044"},
                    {s:QEXTQmlQuickFontAwesome.FA_github,c:"#6AC044"},
                    {s:QEXTQmlQuickFontAwesome.FA_google_plus_circle,c:"#E4A147"},
                    {s:QEXTQmlQuickFontAwesome.FA_coffee,c:"#E4A147"},
                    {s:QEXTQmlQuickFontAwesome.FA_flag,c:"#F36D6F"},
                    {s:QEXTQmlQuickFontAwesome.FA_facebook_official,c:"#F36D6F"}
                ]

                delegate: QEXTQmlQuickAwesomeIcon{
                    width: 25
                    height: 25
                    source: modelData.s
                    color: modelData.c
                }
            }
        }
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

                delegate: QEXTQmlQuickSVGIcon {
                    width: 40
                    height: 40
                    source: "qrc:/images/svg"+index+".svg"
                    color: modelData
//                    mirror: true
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
