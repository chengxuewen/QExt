import QtQuick 2.12
import QtQml 2.12

/*
Qt ListView ，Qt Flickable
 QEXTScrllbarV{
    target:listView
 }
*/
Item {
    id: qextScrollbarH
    height: 22
    state: narrowed ? "narrowed" : "full"

    property Flickable target: parent
    //0 - 1
    property double xPosition: 0
    property bool narrowed: true
    property bool autoHide: false
    property bool autoScroll: false
    property int thumbMinWidth: 30
    property int stateDuration: 1000

    property alias thumbVisible: mThumbLoader.visible
    property alias trackVisible: mTrackLoader.visible

    property Component thumbComponent
    property Component trackComponent

    Loader {
        id: mTrackLoader
        anchors.bottom: parent.bottom
        sourceComponent: trackComponent
        width: parent.width
    }

    Loader {
        id: mThumbLoader
        anchors.verticalCenter: mTrackLoader.verticalCenter
        sourceComponent: thumbComponent
        width: thumbMinWidth
    }

    MouseArea {
        id: mMouseArea
        anchors.fill: parent
        hoverEnabled: true

        property bool ishold: false
        property bool isdrag: false
        property double offset: 0

        onWheel: {

        }

        onPressed: {
            ishold = true
            if (mouseX > mThumbLoader.x && mouseX < mThumbLoader.width + mThumbLoader.x) {
                offset  = mouseX - mThumbLoader.x
                isdrag = true
            } else {
                mPrivate.setValue(mouseX - mThumbLoader.width / 2)
            }
        }

        onReleased: {
            ishold = false
            isdrag = false
            if (!containsMouse) {
                mStateTimer.rStart()
            }
        }

        onEntered: {
            qextScrollbarH.state = "full"
            mStateTimer.stop()
        }

        onExited: {
            if (!ishold) {
                mStateTimer.rStart()
            }
        }

        onMouseXChanged: {
            if (ishold && isdrag) {
                mPrivate.setValue(mouseX - offset)
            }
        }

        Component.onCompleted: {
            mPrivate.checkVisible()
        }

        onIsholdChanged: target.interactive = !ishold
    }

    onXPositionChanged: {
        if (mMouseArea.ishold) {//drag interior setting
            target.contentX = (target.contentWidth - target.width) * xPosition
        }
    }

    Connections {
        target: qextScrollbarH.target
        onContentXChanged: {
            if (!mMouseArea.ishold) {
                var t = qextScrollbarH.target
                var p = t.contentX / (t.contentWidth - t.width)
                mPrivate.setValue(p * (width - mThumbLoader.width))
            }

            mPrivate.restoreVisibleState()
        }

        onContentWidthChanged: {
            var t  = qextScrollbarH.target
            var nh = t.width / t.contentWidth * qextScrollbarH.width
            if(nh > thumbMinWidth){
                mThumbLoader.width = nh
            }
            mPrivate.checkVisible()
            if (autoScroll) {
                xPosition = 1
                if (target.contentWidth > target.width) {
                    target.contentX = (target.contentWidth - target.width) * xPosition
                }
            }
        }

        onWidthChanged:mPrivate.checkVisible()
    }

    QEXTQmlQuickObject {
        id: mPrivate

        function setValue(v) {
            if(v < 0) {
                mThumbLoader.x = 0
            } else if (v + mThumbLoader.width > width){
                mThumbLoader.x = width - mThumbLoader.width
            } else {
                mThumbLoader.x = v
            }

            xPosition = mThumbLoader.x / (width -  mThumbLoader.width)
        }

        function checkVisible() {
            var t = qextScrollbarH.target
            if (t) {
                qextScrollbarH.visible = t.contentWidth > t.width
                qextScrollbarH.enabled = qextScrollbarH.visible
            }
        }

        function restoreVisibleState() {
            if (!mMouseArea.containsMouse && !mMouseArea.ishold && !mStateTimer.running) {
                if (qextScrollbarH.narrowed) {
                    qextScrollbarH.state = "narrowed"
                } else {
                    qextScrollbarH.state = "full"
                }
                mStateTimer.rStart()
            }
        }
    }


    trackComponent: Rectangle {
        id: mTrack
        state: qextScrollbarH.state
        color: "#E5E5E5"
        opacity: 0.1
        states: [
            State {
                name: "full"
                PropertyChanges {
                    target: mTrack
                    color:"#5d5d5d"
                    height: 15
                }
            },
            State {
                name: "narrowed"
                PropertyChanges {
                    target: mTrack
                    height: 5
                    visible: false
                }
            },
            State {
                name: "hide"
                PropertyChanges {
                    target: mTrack
                    visible: false
                }
            }
        ]
    }

    thumbComponent: Rectangle {
        id: mThumb
        state: qextScrollbarH.state
        radius: width / 2
        color: "#B2B2B2"
        states: [
            State {
                name: "full"
                PropertyChanges {
                    target: mThumb
                    height: 8
                }
            },
            State {
                name: "narrowed"
                PropertyChanges {
                    target: mThumb
                    height: 3
                }
            },
            State {
                name: "hide"
                PropertyChanges {
                    target: mThumb
                    visible: false
                }
            }
        ]
    }

    Timer {
        id: mStateTimer
        property bool isrun: narrowed || autoHide
        interval: stateDuration
        running: isrun
        repeat: true
        onTriggered: {
            if (qextScrollbarH.state === "full") {
                if (qextScrollbarH.narrowed) {
                    qextScrollbarH.state = "narrowed"
                } else if (qextScrollbarH.autoHide) {
                    qextScrollbarH.state = "hide"
                }
            } else if (qextScrollbarH.state === "narrowed") {
                if(qextScrollbarH.autoHide){
                    qextScrollbarH.state = "hide"
                }
            }

            if (qextScrollbarH.state === "hide") {
                stop()
            }
        }

        function rStart() {
            if (isrun) {
                restart()
            }
        }
    }
}
