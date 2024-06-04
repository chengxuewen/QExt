import QtQuick 2.12
import QtQml 2.12
import QtQuick.Controls 2.12
import QExtQuick 1.2

Switch {
    id: qextSwitch
    implicitWidth: leftInset + rightInset + leftPadding + rightPadding + mPrivate.implicitAvailableWidth
    implicitHeight: 30
    checkable: true
    checked: false
    opacity: qextSwitch.enabled ? 1.0 : 0.5
    padding: 5

    property bool textInLeft: false
    property font textFont: qextSwitch.font
    property color textColor: QExtQuickPalette.textPrimaryColor
    property real textOpacity: 1
    property int textHorizontalAlignment: Text.AlignHCenter
    property int textVerticalAlignment: Text.AlignVCenter
    property int textElide: Text.ElideRight
    property real textSpace: 5

    property color trackColor: qextSwitch.checked ? QExtQuickPalette.brandPositiveColor : QExtQuickPalette.brandNegativeColor
    property color trackBorderColor: trackColor
    property real trackBorderWidth: 1

    property color thumbColor: "#FFFFFF"
    property color thumbBorderColor: thumbColor
    property real thumbBorderWidth: 1
    property string thumbIconSource

    property Component thumbIconItem
    property Component switchItem: switchCircleInItem

    background: null
    indicator: Loader {
        x: qextSwitch.textInLeft ? qextSwitch.width - qextSwitch.rightPadding - mPrivate.trackWidth :
                                   qextSwitch.leftPadding
        width: mPrivate.trackWidth
        anchors.verticalCenter: parent.verticalCenter
        sourceComponent: switchItem
    }
    contentItem: Text {
        id: mText
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: qextSwitch.textInLeft ? 0 : mPrivate.trackWidth + qextSwitch.textSpace
        anchors.rightMargin: qextSwitch.textInLeft ? mPrivate.trackWidth + qextSwitch.textSpace : 0
        width: parent.availableWidth - mPrivate.trackWidth - qextSwitch.textSpace
        height: parent.availableHeight
        anchors.verticalCenter: parent.verticalCenter
        text: qextSwitch.text
        font: qextSwitch.textFont
        opacity: qextSwitch.textOpacity
        color: qextSwitch.textColor
        horizontalAlignment: qextSwitch.textHorizontalAlignment
        verticalAlignment: qextSwitch.textVerticalAlignment
        elide: qextSwitch.textElide
        Binding {
            target: mPrivate
            property: "textImplicitWidth"
            value: mText.implicitWidth
        }
    }

    readonly property Component switchRectInItem: Rectangle {
        height: qextSwitch.availableHeight
        radius: height / 4
        color: qextSwitch.trackColor
        border.color: qextSwitch.trackBorderColor
        border.width: qextSwitch.trackBorderWidth

        Rectangle {
            x: qextSwitch.checked ? parent.width - width - parent.height / 10 : parent.height / 10
            width: parent.height / 10 * 8
            height: width
            radius: width / 4
            anchors.verticalCenter: parent.verticalCenter
            color: qextSwitch.thumbColor
            border.color: qextSwitch.thumbBorderColor
            border.width: qextSwitch.thumbBorderWidth
            Behavior on x {
                NumberAnimation {
                    duration: 200
                }
            }
        }
    }

    readonly property Component switchRectOutItem: Rectangle {
        height: qextSwitch.availableHeight / 4 * 3
        radius: height / 4
        color: qextSwitch.trackColor
        border.color: qextSwitch.trackBorderColor
        border.width: qextSwitch.trackBorderWidth

        Rectangle {
            x: qextSwitch.checked ? parent.width - width : 0
            width: parent.height / 4 * 6
            height: width
            radius: width / 4
            anchors.verticalCenter: parent.verticalCenter
            color: qextSwitch.thumbColor
            border.color: qextSwitch.thumbBorderColor
            border.width: qextSwitch.thumbBorderWidth
            Behavior on x {
                NumberAnimation {
                    duration: 200
                }
            }
        }
    }

    readonly property Component switchCircleInItem: Rectangle {
        height: qextSwitch.availableHeight
        radius: height / 2
        color: qextSwitch.trackColor
        border.color: qextSwitch.trackBorderColor
        border.width: qextSwitch.trackBorderWidth

        Rectangle {
            x: qextSwitch.checked ? parent.width - width - parent.height / 10 : parent.height / 10
            width: parent.height / 10 * 8
            height: width
            radius: width / 2
            anchors.verticalCenter: parent.verticalCenter
            color: qextSwitch.thumbColor
            border.color: qextSwitch.thumbBorderColor
            border.width: qextSwitch.thumbBorderWidth
            Behavior on x {
                NumberAnimation {
                    duration: 200
                }
            }
        }
    }

    readonly property Component switchCircleOutItem: Rectangle {
        height: qextSwitch.availableHeight / 4 * 3
        radius: height / 2
        color: qextSwitch.trackColor
        border.color: qextSwitch.trackBorderColor
        border.width: qextSwitch.trackBorderWidth

        Rectangle {
            x: qextSwitch.checked ? parent.width - width : 0
            width: parent.height / 4 * 6
            height: width
            radius: width / 2
            anchors.verticalCenter: parent.verticalCenter
            color: qextSwitch.thumbColor
            border.color: qextSwitch.thumbBorderColor
            border.width: qextSwitch.thumbBorderWidth
            Behavior on x {
                NumberAnimation {
                    duration: 200
                }
            }
        }
    }

    QtObject {
        id: mPrivate
        property real trackWidth: qextSwitch.availableHeight * 2
        property real textImplicitWidth: 0
        property real implicitAvailableWidth: textImplicitWidth > 0 ? trackWidth + textImplicitWidth + qextSwitch.textSpace :
                                                                      trackWidth
    }

    onCheckedChanged: {
        qextSwitch.state = qextSwitch.checked ? QExtQuick.stateToString(QExtQuick.State_Checked) :
                                                QExtQuick.stateToString(QExtQuick.State_Unchecked)
    }
}

