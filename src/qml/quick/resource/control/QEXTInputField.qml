import QtQuick 2.12
import QtQml 2.12
import QtQuick.Controls 2.12

import QEXTQuick 1.0

Item {
    id: qextInputField
    width: 160
    height: 38
    state: inputing ? "inputing" : ""
    clip: true

    signal cleared()

    property bool clearable: true
    property int verticalMargin: 5
    property int horizontalMargin : verticalMargin + (backgroundRadius >= height / 2 ? 10 : 5)
    property int placeholderPosition: QEXTQuick.Position_Center
    property int placeholderSpacing: 10
    property color cursorColor: "#000000"

    property string placeholderText: "QEXTInputField"
    property color placeholderTextColor: QEXTQuickPalette.textPlaceholderColor
    property font placeholderTextFont

    property bool backgroundVisiable: true
    property color backgroundColor: "#FFFFFF"
    property real backgroundRadius: 2
    property real backgroundOpacity: 1
    property color backgroundBorderColor: QEXTQuickPalette.borderLevel1Color
    property real backgroundBorderWidth: 1

    property string placeholderIconSource
    property real placeholderIconWidth: 12
    property real placeholderIconHeight: 12
    property color placeholderIconColor: QEXTQuickPalette.textPlaceholderColor

    property string clearIconSource: "qrc:/QEXTQuick/svg/close-px.svg"
    property real clearIconWidth: 20
    property real clearIconHeight: 20
    property color clearIconColor: QEXTQuickPalette.textPlaceholderColor

    property color textColor: QEXTQuickPalette.textPrimaryColor
    property font textFont

    property alias inputing: mTextInput.focus
    property alias acceptableInput: mTextInput.acceptableInput
    property alias activeFocusOnPress: mTextInput.activeFocusOnPress
    property alias canPaste: mTextInput.canPaste
    property alias canRedo: mTextInput.canRedo
    property alias canUndo: mTextInput.canUndo
    property alias echoMode: mTextInput.echoMode
    property alias inputMask: mTextInput.inputMask
    property alias inputMethodComposing: mTextInput.inputMethodComposing
    property alias inputMethodHints: mTextInput.inputMethodHints
    property alias length: mTextInput.length
    property alias maximumLength: mTextInput.maximumLength
    property alias selectByMouse: mTextInput.selectByMouse
    property alias selectedText: mTextInput.selectedText
    property alias selectionEnd: mTextInput.selectionEnd
    property alias selectionStart: mTextInput.selectionStart
    property alias text: mTextInput.text
    property alias qtInput: mTextInput

    property Component cursorDelegate

    cursorDelegate: QEXTDividerLine {
        id: cursor
        width: 1
        height: mTextInput.contentHeight
        color: qextInputField.cursorColor
        visible: false
        Timer {
            interval: 500
            running: mTextInput.focus
            repeat: true
            onTriggered: cursor.visible = !cursor.visible
            onRunningChanged: !running ? cursor.visible = false : false
        }
    }


    Rectangle {
        anchors.fill: parent
        border.width: qextInputField.backgroundBorderWidth
        border.color: backgroundVisiable ? qextInputField.backgroundBorderColor : Qt.rgba(0, 0, 0, 0)
        clip: true
        color: backgroundVisiable ? backgroundColor : Qt.rgba(0, 0, 0, 0)
        radius: backgroundRadius
        opacity: backgroundOpacity

        TextInput {
            id: mTextInput
            clip: true
            anchors.fill: parent
            color: qextInputField.textColor
            font: qextInputField.textFont
            verticalAlignment: TextInput.AlignVCenter
            cursorDelegate: qextInputField.cursorDelegate
            anchors.topMargin: qextInputField.verticalMargin
            anchors.bottomMargin: qextInputField.verticalMargin
            anchors.rightMargin: {
                if (clearable && mClearIconButton.visible) {
                    return mClearIconButton.width + mClearIconButton.anchors.rightMargin + mClearIconButton.anchors.leftMargin
                }
                return qextInputField.horizontalMargin
            }

            anchors.leftMargin: {
                if (mPrivate.hold) {
                    return mPlaceholderRow.leftPadding
                }
                return qextInputField.horizontalMargin
            }

            Keys.onReleased: {
                mTextInput.focus = event.key !== Qt.Key_Escape
            }
        }

        QEXTIcon {
            id: mClearIconButton
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 10
            focus: false
            visible: clearable && mTextInput.length > 0
            width: qextInputField.clearIconWidth
            height: qextInputField.clearIconHeight
            source: qextInputField.clearIconSource
            color: qextInputField.clearIconColor

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    mTextInput.text = ""
                }
            }
        }


        Row {
            id: mPlaceholderRow
            spacing: 4
            opacity: 0.7
            x: mTextInput.focus || mTextInput.length > 0 ? holdX : startX
            anchors.verticalCenter: parent.verticalCenter
            property int holdX: qextInputField.horizontalMargin
            property int leftPadding: {
                return mPlaceholderIcon.visible ? mPlaceholderIcon.width + spacing / 2 + x :
                                                  spacing / 2 + x
            }

            property int startX: {
                if (placeholderPosition !== QEXTQuick.Position_Left) {
                    return (parent.width - width) / 2
                }
                return holdX
            }

            QEXTIcon {
                id: mPlaceholderIcon
                enabled: false
                visible: qextInputField.placeholderIconSource.length > 0
                anchors.verticalCenter: parent.verticalCenter
                source: qextInputField.placeholderIconSource
                color: qextInputField.placeholderIconColor
                width: qextInputField.placeholderIconWidth
                height: qextInputField.placeholderIconHeight
            }

            Behavior on x {
                NumberAnimation {
                    duration: 100
                    onRunningChanged: mPlaceholderLabel.vout = running
                }
            }

            Label {
                id: mPlaceholderLabel
                text: placeholderText
                color: placeholderTextColor
                font: placeholderTextFont

                property bool vout
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: {
                    vout
                    if (!vout && mTextInput.focus || mTextInput.length > 0) {
                        return -50
                    }
                    return 0
                }

                Behavior on anchors.verticalCenterOffset {
                    NumberAnimation {
                        duration: 200
                    }
                }
            }
        }
    }

    QtObject {
        id: mPrivate
        property bool hold: mTextInput.focus || mTextInput.length > 0 || placeholderPosition === QEXTQuick.Position_Left
    }
}
