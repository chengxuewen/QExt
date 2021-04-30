import QtQuick 2.7
import QEXTQuick 1.2

Column{
    spacing: 20

    QEXTNavigationBar {
        width: 400
        itemWidth: 90
        itemActiveTextFont.bold: true
        QEXTNavigationElement {
            text: "User"
        }

        QEXTNavigationElement {
            text: "Config"
        }

        QEXTNavigationElement {
            text: "Role"
        }

        QEXTNavigationElement {
            text: "Task"
        }

        children: [
            QEXTDividerLine{
                width: parent.width
                height: 1
                color: "#DCDCDC"
                anchors.bottom: parent.bottom
            }
        ]

    }


    QEXTNavigationBar {
        id:nb
        width: 400
        itemWidth: 90

        itemActiveTextColor: "#F36D6F"
        itemActiveIconColor: "#F36D6F"

        QEXTNavigationElement {
            iconSource: QEXTQuickFontAwesome.FA_apple
            text: "Apple"
        }

        QEXTNavigationElement {
            iconSource: QEXTQuickFontAwesome.FA_android
            text: "Android"
        }

        QEXTNavigationElement {
            iconSource: QEXTQuickFontAwesome.FA_github
            text: "Github"
        }

        QEXTNavigationElement {
            iconSource: QEXTQuickFontAwesome.FA_youtube
            text: "Youtube"
        }

        children: [
            QEXTDividerLine {
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

    QEXTNavigationBar {
        width: 400
        itemWidth: 90

        itemActiveTextColor: "#F36D6F"
        itemActiveIconColor: "#F36D6F"
        itemBackgroundColor: "#FAFAFA"
        itemActiveBackgroundColor: "#1A76D3"
        itemBackgroundVisiable: true

        QEXTNavigationElement {
            iconSource: QEXTQuickFontAwesome.FA_apple
            text: "Apple"
        }

        QEXTNavigationElement {
            iconSource: QEXTQuickFontAwesome.FA_android
            text: "Android"
        }

        QEXTNavigationElement {
            iconSource: QEXTQuickFontAwesome.FA_github
            text: "Github"
        }

        QEXTNavigationElement {
            iconSource: QEXTQuickFontAwesome.FA_youtube
            text: "Youtube"
        }

    }

}
