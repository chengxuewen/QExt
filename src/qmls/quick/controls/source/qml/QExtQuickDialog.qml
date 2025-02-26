import QtQml 2.9
import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQuick.Controls 1.3

// Popup
Dialog {
    id: root
    dim: true
    clip: true
    modal: true
    padding: 0
    closePolicy: Popup.NoAutoClose
    implicitWidth: 300
    implicitHeight: implicitHeaderHeight + implicitContentHeight + implicitFooterHeight
    anchors.centerIn: Overlay.overlay
    title: "QExtQuickDialog"

    signal buttonTriggered(var button)

    property bool layoutInCenter: true
    property bool closeable: true

    property string contentText: "QExtQuickDialog content"
    property string headerText: root.title
    property font headerTextFont: root.font
    property color headerTextColor: QExtQuickPalette.textPrimaryColor
    property real headerTextOpacity: 1
    property int headerTextHorizontalAlignment: root.layoutInCenter ? Text.AlignHCenter : Text.AlignLeft
    property int headerTextVerticalAlignment: Text.AlignVCenter
    property int headerTextElide: Text.ElideRight

    property color backgroundColor: "#FFFFFF"
    property real backgroundOpacity: 1
    property color backgroundBorderColor: QExtQuickPalette.borderLevel1Color
    property real backgroundBorderWidth: 1
    property real backgroundRadius: 5

    property real buttonSpacing: 5
    property list<QExtQuickDialogButton> buttons
    property list<QExtQuickDialogButton> defaultButtons: [
        QExtQuickDialogButton {
            lighter: true
            text: "Enter"
            textFont.bold: true
            textColor: QExtQuickPalette.textPrimaryColor
        }
    ]

    background: Rectangle {
        color: root.backgroundColor
        opacity: root.backgroundOpacity
        border.color: root.backgroundBorderColor
        border.width: root.backgroundBorderWidth
        radius: root.backgroundRadius
    }

    header: Item {
        id: mHeader
        implicitWidth: root.implicitWidth
        implicitHeight: 40

        Text {
            id: mHeaderText
            height: parent.height
            width: mCloseButton.x
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: root.headerText
            font: root.headerTextFont
            horizontalAlignment: root.headerTextHorizontalAlignment
            verticalAlignment: root.headerTextVerticalAlignment
            elide: root.headerTextElide
            opacity: root.headerTextOpacity
        }

        QExtQuickImage {
            id: mCloseButton
            height: 20
            width: 20
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            visible: root.closeable
            source: "qrc:/QExtQuickControls/resource/image/close_px.svg"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.reject()
                }
            }
        }
    }

    contentItem: Item {
        id: mDialogContent
        implicitWidth: root.implicitWidth
        implicitHeight: mDialogContentText.contentHeight + 30

        Text {
            id: mDialogContentText
            width: root.implicitWidth - 20
            anchors.margins: 15
            anchors.fill: parent
            text: root.contentText
            horizontalAlignment: root.layoutInCenter ? Text.AlignHCenter : Text.AlignLeft
            verticalAlignment: root.layoutInCenter ? Text.AlignVCenter : Text.AlignTop
            wrapMode: Text.WrapAnywhere
        }

        QExtQuickDividerLine {
            id: mDialogContentDividerLine
            width: parent.width * 0.95
            height: 1
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
        }

    }

    footer: Item {
        id: mDialogFooter
        implicitWidth: layout.implicitWidth
        implicitHeight: layout.implicitHeight

        property var buttonModel: root.buttons.length > 0 ? root.buttons : root.defaultButtons

        Row {
            id: layout
            padding: 10
            spacing: root.buttonSpacing
            x: root.layoutInCenter ? (parent.width - width) / 2 : parent.width - width
            anchors.verticalCenter: parent.verticalCenter
            Repeater {
                model: root.buttons.length > 0 ? root.buttons : root.defaultButtons
                delegate: QExtQuickToolButton {
                    width: root.contentCenter ? mDialogFooter.width / buttonModel.length : 80
                    padding: 20
                    anchors.verticalCenter: parent.verticalCenter

                    text: modelData.text
                    textFont: modelData.textFont
                    textColor: modelData.textColor

                    iconSource: modelData.iconSource
                    iconWidth: modelData.iconWidth
                    iconHeight: modelData.iconHeight
                    iconColor: modelData.iconColor

                    backgroundVisible: modelData.backgroundVisible
                    backgroundColor: modelData.backgroundColor
                    backgroundBorderColor: modelData.backgroundBorderColor
                    backgroundBorderWidth: modelData.backgroundBorderWidth
                    backgroundRadius: modelData.backgroundRadius

                    onClicked: buttonTriggered(modelData)
                }
            }
        }

        Component.onCompleted: {
            root.implicitWidth = Math.max(root.implicitWidth, mDialogFooter.implicitWidth)
        }
    }
}
