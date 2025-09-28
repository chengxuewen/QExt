import QtQml 2.12
import QtQuick 2.12
import QtQuick.Window 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import QExtQml 1.4
import QExtQml.Theme 1.4
import PaletteTableModel 1.0

Window {
    width: 600
    height: 400
    visible: true

    PaletteTableModel {
        id: mPaletteTableModel
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
            model: mPaletteTableModel
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
                        append({text: "brandPrimaryColor", color: QExtQmlThemeManager.palette.brandPrimaryColor})
                        append({text: "brandSecondaryColor", color: QExtQmlThemeManager.palette.brandSecondaryColor})
                        append({text: "brandAccentColor", color: QExtQmlThemeManager.palette.brandAccentColor})
                        append({text: "brandDarkColor", color: QExtQmlThemeManager.palette.brandDarkColor})
                        append({text: "brandPositiveColor", color: QExtQmlThemeManager.palette.brandPositiveColor})
                        append({text: "brandNegativeColor", color: QExtQmlThemeManager.palette.brandNegativeColor})
                        append({text: "brandInfoColor", color: QExtQmlThemeManager.palette.brandInfoColor})
                        append({text: "brandSuccessColor", color: QExtQmlThemeManager.palette.brandSuccessColor})
                        append({text: "brandWarningColor", color: QExtQmlThemeManager.palette.brandWarningColor})
                        append({text: "brandDangerColor", color: QExtQmlThemeManager.palette.brandDangerColor})
                    }
                }
                delegate: Rectangle {
                    width: parent.width
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
                        append({text: "textPrimaryColor", color: QExtQmlThemeManager.palette.textPrimaryColor})
                        append({text: "textNormalColor", color: QExtQmlThemeManager.palette.textNormalColor})
                        append({text: "textSecondaryColor", color: QExtQmlThemeManager.palette.textSecondaryColor})
                        append({text: "textPlaceholderColor", color: QExtQmlThemeManager.palette.textPlaceholderColor})
                    }
                }
                delegate: Rectangle {
                    width: parent.width
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
                        append({text: "borderLevel1Color", color: QExtQmlThemeManager.palette.borderLevel1Color})
                        append({text: "borderLevel2Color", color: QExtQmlThemeManager.palette.borderLevel2Color})
                        append({text: "borderLevel3Color", color: QExtQmlThemeManager.palette.borderLevel3Color})
                        append({text: "borderLevel4Color", color: QExtQmlThemeManager.palette.borderLevel4Color})
                    }
                }
                delegate: Rectangle {
                    width: parent.width
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

    Component.onCompleted: {
        console.warn("QExtQml.version()=", QExtQmlThemeManager.version);
        console.warn("borderLevel1Color=", QExtQmlThemeManager.palette.borderLevel1Color);
    }
}
