import QtQuick 2.12
import QEXTQmlQuick 1.0

Column{
    spacing: 20

    QEXTQmlQuickNavigationBar {
        width: 400
        itemWidth: 90
        itemActiveTextFont.bold: true
        QEXTQmlQuickNavigationElement {
            text: "User"
        }

        QEXTQmlQuickNavigationElement {
            text: "Config"
        }

        QEXTQmlQuickNavigationElement {
            text: "Role"
        }

        QEXTQmlQuickNavigationElement {
            text: "Task"
        }

        children: [
            QEXTQmlQuickDividerLine{
                width: parent.width
                height: 1
                color: "#DCDCDC"
                anchors.bottom: parent.bottom
            }
        ]

    }


    QEXTQmlQuickNavigationBar {
        id:nb
        width: 400
        itemWidth: 90

        itemActiveTextColor: "#F36D6F"
        itemActiveIconColor: "#F36D6F"

        QEXTQmlQuickNavigationElement {
            iconSource: QEXTQmlQuickFontAwesome.FA_apple
            text: "Apple"
        }

        QEXTQmlQuickNavigationElement {
            iconSource: QEXTQmlQuickFontAwesome.FA_android
            text: "Android"
        }

        QEXTQmlQuickNavigationElement {
            iconSource: QEXTQmlQuickFontAwesome.FA_github
            text: "Github"
        }

        QEXTQmlQuickNavigationElement {
            iconSource: QEXTQmlQuickFontAwesome.FA_youtube
            text: "Youtube"
        }

        children: [
            QEXTQmlQuickDividerLine {
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

    QEXTQmlQuickNavigationBar {
        width: 400
        itemWidth: 90

        itemActiveTextColor: "#F36D6F"
        itemActiveIconColor: "#F36D6F"
        itemBackgroundColor: "#FAFAFA"
        itemActiveBackgroundColor: "#1A76D3"
        itemBackgroundVisiable: true

        QEXTQmlQuickNavigationElement {
            iconSource: QEXTQmlQuickFontAwesome.FA_apple
            text: "Apple"
        }

        QEXTQmlQuickNavigationElement {
            iconSource: QEXTQmlQuickFontAwesome.FA_android
            text: "Android"
        }

        QEXTQmlQuickNavigationElement {
            iconSource: QEXTQmlQuickFontAwesome.FA_github
            text: "Github"
        }

        QEXTQmlQuickNavigationElement {
            iconSource: QEXTQmlQuickFontAwesome.FA_youtube
            text: "Youtube"
        }

    }

}
