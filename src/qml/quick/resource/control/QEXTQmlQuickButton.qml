import QtQuick 2.12
import QtQml 2.12
import QtQuick.Controls 2.12

import QEXTQmlQuick 1.0

Button {
    id: qextButton
    width: 100
    height: 30
    opacity: qextButton.enabled ? 1.0 : 0.3
    text: "QEXTQmlQuickButton"

    property font textFont: qextButton.font
    property color textColor: QEXTQmlQuickPalette.textPrimaryColor
    property real textOpacity: 1
    property int textHorizontalAlignment: Text.AlignHCenter
    property int textVerticalAlignment: Text.AlignVCenter
    property int textElide: Text.ElideRight

    property bool backgroundVisible: true
    property bool backgroundBorderVisible: true
    property color backgroundColor: "#FFFFFF"
    property real backgroundOpacity: 1
    property real backgroundRadius: 2
    property color backgroundBorderColor: QEXTQmlQuickPalette.borderLevel1Color
    property real backgroundBorderWidth: 1

    property bool pressPromptEnable: true

    contentItem: Text {
        text: qextButton.text
        font: qextButton.textFont
        color: qextButton.textColor
        opacity: qextButton.textOpacity
        horizontalAlignment: qextButton.textHorizontalAlignment
        verticalAlignment: qextButton.textVerticalAlignment
        elide: qextButton.textElide
    }

    background: Rectangle {
        anchors.fill: qextButton
        color: qextButton.backgroundVisible ? qextButton.backgroundColor : Qt.rgba(0, 0, 0, 0)
        opacity: qextButton.backgroundOpacity
        border.color: qextButton.backgroundBorderVisible ? qextButton.backgroundBorderColor : Qt.rgba(0, 0, 0, 0)
        border.width: qextButton.backgroundBorderWidth
        radius: qextButton.backgroundRadius
    }

    onPressed: {
        qextButton.state = QEXTQmlQuick.stateToString(QEXTQmlQuick.State_Pressed)
        if (pressPromptEnable) {
            scale = 0.95
        }
    }
    onReleased: {
        qextButton.state = QEXTQmlQuick.stateToString(QEXTQmlQuick.State_Hovered)
        if (pressPromptEnable) {
            scale = 1
        }
    }
    onHoveredChanged: {
        if (qextButton.hovered) {
            qextButton.state = QEXTQmlQuick.stateToString(QEXTQmlQuick.State_Hovered)
        } else {
            qextButton.state = QEXTQmlQuick.stateToString(QEXTQmlQuick.State_Normal)
        }
    }
    onTextFontChanged: {
        qextButton.font = qextButton.textFont
    }
}
