import QtQml 2.9
import QtQuick 2.9
import QtQuick.Controls 2.9

Item {
    id: root
    width: mContentItemLoader.width + 5
    height: mContentItemLoader.height + 5

    readonly property alias fps: mData.fps
    readonly property alias fpsAvg: mData.fpsAvg

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
        id: mData
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
        onRotationChanged: mData.frameCounter++
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
            mData.frameCounterAvg += mData.frameCounter
            mData.fps = mData.frameCounter/2
            mData.counter++
            mData.frameCounter = 0
            if (mData.counter >= 3) {
                mData.fpsAvg = mData.frameCounterAvg/(2 * mData.counter)
                mData.frameCounterAvg = 0
                mData.counter = 0
            }
        }
    }
}

