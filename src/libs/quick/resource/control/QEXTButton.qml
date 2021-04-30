import QtQuick 2.7
import QtQuick.Controls 2.0
import QEXTQuick 1.2

Button {
    id: qextButton
    width: 100
    height: 30
    opacity: qextButton.enabled ? 1.0 : 0.3
    text: "QEXTButton"

    property font textFont: qextButton.font
    property color textColor: QEXTQuickPalette.textPrimaryColor
    property real textOpacity: 1
    property int textHorizontalAlignment: Text.AlignHCenter
    property int textVerticalAlignment: Text.AlignVCenter
    property int textElide: Text.ElideRight

    property bool backgroundVisiable: true
    property bool backgroundBorderVisiable: true
    property color backgroundColor: "#FFFFFF"
    property real backgroundOpacity: 1
    property real backgroundRadius: 2
    property color backgroundBorderColor: QEXTQuickPalette.borderLevel1Color
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
        color: qextButton.backgroundVisiable ? qextButton.backgroundColor : Qt.rgba(0, 0, 0, 0)
        opacity: qextButton.backgroundOpacity
        border.color: qextButton.backgroundBorderVisiable ? qextButton.backgroundBorderColor : Qt.rgba(0, 0, 0, 0)
        border.width: qextButton.backgroundBorderWidth
        radius: qextButton.backgroundRadius
    }

    onPressed: {
        qextButton.state = QEXTQuick.stateToString(QEXTQuick.State_Pressed)
        if (pressPromptEnable) {
            scale = 0.95
        }
    }
    onReleased: {
        qextButton.state = QEXTQuick.stateToString(QEXTQuick.State_Hovered)
        if (pressPromptEnable) {
            scale = 1
        }
    }
    onHoveredChanged: {
        if (qextButton.hovered) {
            qextButton.state = QEXTQuick.stateToString(QEXTQuick.State_Hovered)
        } else {
            qextButton.state = QEXTQuick.stateToString(QEXTQuick.State_Normal)
        }
    }
    onTextFontChanged: {
        qextButton.font = qextButton.textFont
    }
}
