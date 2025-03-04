import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQml 2.12
import QtQuick.Window 2.2

import QExtQuick.Controls 1.3
import QExtQuickPaletteView 1.0

Window {
    id: root
    visible: true
    width: 550
    height: 700

    QExtQuickWorld {
        mouseAreaCursorShape: Qt.PointingHandCursor
    }

    QExtQuickPaletteTableModel {
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
                        append({text: "brandPrimaryColor", color: QExtQuickPalette.brandPrimaryColor})
                        append({text: "brandSecondaryColor", color: QExtQuickPalette.brandSecondaryColor})
                        append({text: "brandAccentColor", color: QExtQuickPalette.brandAccentColor})
                        append({text: "brandDarkColor", color: QExtQuickPalette.brandDarkColor})
                        append({text: "brandPositiveColor", color: QExtQuickPalette.brandPositiveColor})
                        append({text: "brandNegativeColor", color: QExtQuickPalette.brandNegativeColor})
                        append({text: "brandInfoColor", color: QExtQuickPalette.brandInfoColor})
                        append({text: "brandSuccessColor", color: QExtQuickPalette.brandSuccessColor})
                        append({text: "brandWarningColor", color: QExtQuickPalette.brandWarningColor})
                        append({text: "brandDangerColor", color: QExtQuickPalette.brandDangerColor})
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
                        append({text: "textPrimaryColor", color: QExtQuickPalette.textPrimaryColor})
                        append({text: "textNormalColor", color: QExtQuickPalette.textNormalColor})
                        append({text: "textSecondaryColor", color: QExtQuickPalette.textSecondaryColor})
                        append({text: "textPlaceholderColor", color: QExtQuickPalette.textPlaceholderColor})
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
                        append({text: "borderLevel1Color", color: QExtQuickPalette.borderLevel1Color})
                        append({text: "borderLevel2Color", color: QExtQuickPalette.borderLevel2Color})
                        append({text: "borderLevel3Color", color: QExtQuickPalette.borderLevel3Color})
                        append({text: "borderLevel4Color", color: QExtQuickPalette.borderLevel4Color})
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
