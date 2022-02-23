import QtQuick 2.9
import QtQml 2.9
import QtQuick.Controls 2.9
import QEXTQmlQuick 1.0

RadioButton {
    id: qextRadioButton
    implicitWidth: leftInset + rightInset + leftPadding + rightPadding + mPrivate.implicitAvailableWidth
    implicitHeight: 30
    checkable: true
    checked: false
    opacity: qextRadioButton.enabled ? 1.0 : 0.5
    padding: 5

    property color indicatorColor: "#46A0FC"

    property bool textInLeft: false
    property font textFont: qextRadioButton.font
    property color textColor: QEXTQmlQuickPalette.textPrimaryColor
    property real textOpacity: 1
    property int textHorizontalAlignment: Text.AlignHCenter
    property int textVerticalAlignment: Text.AlignVCenter
    property int textElide: Text.ElideRight

    property color backgroundColor: "#FFFFFF"
    property bool backgroundVisiable: false
    property real backgroundOpacity: qextRadioButton.enabled ? 1 : 0.3
    property color backgroundBorderColor: QEXTQmlQuickPalette.borderLevel1Color
    property real backgroundBorderWidth: 0
    property real backgroundRadius: 2

    property Component radioItem: radioAnimatorItem

    indicator: Loader {
        x: qextRadioButton.textInLeft ? qextRadioButton.width - qextRadioButton.rightInset - qextRadioButton.rightPadding - qextRadioButton.availableHeight :
                                        qextRadioButton.leftInset + qextRadioButton.leftPadding
        width: qextRadioButton.availableHeight
        height: qextRadioButton.availableHeight
        anchors.verticalCenter: parent.verticalCenter
        sourceComponent: radioItem
    }

    contentItem: Text {
        id: mText
        height: parent.availableHeight
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: qextRadioButton.textInLeft ? qextRadioButton.leftInset + qextRadioButton.leftPadding :
                                                         qextRadioButton.leftInset + qextRadioButton.leftPadding * 2 + qextRadioButton.availableHeight
        anchors.rightMargin: qextRadioButton.textInLeft ? qextRadioButton.rightInset + qextRadioButton.rightPadding * 2 + qextRadioButton.availableHeight:
                                                          qextRadioButton.rightInset + qextRadioButton.rightPadding
        anchors.verticalCenter: parent.verticalCenter
        text: qextRadioButton.text
        font: qextRadioButton.textFont
        opacity: qextRadioButton.textOpacity
        color: qextRadioButton.textColor
        horizontalAlignment: qextRadioButton.textHorizontalAlignment
        verticalAlignment: qextRadioButton.textVerticalAlignment
        elide: qextRadioButton.textElide
        Binding {
            target: mPrivate
            property: "textContentWidth"
            value: mText.contentWidth
        }
    }
    background: Rectangle {
        anchors.fill: parent
        color: qextRadioButton.backgroundColor
        visible: qextRadioButton.backgroundVisiable
        opacity: qextRadioButton.backgroundOpacity
        border.color: qextRadioButton.backgroundBorderColor
        border.width: qextRadioButton.backgroundBorderWidth
        radius: qextRadioButton.backgroundRadius
    }

    readonly property Component radioFlatItem: Rectangle {
        width: height
        radius: height / 2
        color: qextRadioButton.backgroundColor
        border.color: qextRadioButton.indicatorColor
        border.width: height / 10

        Rectangle {
            width: qextRadioButton.checked ? parent.height / 10 * 6 : 0
            height: width
            radius: width / 2
            anchors.centerIn: parent
            color: qextRadioButton.indicatorColor
            border.width: 0
            Behavior on width {
                NumberAnimation {
                    duration: 200
                }
            }
        }
    }

    readonly property Component radioAnimatorItem: Rectangle {
        width: height
        radius: width / 2
        color: qextRadioButton.backgroundColor
        border.color: qextRadioButton.indicatorColor
        border.width: height / 10

        Rectangle {
            id: mBg
            width: 0
            height: width
            radius: height / 2
            anchors.centerIn: parent
            opacity: 0.5
            color: Qt.lighter(qextRadioButton.indicatorColor, 1.5)
            border.width: 0
            Connections {
                target: qextRadioButton
                function onHoveredChanged() {
                    if (qextRadioButton.hovered) {
                        mBg.width = qextRadioButton.textInLeft ? qextRadioButton.leftPadding * 2 + qextRadioButton.availableHeight :
                                                                 qextRadioButton.rightPadding * 2 + qextRadioButton.availableHeight
                    } else {
                        mBg.width = 0
                    }
                }
            }
            Behavior on width {
                NumberAnimation {
                    duration: 500
                }
            }
        }

        Rectangle {
            width: qextRadioButton.checked ? parent.height / 10 * 6 : 0
            height: width
            radius: width / 2
            anchors.centerIn: parent
            color: qextRadioButton.indicatorColor
            border.width: 0
            Behavior on width {
                NumberAnimation {
                    duration: 200
                }
            }
        }
    }

    QtObject {
        id: mPrivate
        property real textContentWidth: 0
        property real implicitAvailableWidth: qextRadioButton.textInLeft ? textContentWidth + qextRadioButton.rightPadding + qextRadioButton.availableHeight :
                                                                           textContentWidth + qextRadioButton.leftPadding + qextRadioButton.availableHeight
    }
    onTextFontChanged: {
        qextRadioButton.font = qextRadioButton.textFont
    }
    onCheckedChanged: {
        qextRadioButton.state = qextRadioButton.checked ? QEXTQmlQuick.stateToString(QEXTQmlQuick.State_Checked) :
                                                          QEXTQmlQuick.stateToString(QEXTQmlQuick.State_Unchecked)
    }


}
