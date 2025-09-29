import QtQuick 2.6

import QExtQml 1.4
import QExtQml.Theme 1.4
import QExtQuick.Controls 1.4

QExtQuickButtonArea {
    id: mControl;
    checkable: true
    width: content.width + padding
    height: content.height + padding

    property int padding: 6

    property alias theme: mTheme
    property alias dot: mDotInfo
    property color activeColor: "#46A0FC"
    property alias background: mBackgroundInfo

    property Component dotComponent;
    property Component backgroundComponent;

    backgroundComponent: Rectangle {
        color: checked ? activeColor : mBackgroundInfo.color
        width: mBackgroundInfo.width
        height: mBackgroundInfo.height
        radius: mBackgroundInfo.radius
        border.width: 1;
        border.color: Qt.darker(color,1.1)
    }

    dotComponent: Item {
        width:  mDotInfo.width;
        height: mDotInfo.height;

        Rectangle{
            anchors.fill: parent;
            anchors.margins: 2;
            color: mDotInfo.color;
            radius: mDotInfo.radius;
        }
    }

    QExtQmlRectangleInfo {
        id: mBackgroundInfo
        width: 40
        height: 20
        color: "#F36D6F"
        radius: height / 2
    }

    QExtQmlRectangleInfo {
        id: mDotInfo;
        width: 20
        height: 20
        radius: height / 2
    }

    Item {
        id: content
        anchors.centerIn: parent
        width: Math.max(backgroundLoader.width,dotloader.width)
        height: Math.max(backgroundLoader.height,dotloader.height)

        Loader {
            id: backgroundLoader
            sourceComponent: backgroundComponent
            anchors.verticalCenter: parent.verticalCenter
        }

        Loader {
            id:dotloader;
            sourceComponent: dotComponent
            anchors.verticalCenter: parent.verticalCenter
            x: checked ? content.width - width : 0
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
            childName: "background"
            target: mBackgroundInfo

            property int width: mBackgroundInfo.width
            property int height: mBackgroundInfo.height
            property int radius: mBackgroundInfo.radius
            property color color: mBackgroundInfo.color
        }

        QExtQmlThemeBinder {
            childName: "activeColor"
            target: mControl

            property color color: activeColor
        }

        QExtQmlThemeBinder {
            childName: "dot"
            target: mDotInfo

            property int width: mDotInfo.width
            property int height: mDotInfo.height
            property int radius: mDotInfo.radius
            property color color: mDotInfo.color
        }

        Component.onCompleted: initialize();
    }

}
