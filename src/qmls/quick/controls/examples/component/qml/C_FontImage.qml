import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQml.FontIcon 1.3
import QExtQuick.Controls 1.3

Flickable {
    Column {
        spacing: 10
        Row {
            id:layout
            spacing: 18
            Repeater{
                model: [
                    { s: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_bug), c: "#46A0FC" },
                    { s: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_cog), c: "#46A0FC" },
                    { s: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_qq), c: "#6AC044" },
                    { s: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_github), c: "#6AC044" },
                    { s: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_google_plus_circle), c: "#E4A147" },
                    { s: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_coffee), c: "#E4A147" },
                    { s: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_flag), c:"#F36D6F" },
                    { s: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_facebook_official), c: "#F36D6F" }
                ]

                delegate: QExtQuickFontImage{
                    width: 25
                    height: 25
                    source: modelData.s
                    color: modelData.c
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
