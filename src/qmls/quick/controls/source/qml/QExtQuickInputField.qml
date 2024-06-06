import QtQml 2.9
import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQuick.Controls 1.2

Item {
    id: root
    width: 160
    height: 38
    state: inputing ? "inputing" : ""
    clip: true

    signal cleared()

    property bool clearable: true
    property int verticalMargin: 5
    property int horizontalMargin : verticalMargin + (backgroundRadius >= height / 2 ? 10 : 5)
    property int placeholderPosition: QExtQuickControls.Position_Center
    property int placeholderSpacing: 10
    property color cursorColor: "#000000"

    property string placeholderText: "QExtQuickInputField"
    property color placeholderTextColor: QExtQuickPalette.textPlaceholderColor
    property font placeholderTextFont

    property bool backgroundVisible: true
    property color backgroundColor: "#FFFFFF"
    property real backgroundRadius: 2
    property real backgroundOpacity: 1
    property color backgroundBorderColor: QExtQuickPalette.borderLevel1Color
    property real backgroundBorderWidth: 1

    property string placeholderIconSource
    property real placeholderIconWidth: 12
    property real placeholderIconHeight: 12
    property color placeholderIconColor: QExtQuickPalette.textPlaceholderColor

    property string clearIconSource: "qrc:/QExtQuickControls/resource/image/close_px.svg"
    property real clearIconWidth: 20
    property real clearIconHeight: 20
    property color clearIconColor: QExtQuickPalette.textPlaceholderColor

    property color textColor: QExtQuickPalette.textPrimaryColor
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

    cursorDelegate: QExtQuickDividerLine {
        id: cursor
        width: 1
        height: mTextInput.contentHeight
        color: root.cursorColor
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
        border.width: root.backgroundBorderWidth
        border.color: backgroundVisible ? root.backgroundBorderColor : Qt.rgba(0, 0, 0, 0)
        clip: true
        color: backgroundVisible ? backgroundColor : Qt.rgba(0, 0, 0, 0)
        radius: backgroundRadius
        opacity: backgroundOpacity

        TextInput {
            id: mTextInput
            clip: true
            anchors.fill: parent
            color: root.textColor
            font: root.textFont
            verticalAlignment: TextInput.AlignVCenter
            cursorDelegate: root.cursorDelegate
            anchors.topMargin: root.verticalMargin
            anchors.bottomMargin: root.verticalMargin
            anchors.rightMargin: {
                if (clearable && mClearIconButton.visible) {
                    return mClearIconButton.width + mClearIconButton.anchors.rightMargin + mClearIconButton.anchors.leftMargin
                }
                return root.horizontalMargin
            }

            anchors.leftMargin: {
                if (mData.hold) {
                    return mPlaceholderRow.leftPadding
                }
                return root.horizontalMargin
            }

            Keys.onReleased: {
                mTextInput.focus = event.key !== Qt.Key_Escape
            }
        }

        QExtQuickImage {
            id: mClearIconButton
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 10
            focus: false
            visible: clearable && mTextInput.length > 0
            width: root.clearIconWidth
            height: root.clearIconHeight
            source: root.clearIconSource
            color: root.clearIconColor

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
            property int holdX: root.horizontalMargin
            property int leftPadding: {
                return mPlaceholderIcon.visible ? mPlaceholderIcon.width + spacing / 2 + x :
                                                  spacing / 2 + x
            }

            property int startX: {
                if (placeholderPosition !== QExtQuickControls.Position_Left) {
                    return (parent.width - width) / 2
                }
                return holdX
            }

            QExtQuickImage {
                id: mPlaceholderIcon
                enabled: false
                visible: root.placeholderIconSource.length > 0
                anchors.verticalCenter: parent.verticalCenter
                source: root.placeholderIconSource
                color: root.placeholderIconColor
                width: root.placeholderIconWidth
                height: root.placeholderIconHeight
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
        id: mData
        property bool hold: mTextInput.focus || mTextInput.length > 0 || placeholderPosition === QExtQuickControls.Position_Left
    }
}
