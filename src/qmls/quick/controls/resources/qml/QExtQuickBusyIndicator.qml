import QtQml 2.9
import QtQuick 2.9

import QExtQuick.Controls 1.3

Item {
    id: root
    width: contentWidth + padding
    height: contentWidth + padding

    readonly property int contentWidth: mContentLoader.width
    readonly property int contentHeight: mContentLoader.height

    property int padding: 5
    property int  duration: 1000

    property alias icon: mIconGadget
    property alias color: mIconGadget.color
    property alias running: root.visible

    property Component contentItem: iconAnimatorComponent

    QExtQuickIconGadget {
        id: mIconGadget
        source: "qrc:/QExtQuickControls/image/loading.svg"
        color: "#5D5D5D"
    }

    Loader {
        id: mContentLoader
        anchors.centerIn: parent
        sourceComponent: contentItem
    }

    readonly property Component iconAnimatorComponent: QExtQuickImage {
        source: icon.source
        color: icon.color
        width: 26
        height: 26
        RotationAnimator on rotation {
            from: 0
            to: 360
            duration: root.duration
            running: root.visible
            loops: Animation.Infinite
        }
    }

    readonly property Component dotAnimatorComponent: Row {
        id: mContentLayoutComponent
        spacing: 5
        Repeater {
            model: 3
            delegate: Rectangle {
                width: 12
                height: 12
                radius: 6
                color: root.color
                property bool animrun: false
                SequentialAnimation on scale {
                    running: animrun
                    loops: Animation.Infinite
                    ScaleAnimator {
                        from: 1
                        to: 0.2
                        duration:root.duration
                    }
                    ScaleAnimator {
                        from: 0.2
                        to: 1
                        duration:root.duration
                    }
                }
            }
        }

        Timer {
            id: delayTimer
            interval: 100
            repeat: true
            property int count: mContentLayoutComponent.children.length
            property int i: 0
            onTriggered: {
                if (mContentLayoutComponent.children[i].animrun !== "undefined") {
                    mContentLayoutComponent.children[i].animrun = true
                }
                if (++i >= count - 1) {
                    stop()
                }
            }
        }

        Component.onCompleted: delayTimer.start()
    }
}
