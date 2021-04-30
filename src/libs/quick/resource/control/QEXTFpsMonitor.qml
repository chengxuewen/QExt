import QtQuick 2.7
import QtQuick.Controls 2.12

Item {
    id: qextFpsMonitor
    width: mContentItemLoader.width + 5
    height: mContentItemLoader.height + 5

    readonly property alias fps: mPrivate.fps
    readonly property alias fpsAvg: mPrivate.fpsAvg

    property color color: "#C0C0C0"
    property Component contentItem: contentComponent

    Component {
        id: contentComponent
        Label {
            font.pixelSize: 10
            font.bold: true
            text: " Avg " + fpsAvg + " | " + fps + " Fps"
        }
    }

    QtObject {
        id: mPrivate
        property int frameCounter: 0
        property int frameCounterAvg: 0
        property int counter: 0
        property int fps: 0
        property int fpsAvg: 0
    }

    Rectangle {
        id: mMonitorRect
        radius: 3
        width: 6
        height: width
        opacity: 0

        NumberAnimation on rotation {
            from: 0
            to: 360
            duration: 800
            loops: Animation.Infinite
        }
        onRotationChanged: mPrivate.frameCounter++
    }

    Loader{
        id: mContentItemLoader
        sourceComponent: contentItem
    }

    Timer {
        interval: 2000
        repeat: true
        running: visible
        onTriggered: {
            mPrivate.frameCounterAvg += mPrivate.frameCounter
            mPrivate.fps = mPrivate.frameCounter/2
            mPrivate.counter++
            mPrivate.frameCounter = 0
            if (mPrivate.counter >= 3) {
                mPrivate.fpsAvg = mPrivate.frameCounterAvg/(2 * mPrivate.counter)
                mPrivate.frameCounterAvg = 0
                mPrivate.counter = 0
            }
        }
    }
}

