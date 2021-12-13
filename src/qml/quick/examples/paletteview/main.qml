import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQml 2.12
import QtQuick.Window 2.2
import QEXTQuick 1.0
import QEXTQuickPaletteView 1.0

Window {
    id: root
    visible: true
    width: 550
    height: 700

    QEXTQuickWorld {
        mouseAreaCursorShape: Qt.PointingHandCursor
    }

    QEXTQuickPaletteTableModel {
        id: mQuickPaletteTableModel
    }

    TabBar {
        id: mTabBar
        height: 60
        width: parent.width
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        TabButton {
            text: "Material color"
        }
        TabButton {
            text: "Brand color"
        }
        TabButton {
            text: "Text color"
        }
        TabButton {
            text: "Border color"
        }
        onCurrentIndexChanged: {
            mStackLayout.currentIndex = currentIndex
        }
    }
    StackLayout {
        id: mStackLayout
        width: parent.width
        anchors.top: mTabBar.bottom
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        TableView {
            id: mTableView
            boundsBehavior: Flickable.StopAtBounds
            flickableDirection: Flickable.AutoFlickDirection
            model: mQuickPaletteTableModel
            columnWidthProvider: function (column) {
                return 100
            }
            rowHeightProvider: function (row) {
                return 60
            }
            delegate: Rectangle {
                color: colorName
                Text {
                    anchors.left: parent.left
                    anchors.top: parent.top
                    text: colorDepth
                    color: "black"
                }
                Text {
                    anchors.centerIn: parent
                    text: colorName
                    color: "white"
                }
            }
            ScrollBar.vertical: ScrollBar {
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
            }
            ScrollBar.horizontal: ScrollBar {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
            }
        }

        Item {
            ListView {
                anchors.fill: parent
                model: ListModel {
                    Component.onCompleted: {
                        append({text: "brandPrimaryColor", color: QEXTQuickPalette.brandPrimaryColor})
                        append({text: "brandSecondaryColor", color: QEXTQuickPalette.brandSecondaryColor})
                        append({text: "brandAccentColor", color: QEXTQuickPalette.brandAccentColor})
                        append({text: "brandDarkColor", color: QEXTQuickPalette.brandDarkColor})
                        append({text: "brandPositiveColor", color: QEXTQuickPalette.brandPositiveColor})
                        append({text: "brandNegativeColor", color: QEXTQuickPalette.brandNegativeColor})
                        append({text: "brandInfoColor", color: QEXTQuickPalette.brandInfoColor})
                        append({text: "brandSuccessColor", color: QEXTQuickPalette.brandSuccessColor})
                        append({text: "brandWarningColor", color: QEXTQuickPalette.brandWarningColor})
                        append({text: "brandDangerColor", color: QEXTQuickPalette.brandDangerColor})
                    }
                }
                delegate: Rectangle {
                    width: 100
                    height: 60
                    color: model.color
                    Text {
                        anchors.centerIn: parent
                        text: model.text
                        color: "white"
                    }
                }
            }
        }

        Item {
            ListView {
                anchors.fill: parent
                model: ListModel {
                    Component.onCompleted: {
                        append({text: "textPrimaryColor", color: QEXTQuickPalette.textPrimaryColor})
                        append({text: "textNormalColor", color: QEXTQuickPalette.textNormalColor})
                        append({text: "textSecondaryColor", color: QEXTQuickPalette.textSecondaryColor})
                        append({text: "textPlaceholderColor", color: QEXTQuickPalette.textPlaceholderColor})
                    }
                }
                delegate: Rectangle {
                    width: 100
                    height: 60
                    color: model.color
                    Text {
                        anchors.centerIn: parent
                        text: model.text
                        color: "white"
                    }
                }
            }
        }

        Item {
            ListView {
                anchors.fill: parent
                model: ListModel {
                    Component.onCompleted: {
                        append({text: "borderLevel1Color", color: QEXTQuickPalette.borderLevel1Color})
                        append({text: "borderLevel2Color", color: QEXTQuickPalette.borderLevel2Color})
                        append({text: "borderLevel3Color", color: QEXTQuickPalette.borderLevel3Color})
                        append({text: "borderLevel4Color", color: QEXTQuickPalette.borderLevel4Color})
                    }
                }
                delegate: Rectangle {
                    width: 100
                    height: 60
                    color: model.color
                    Text {
                        anchors.centerIn: parent
                        text: model.text
                        color: "white"
                    }
                }
            }
        }
    }

}
