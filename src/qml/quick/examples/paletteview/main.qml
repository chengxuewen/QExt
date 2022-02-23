import QtQuick 2.9
import QtQuick.Controls 2.9
import QtQuick.Layouts 1.12
import QtQml 2.9
import QtQuick.Window 2.2
import QEXTQmlQuick 1.0
import QEXTQmlQuickPaletteView 1.0

Window {
    id: root
    visible: true
    width: 550
    height: 700

    QEXTQmlQuickWorld {
        mouseAreaCursorShape: Qt.PointingHandCursor
    }

    QEXTQmlQuickPaletteTableModel {
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
                        append({text: "brandPrimaryColor", color: QEXTQmlQuickPalette.brandPrimaryColor})
                        append({text: "brandSecondaryColor", color: QEXTQmlQuickPalette.brandSecondaryColor})
                        append({text: "brandAccentColor", color: QEXTQmlQuickPalette.brandAccentColor})
                        append({text: "brandDarkColor", color: QEXTQmlQuickPalette.brandDarkColor})
                        append({text: "brandPositiveColor", color: QEXTQmlQuickPalette.brandPositiveColor})
                        append({text: "brandNegativeColor", color: QEXTQmlQuickPalette.brandNegativeColor})
                        append({text: "brandInfoColor", color: QEXTQmlQuickPalette.brandInfoColor})
                        append({text: "brandSuccessColor", color: QEXTQmlQuickPalette.brandSuccessColor})
                        append({text: "brandWarningColor", color: QEXTQmlQuickPalette.brandWarningColor})
                        append({text: "brandDangerColor", color: QEXTQmlQuickPalette.brandDangerColor})
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
                        append({text: "textPrimaryColor", color: QEXTQmlQuickPalette.textPrimaryColor})
                        append({text: "textNormalColor", color: QEXTQmlQuickPalette.textNormalColor})
                        append({text: "textSecondaryColor", color: QEXTQmlQuickPalette.textSecondaryColor})
                        append({text: "textPlaceholderColor", color: QEXTQmlQuickPalette.textPlaceholderColor})
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
                        append({text: "borderLevel1Color", color: QEXTQmlQuickPalette.borderLevel1Color})
                        append({text: "borderLevel2Color", color: QEXTQmlQuickPalette.borderLevel2Color})
                        append({text: "borderLevel3Color", color: QEXTQmlQuickPalette.borderLevel3Color})
                        append({text: "borderLevel4Color", color: QEXTQmlQuickPalette.borderLevel4Color})
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
