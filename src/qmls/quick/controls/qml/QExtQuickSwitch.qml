import QtQuick 2.6

import QExtQml 1.4
import QExtQml.Theme 1.4
import QExtQuick.Controls 1.4

QExtQuickButtonArea {
    id: mControl
    width: 60
    height: 40
    checkable: true

    property int padding: 6
    property int radius: (height - padding * 2) / 2

    property alias theme: mTheme

    property alias dot: mDotInfo
    property alias background: mBackgroundInfo
    property alias contentVisible: mContentLoader.visible
    property alias checkedBackground: mCheckedBackgroundInfo

    property Component dotComponent;
    property Component contentComponent;
    property Component backgroundComponent;

    backgroundComponent: Rectangle {
        color: checked ? mCheckedBackgroundInfo.color : mBackgroundInfo.color
        radius: checked ? mCheckedBackgroundInfo.radius : mBackgroundInfo.radius
        opacity: checked ? mCheckedBackgroundInfo.opacity : mBackgroundInfo.opacity
        anchors.fill: parent
        border.width: 1;
        border.color: Qt.darker(color,1.1)
    }

    contentComponent: Item {
        anchors.fill: parent
        Text {
            text: "On"
            visible: mControl.checked
            anchors.left: parent.left
            anchors.leftMargin: 5
            verticalAlignment: Text.AlignLeft
            anchors.verticalCenter: parent.verticalCenter
        }
        Text {
            text: "OFF"
            visible: !mControl.checked
            anchors.right: parent.right
            anchors.rightMargin: 5
            verticalAlignment: Text.AlignRight
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    dotComponent: Item {
        width: parent.height
        height: parent.height
        opacity: mDotInfo.opacity

        Rectangle {
            anchors.fill: parent
            anchors.margins: 2
            color: mDotInfo.color
            radius: mDotInfo.radius
        }
    }

    QExtQmlBackgroundInfo {
        id: mCheckedBackgroundInfo
        color: "#6AC044"
        radius: mControl.radius
    }

    QExtQmlBackgroundInfo {
        id: mBackgroundInfo
        color: "#909399"
        radius: mControl.radius
    }

    QExtQmlBackgroundInfo {
        id: mDotInfo
        color: "#FFFFFF"
        radius: mControl.radius
    }

    Item {
        id: mContent
        anchors.fill: parent
        anchors.margins: mControl.padding

        Loader {
            id: mBackgroundLoader
            anchors.fill: parent
            sourceComponent: backgroundComponent
        }

        Loader {
            id: mContentLoader
            visible: false
            anchors.fill: parent
            sourceComponent: visible ? contentComponent : null
        }

        Loader {
            id: mDotloader
            width: parent.height
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            sourceComponent: dotComponent
            x: checked ? mContent.width - width : 0
            Behavior on x {
                NumberAnimation {
                    duration: 80
                }
            }
        }
    }

    QExtQmlThemeBinder {
        id: mTheme
        className: "QExtQuickSwitch"

        QExtQmlThemeBinder {
            childName: "Background"
            target: mBackgroundInfo

            property color color: mBackgroundInfo.color
            property int radius: mBackgroundInfo.radius
            property int opacity: mBackgroundInfo.opacity
        }

        QExtQmlThemeBinder {
            childName: "CheckedBackground"
            target: mCheckedBackgroundInfo

            property color color: mCheckedBackgroundInfo.color
            property int radius: mCheckedBackgroundInfo.radius
            property int opacity: mCheckedBackgroundInfo.opacity
        }

        QExtQmlThemeBinder {
            childName: "Dot"
            target: mDotInfo

            property color color: mDotInfo.color
            property int radius: mDotInfo.radius
            property int opacity: mDotInfo.opacity
        }

        Component.onCompleted: initialize();
    }

}
