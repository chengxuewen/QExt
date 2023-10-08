import QtQuick 2.12
import QtQml 2.12
import QtQuick.Controls 2.12
import QEXTQmlQuick 1.0

// Popup
Dialog {
    id: qextDialog
    clip: true
    dim: true
    padding: 0
    closePolicy: Popup.NoAutoClose
    modal: true
    implicitWidth: 300
    implicitHeight: implicitHeaderHeight + implicitContentHeight + implicitFooterHeight
    anchors.centerIn: Overlay.overlay
    title: "QEXTQmlQuickDialog"

    signal buttonTriggered(var button)

    property bool layoutInCenter: true
    property bool closeable: true

    property string contentText: "QEXTQmlQuickDialog content"
    property string headerText: qextDialog.title
    property font headerTextFont: qextDialog.font
    property color headerTextColor: QEXTQmlQuickPalette.textPrimaryColor
    property real headerTextOpacity: 1
    property int headerTextHorizontalAlignment: qextDialog.layoutInCenter ? Text.AlignHCenter : Text.AlignLeft
    property int headerTextVerticalAlignment: Text.AlignVCenter
    property int headerTextElide: Text.ElideRight

    property color backgroundColor: "#FFFFFF"
    property real backgroundOpacity: 1
    property color backgroundBorderColor: QEXTQmlQuickPalette.borderLevel1Color
    property real backgroundBorderWidth: 1
    property real backgroundRadius: 5

    property real buttonSpacing: 5
    property list<QEXTQmlQuickDialogButton> buttons
    property list<QEXTQmlQuickDialogButton> defaultButtons: [
        QEXTQmlQuickDialogButton {
            lighter: true
            text: "Enter"
            textFont.bold: true
            textColor: QEXTQmlQuickPalette.textPrimaryColor
        }
    ]

    background: Rectangle {
        color: qextDialog.backgroundColor
        opacity: qextDialog.backgroundOpacity
        border.color: qextDialog.backgroundBorderColor
        border.width: qextDialog.backgroundBorderWidth
        radius: qextDialog.backgroundRadius
    }

    header: Item {
        id: mHeader
        implicitWidth: qextDialog.implicitWidth
        implicitHeight: 40

        Text {
            id: mHeaderText
            height: parent.height
            width: mCloseButton.x
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: qextDialog.headerText
            font: qextDialog.headerTextFont
            horizontalAlignment: qextDialog.headerTextHorizontalAlignment
            verticalAlignment: qextDialog.headerTextVerticalAlignment
            elide: qextDialog.headerTextElide
            opacity: qextDialog.headerTextOpacity
        }

        QEXTQmlQuickIcon {
            id: mCloseButton
            height: 20
            width: 20
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            visible: qextDialog.closeable
            source: "qrc:/QEXTQmlQuick/svg/close-px.svg"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    qextDialog.reject()
                }
            }
        }
    }

    contentItem: Item {
        id: mDialogContent
        implicitWidth: qextDialog.implicitWidth
        implicitHeight: mDialogContentText.contentHeight + 30

        Text {
            id: mDialogContentText
            width: qextDialog.implicitWidth - 20
            anchors.margins: 15
            anchors.fill: parent
            text: qextDialog.contentText
            horizontalAlignment: qextDialog.layoutInCenter ? Text.AlignHCenter : Text.AlignLeft
            verticalAlignment: qextDialog.layoutInCenter ? Text.AlignVCenter : Text.AlignTop
            wrapMode: Text.WrapAnywhere
        }

        QEXTQmlQuickDividerLine {
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

        property var buttonModel: qextDialog.buttons.length > 0 ? qextDialog.buttons : qextDialog.defaultButtons

        Row {
            id: layout
            padding: 10
            spacing: qextDialog.buttonSpacing
            x: qextDialog.layoutInCenter ? (parent.width - width) / 2 : parent.width - width
            anchors.verticalCenter: parent.verticalCenter
            Repeater {
                model: qextDialog.buttons.length > 0 ? qextDialog.buttons : qextDialog.defaultButtons
                delegate: QEXTQmlQuickIconButton {
                    width: qextDialog.contentCenter ? mDialogFooter.width / buttonModel.length : 80
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
            qextDialog.implicitWidth = Math.max(qextDialog.implicitWidth, mDialogFooter.implicitWidth)
        }
    }
}
