import QtQuick 2.12
import QtQml 2.12
import QEXTQuick 1.0

Item {
    id: qextBusyIndicator
    width: contentWidth + padding
    height: contentWidth + padding

    readonly property int contentWidth: mContentLoader.width
    readonly property int contentHeight: mContentLoader.height

    property int padding: 5
    property int  duration: 500

    property alias icon: mIconGadget
    property alias color: mIconGadget.color
    property alias running: qextBusyIndicator.visible

    property Component contentItem: contentIconAnimatorItem

    QEXTQuickIconGadget {
        id: mIconGadget
        source: QEXTQuickFontAwesome.FA_circle_o_notch
        color: "#5D5D5D"
    }

    Loader {
        id: mContentLoader
        anchors.centerIn: parent
        sourceComponent: contentItem
    }

    readonly property Component contentIconAnimatorItem: QEXTAwesomeIcon {
        source: icon.source
        color: icon.color
        width: 26
        height: 26
        RotationAnimator on rotation {
            from: 0
            to: 360
            duration: qextBusyIndicator.duration
            running: qextBusyIndicator.visible
            loops: Animation.Infinite
        }
    }

    readonly property Component contentDotAnimatorItem: Row {
        id: mContentLayoutComponent
        spacing: 5
        Repeater {
            model: 3
            delegate: Rectangle {
                width: 12
                height: 12
                radius: 6
                color: qextBusyIndicator.color
                property bool animrun: false
                SequentialAnimation on scale {
                    running: animrun
                    loops: Animation.Infinite
                    ScaleAnimator {
                        from: 1
                        to: 0.2
                        duration:600
                    }
                    ScaleAnimator {
                        from: 0.2
                        to: 1
                        duration:600
                    }
                }
            }
        }

        Timer {
            id: delay
            interval: 200
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

        Component.onCompleted: delay.start()
    }
}
