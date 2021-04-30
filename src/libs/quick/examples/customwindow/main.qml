import QtQuick 2.6
import QtQuick.Window 2.2
import QEXTQuick 1.2

QEXTWindow {
    id: root
    width: 1024
    height: 800
    minimumWidth: 600
    minimumHeight: 400

    QEXTQuickWorld {
        mouseAreaCursorShape: Qt.PointingHandCursor
    }

    QEXTWindowTitleBar {
        height: 100
        additionalButtonBarItem: Row {
            spacing: 10
            QEXTIconButton {
                width: height
                iconDisplay: QEXTQuick.IconDisplay_IconOnly
                iconSource: QEXTQuickFontAwesome.FA_save
            }

            QEXTIconButton {
                width: height
                iconDisplay: QEXTQuick.IconDisplay_IconOnly
                iconSource: QEXTQuickFontAwesome.FA_save
            }
        }

        QEXTNavigationBar {
            id:nb
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: 10
            width: 400
            itemWidth: 90

            itemTextColor: "white"
            itemIconColor: "white"
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


    }

}
