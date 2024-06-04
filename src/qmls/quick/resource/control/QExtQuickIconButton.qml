import QtQuick 2.12
import QtQml 2.12
import QtQuick.Controls 2.12
import QExtQuick 1.2

QExtQuickButton {
    id: qextIconButton
    implicitWidth: 100
    implicitHeight: 30
    text: "QExtQuickIconButton"

    property string iconSource
    property real iconWidth: 25
    property real iconHeight: 25
    property color iconColor: QExtQuickPalette.textPrimaryColor
    property bool iconVisible: true
    property real iconOpacity: 1
    property real iconPadding: 10
    property real iconSpacing: 5
    property real iconScale: 1
    property int iconDisplay: QExtQuick.IconDisplay_Left

    property Component iconItem
    property Component textItem

    iconItem: QExtQuickIcon {
        width: qextIconButton.iconWidth
        height: qextIconButton.iconHeight
        source: qextIconButton.iconSource
        color: qextIconButton.iconColor
    }
    textItem: Text {
        text: qextIconButton.text
        font: qextIconButton.textFont
        color: qextIconButton.textColor
        opacity: qextIconButton.textOpacity
        horizontalAlignment: qextIconButton.textHorizontalAlignment
        verticalAlignment: qextIconButton.textVerticalAlignment
        elide: qextIconButton.textElide
    }

    function contentItemComponent() {
        if (QExtQuick.IconDisplay_TextOnly === qextIconButton.iconDisplay) {
            return mContentTextOnlyComponent
        } else if (QExtQuick.IconDisplay_IconOnly === qextIconButton.iconDisplay) {
            return mContentIconOnlyComponent
        } else if (QExtQuick.IconDisplay_Left === qextIconButton.iconDisplay) {
            return mContentIconLeftComponent
        } else if (QExtQuick.IconDisplay_Right === qextIconButton.iconDisplay) {
            return mContentIconRightComponent
        } else if (QExtQuick.IconDisplay_Top === qextIconButton.iconDisplay) {
            return mContentIconTopComponent
        } else if (QExtQuick.IconDisplay_Bottom === qextIconButton.iconDisplay) {
            return mContentIconBottomComponent
        }
        return null
    }
    contentItem: Loader {
        anchors.fill: parent
        sourceComponent: contentItemComponent()
    }

    background: Rectangle {
        anchors.fill: parent
        color: qextIconButton.backgroundVisible ? qextIconButton.backgroundColor : Qt.rgba(0, 0, 0, 0)
        opacity: qextIconButton.backgroundOpacity
        border.color: qextIconButton.backgroundBorderVisible ? qextIconButton.backgroundBorderColor : Qt.rgba(0, 0, 0, 0)
        border.width: qextIconButton.backgroundBorderWidth
        radius: qextIconButton.backgroundRadius
    }

    Component {
        id: mContentIconOnlyComponent
        Item {
            Loader {
                anchors.centerIn: parent
                visible: qextIconButton.iconVisible
                opacity: qextIconButton.iconOpacity
                sourceComponent: iconItem
            }
        }
    }

    Component {
        id: mContentTextOnlyComponent
        Item {
            Loader {
                anchors.centerIn: parent
                sourceComponent: textItem
            }
        }
    }

    Component {
        id: mContentIconLeftComponent
        Row {
            anchors.fill: parent
            layoutDirection: Qt.LeftToRight
            leftPadding: qextIconButton.iconPadding
            spacing: qextIconButton.iconSpacing
            Loader {
                width: qextIconButton.iconWidth
                height: qextIconButton.iconHeight
                visible: qextIconButton.iconVisible
                opacity: qextIconButton.iconOpacity
                anchors.verticalCenter: parent.verticalCenter
                sourceComponent: iconItem
            }
            Loader {
                width: qextIconButton.width - qextIconButton.iconWidth - qextIconButton.iconPadding - qextIconButton.iconSpacing
                height: parent.height
                anchors.verticalCenter: parent.verticalCenter
                sourceComponent: textItem
            }
        }
    }

    Component {
        id: mContentIconRightComponent
        Row {
            anchors.fill: parent
            layoutDirection: Qt.LeftToRight
            rightPadding: qextIconButton.iconPadding
            spacing: qextIconButton.iconSpacing
            Loader {
                width: qextIconButton.width - qextIconButton.iconWidth - qextIconButton.iconPadding - qextIconButton.iconSpacing
                height: parent.height
                anchors.verticalCenter: parent.verticalCenter
                sourceComponent: textItem
            }
            Loader {
                width: qextIconButton.iconWidth
                height: qextIconButton.iconHeight
                visible: qextIconButton.iconVisible
                opacity: qextIconButton.iconOpacity
                anchors.verticalCenter: parent.verticalCenter
                sourceComponent: iconItem
            }
        }
    }

    Component {
        id: mContentIconTopComponent
        Column {
            anchors.fill: parent
            topPadding: qextIconButton.iconPadding
            spacing: qextIconButton.iconSpacing
            Loader {
                width: qextIconButton.iconWidth
                height: qextIconButton.iconHeight
                visible: qextIconButton.iconVisible
                opacity: qextIconButton.iconOpacity
                anchors.horizontalCenter: parent.horizontalCenter
                sourceComponent: iconItem
            }
            Loader {
                width: parent.width
                height: qextIconButton.height - qextIconButton.iconHeight - qextIconButton.iconPadding - qextIconButton.iconSpacing
                anchors.horizontalCenter: parent.horizontalCenter
                sourceComponent: textItem
            }
        }
    }

    Component {
        id: mContentIconBottomComponent
        Column {
            anchors.fill: parent
            bottomPadding: qextIconButton.iconPadding
            spacing: qextIconButton.iconSpacing
            Loader {
                width: parent.width
                height: qextIconButton.height - qextIconButton.iconHeight - qextIconButton.iconPadding - qextIconButton.iconSpacing
                anchors.horizontalCenter: parent.horizontalCenter
                sourceComponent: textItem
            }
            Loader {
                width: qextIconButton.iconWidth
                height: qextIconButton.iconHeight
                visible: qextIconButton.iconVisible
                opacity: qextIconButton.iconOpacity
                anchors.horizontalCenter: parent.horizontalCenter
                sourceComponent: iconItem
            }
        }
    }
}
