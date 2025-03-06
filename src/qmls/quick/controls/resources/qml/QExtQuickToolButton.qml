import QtQml 2.9
import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQuick.Controls 1.3

QExtQuickButton {
    id: root
    implicitWidth: 100
    implicitHeight: 30
    text: "QExtQuickToolButton"

    property string iconSource
    property real iconWidth: 25
    property real iconHeight: 25
    property color iconColor: QExtQuickPalette.textPrimaryColor
    property bool iconVisible: true
    property real iconOpacity: 1
    property real iconPadding: 10
    property real iconSpacing: 5
    property real iconScale: 1
    property int iconDisplay: QExtQuickControls.IconDisplay_Left

    property Component iconItem
    property Component textItem

    iconItem: QExtQuickImage {
        width: root.iconWidth
        height: root.iconHeight
        source: root.iconSource
        color: root.iconColor
    }
    textItem: Text {
        text: root.text
        font: root.textFont
        color: root.textColor
        opacity: root.textOpacity
        horizontalAlignment: root.textHorizontalAlignment
        verticalAlignment: root.textVerticalAlignment
        elide: root.textElide
    }

    function contentItemComponent() {
        if (QExtQuickControls.IconDisplay_TextOnly === root.iconDisplay) {
            return mContentTextOnlyComponent
        } else if (QExtQuickControls.IconDisplay_IconOnly === root.iconDisplay) {
            return mContentIconOnlyComponent
        } else if (QExtQuickControls.IconDisplay_Left === root.iconDisplay) {
            return mContentIconLeftComponent
        } else if (QExtQuickControls.IconDisplay_Right === root.iconDisplay) {
            return mContentIconRightComponent
        } else if (QExtQuickControls.IconDisplay_Top === root.iconDisplay) {
            return mContentIconTopComponent
        } else if (QExtQuickControls.IconDisplay_Bottom === root.iconDisplay) {
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
        color: root.backgroundVisible ? root.backgroundColor : Qt.rgba(0, 0, 0, 0)
        opacity: root.backgroundOpacity
        border.color: root.backgroundBorderVisible ? root.backgroundBorderColor : Qt.rgba(0, 0, 0, 0)
        border.width: root.backgroundBorderWidth
        radius: root.backgroundRadius
    }

    Component {
        id: mContentIconOnlyComponent
        Item {
            Loader {
                anchors.centerIn: parent
                visible: root.iconVisible
                opacity: root.iconOpacity
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
            leftPadding: root.iconPadding
            spacing: root.iconSpacing
            Loader {
                width: root.iconWidth
                height: root.iconHeight
                visible: root.iconVisible
                opacity: root.iconOpacity
                anchors.verticalCenter: parent.verticalCenter
                sourceComponent: iconItem
            }
            Loader {
                width: root.width - root.iconWidth - root.iconPadding - root.iconSpacing
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
            rightPadding: root.iconPadding
            spacing: root.iconSpacing
            Loader {
                width: root.width - root.iconWidth - root.iconPadding - root.iconSpacing
                height: parent.height
                anchors.verticalCenter: parent.verticalCenter
                sourceComponent: textItem
            }
            Loader {
                width: root.iconWidth
                height: root.iconHeight
                visible: root.iconVisible
                opacity: root.iconOpacity
                anchors.verticalCenter: parent.verticalCenter
                sourceComponent: iconItem
            }
        }
    }

    Component {
        id: mContentIconTopComponent
        Column {
            anchors.fill: parent
            topPadding: root.iconPadding
            spacing: root.iconSpacing
            Loader {
                width: root.iconWidth
                height: root.iconHeight
                visible: root.iconVisible
                opacity: root.iconOpacity
                anchors.horizontalCenter: parent.horizontalCenter
                sourceComponent: iconItem
            }
            Loader {
                width: parent.width
                height: root.height - root.iconHeight - root.iconPadding - root.iconSpacing
                anchors.horizontalCenter: parent.horizontalCenter
                sourceComponent: textItem
            }
        }
    }

    Component {
        id: mContentIconBottomComponent
        Column {
            anchors.fill: parent
            bottomPadding: root.iconPadding
            spacing: root.iconSpacing
            Loader {
                width: parent.width
                height: root.height - root.iconHeight - root.iconPadding - root.iconSpacing
                anchors.horizontalCenter: parent.horizontalCenter
                sourceComponent: textItem
            }
            Loader {
                width: root.iconWidth
                height: root.iconHeight
                visible: root.iconVisible
                opacity: root.iconOpacity
                anchors.horizontalCenter: parent.horizontalCenter
                sourceComponent: iconItem
            }
        }
    }
}
