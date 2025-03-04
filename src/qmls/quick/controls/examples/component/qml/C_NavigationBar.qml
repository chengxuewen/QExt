import QtQuick 2.12
import QExtQuick.Controls 1.3

Column{
    spacing: 20

    QExtQuickNavigationBar {
        width: 400
        itemWidth: 90
        itemActiveTextFont.bold: true
        QExtQuickNavigationElement {
            text: "User"
        }

        QExtQuickNavigationElement {
            text: "Config"
        }

        QExtQuickNavigationElement {
            text: "Role"
        }

        QExtQuickNavigationElement {
            text: "Task"
        }

        children: [
            QExtQuickDividerLine{
                width: parent.width
                height: 1
                color: "#DCDCDC"
                anchors.bottom: parent.bottom
            }
        ]

    }


    QExtQuickNavigationBar {
        id:nb
        width: 400
        itemWidth: 90

        itemActiveTextColor: "#F36D6F"
        itemActiveIconColor: "#F36D6F"

        QExtQuickNavigationElement {
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_apple)
            text: "Apple"
        }

        QExtQuickNavigationElement {
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_android)
            text: "Android"
        }

        QExtQuickNavigationElement {
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_github)
            text: "Github"
        }

        QExtQuickNavigationElement {
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_youtube)
            text: "Youtube"
        }

        children: [
            QExtQuickDividerLine {
                anchors.bottom: parent.bottom
                width: nb.currentItem.width
                height: 2
                x: nb.currentItem.x
                color: "#DCDCDC"

                Behavior on x {
                    NumberAnimation {
                        easing.type: Easing.OutBack
                        duration: 100
                    }
                }
            }
        ]
    }

    QExtQuickNavigationBar {
        width: 400
        itemWidth: 90

        itemActiveTextColor: "#F36D6F"
        itemActiveIconColor: "#F36D6F"
        itemBackgroundColor: "#FAFAFA"
        itemActiveBackgroundColor: "#1A76D3"
        itemBackgroundVisible: true

        QExtQuickNavigationElement {
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_apple)
            text: "Apple"
        }

        QExtQuickNavigationElement {
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_android)
            text: "Android"
        }

        QExtQuickNavigationElement {
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_github)
            text: "Github"
        }

        QExtQuickNavigationElement {
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_youtube)
            text: "Youtube"
        }

    }

}
