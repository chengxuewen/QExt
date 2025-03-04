import QtQml 2.9
import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQuick.Controls 1.3

Button {
    id: root
    width: 100
    height: 30
    opacity: root.enabled ? 1.0 : 0.3
    text: "QExtQuickButton"

    property font textFont: root.font
    property color textColor: QExtQuickPalette.textPrimaryColor
    property real textOpacity: 1
    property int textHorizontalAlignment: Text.AlignHCenter
    property int textVerticalAlignment: Text.AlignVCenter
    property int textElide: Text.ElideRight

    property bool backgroundVisible: true
    property bool backgroundBorderVisible: true
    property color backgroundColor: "#FFFFFF"
    property real backgroundOpacity: 1
    property real backgroundRadius: 2
    property color backgroundBorderColor: QExtQuickPalette.borderLevel1Color
    property real backgroundBorderWidth: 1

    property bool pressPromptEnable: true

    contentItem: Text {
        text: root.text
        font: root.textFont
        color: root.textColor
        opacity: root.textOpacity
        horizontalAlignment: root.textHorizontalAlignment
        verticalAlignment: root.textVerticalAlignment
        elide: root.textElide
    }

    background: Rectangle {
        anchors.fill: root
        color: root.backgroundVisible ? root.backgroundColor : Qt.rgba(0, 0, 0, 0)
        opacity: root.backgroundOpacity
        border.color: root.backgroundBorderVisible ? root.backgroundBorderColor : Qt.rgba(0, 0, 0, 0)
        border.width: root.backgroundBorderWidth
        radius: root.backgroundRadius
    }

    onPressed: {
        root.state = QExtQuickControls.stateToString(QExtQuickControls.State_Pressed)
        if (pressPromptEnable) {
            scale = 0.95
        }
    }
    onReleased: {
        root.state = QExtQuickControls.stateToString(QExtQuickControls.State_Hovered)
        if (pressPromptEnable) {
            scale = 1
        }
    }
    onHoveredChanged: {
        if (root.hovered) {
            root.state = QExtQuickControls.stateToString(QExtQuickControls.State_Hovered)
        } else {
            root.state = QExtQuickControls.stateToString(QExtQuickControls.State_Normal)
        }
    }
    onTextFontChanged: {
        root.font = root.textFont
    }
}
