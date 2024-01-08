import QtQuick 2.12
import QtQml 2.12
import QtQuick.Controls 2.12
import QExtQuick 1.2

CheckBox {
    id: qextCheckBox
    implicitWidth: leftInset + rightInset + leftPadding + rightPadding + mPrivate.implicitAvailableWidth
    implicitHeight: 30
    checkable: true
    checked: false
    opacity: qextCheckBox.enabled ? 1.0 : 0.5
    text: "QEXCheckBox"

    property color indicatorColor: "#46A0FC"

    property bool textInLeft: false
    property font textFont: qextCheckBox.font
    property color textColor: QEXTQmlQuickPalette.textPrimaryColor
    property real textOpacity: 1
    property int textHorizontalAlignment: Text.AlignHCenter
    property int textElide: Text.ElideRight
    property real textSpacing: 5

    property color backgroundColor: "#FFFFFF"
    property bool backgroundVisible: true
    property real backgroundOpacity: qextCheckBox.enabled ? 1 : 0.3
    property color backgroundBorderColor: QEXTQmlQuickPalette.borderLevel1Color
    property real backgroundBorderWidth: 0
    property real backgroundRadius: 2

    indicator: QEXTQmlQuickIcon {
        id: mIcon
        x: qextCheckBox.textInLeft ? qextCheckBox.width - qextCheckBox.rightInset - qextCheckBox.rightPadding - qextCheckBox.availableHeight :
                                     qextCheckBox.leftInset + qextCheckBox.leftPadding
        anchors.verticalCenter: parent.verticalCenter
        width: qextCheckBox.availableHeight
        height: qextCheckBox.availableHeight
        color: qextCheckBox.indicatorColor
        source: {
            if (Qt.Unchecked === checkState) {
                return QEXTQmlQuickFontAwesome.FA_square_o
            } else if (Qt.PartiallyChecked === checkState) {
                return QEXTQmlQuickFontAwesome.FA_minus_square
            } else if (Qt.Checked === checkState) {
                return QEXTQmlQuickFontAwesome.FA_check_square
            }
            return ""
        }
    }
    contentItem: Text {
        id: mText
        height: parent.availableHeight
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: qextCheckBox.textInLeft ? qextCheckBox.leftInset + qextCheckBox.leftPadding :
                                                      qextCheckBox.leftInset + qextCheckBox.leftPadding * 2 + qextCheckBox.availableHeight
        anchors.rightMargin: qextCheckBox.textInLeft ? qextCheckBox.rightInset + qextCheckBox.rightPadding * 2 + qextCheckBox.availableHeight :
                                                       qextCheckBox.rightInset + qextCheckBox.rightPadding
        anchors.verticalCenter: parent.verticalCenter
        text: qextCheckBox.text
        font: qextCheckBox.textFont
        color: qextCheckBox.textColor
        opacity: qextCheckBox.textOpacity
        horizontalAlignment: qextCheckBox.textHorizontalAlignment
        verticalAlignment: Text.AlignVCenter
        elide: qextCheckBox.textElide
        Binding {
            target: mPrivate
            property: "textContentWidth"
            value: mText.contentWidth
        }
    }
    background: Rectangle {
        anchors.fill: parent
        color: qextCheckBox.backgroundColor
        visible: qextCheckBox.backgroundVisible
        opacity: qextCheckBox.backgroundOpacity
        border.color: qextCheckBox.backgroundBorderColor
        border.width: qextCheckBox.backgroundBorderWidth
        radius: qextCheckBox.backgroundRadius
    }
    QtObject {
        id: mPrivate
        property real textContentWidth: 0
        property real implicitAvailableWidth: qextCheckBox.textInLeft > 0 ? textContentWidth + qextCheckBox.rightPadding + qextCheckBox.availableHeight :
                                                                            textContentWidth + qextCheckBox.leftPadding + qextCheckBox.availableHeight
    }
    onTextFontChanged: {
        qextCheckBox.font = qextCheckBox.textFont
    }
    onCheckStateChanged: {
        if (Qt.Unchecked === checkState) {
            qextCheckBox.state = QEXTQmlQuick.stateToString(QEXTQmlQuick.State_Unchecked)
        } else if (Qt.PartiallyChecked === checkState) {
            qextCheckBox.state = QEXTQmlQuick.stateToString(QEXTQmlQuick.State_PartiallyChecked)
        } else if (Qt.Checked === checkState) {
            qextCheckBox.state = QEXTQmlQuick.stateToString(QEXTQmlQuick.State_Checked)
        }
    }
}
