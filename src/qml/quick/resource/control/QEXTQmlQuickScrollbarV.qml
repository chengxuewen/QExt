import QtQuick 2.9
import QtQml 2.9

/*
Qt ListView ，Qt Flickable
 TScrllbarV{
    target:listView
 }
*/
Item {
    id: qextScrollbarV
    width: 22

    property Flickable target: parent
    //0 - 1
    property double yPosition: 0
    property bool narrowed: true
    property bool autoHide: false
    property bool autoScroll: false
    //Too small a height affects drag accuracy
    property int thumbMinHieght: 30
    property int stateDuration: 1000
    readonly property alias thumbHieght: mThumbLoader.height
    property alias trackVisible: mTrackLoader.visible
    property alias thumbVisible: mThumbLoader.visible

    property Component thumbComponent
    property Component trackComponent

    state: narrowed ? "narrowed" : "full"

    Loader {
        id: mTrackLoader
        anchors.right: parent.right
        sourceComponent: trackComponent
        height: parent.height
//        visible: mgadgettrack.visible
    }

    Loader {
        id: mThumbLoader
        anchors.horizontalCenter: mTrackLoader.horizontalCenter
        sourceComponent: thumbComponent
        height: thumbMinHieght
    }

    MouseArea{
        id: mMouseArea
        width: parent.width
        height: parent.height
        hoverEnabled: true

        property bool ishold: false
        property bool isdrag: false
        property double offset: 0

        onPressed: {
            ishold = true
            if (mouseY > mThumbLoader.y && mouseY < mThumbLoader.height + mThumbLoader.y) {
                offset = mouseY - mThumbLoader.y
                isdrag = true
            } else {
                mPrivate.setValue(mouseY - mThumbLoader.height / 2)
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
            qextScrollbarV.state = "full"
            mStateTimer.stop()
        }

        onExited: {
            if (!ishold) {
                mStateTimer.rStart()
            }
        }

        onMouseYChanged: {
            if (ishold && isdrag) {
                mPrivate.setValue(mouseY - offset)
            }
        }

        Component.onCompleted: {
            mPrivate.checkVisible()
        }

        onIsholdChanged: target.interactive = !ishold
    }

    onYPositionChanged: {
        if (mMouseArea.ishold) {//drag interior setting
            target.contentY = (target.contentHeight - target.height) * yPosition
        }
    }

    Connections {
        target: qextScrollbarV.target
        onContentYChanged: {
            if (!mMouseArea.ishold) {
                var t = qextScrollbarV.target
                var p = t.contentY / (t.contentHeight - t.height)
                mPrivate.setValue(p * (height - mThumbLoader.height))
            }

            mPrivate.restoreVisibleState()
        }

        onContentHeightChanged: {
            var t  = qextScrollbarV.target
            var nh = t.height / t.contentHeight * qextScrollbarV.height
            if (nh > thumbMinHieght) {
                mThumbLoader.height = nh
            }
            mPrivate.checkVisible()
            if (autoScroll) {
                yPosition = 1
                if (target.contentHeight > target.height) {
                    target.contentY = (target.contentHeight - target.height) * yPosition
                }
            }
        }

        onHeightChanged: mPrivate.checkVisible()
    }

    QtObject {
        id: mPrivate

        function setValue(v) {
            if (v < 0) {
                mThumbLoader.y = 0
            } else if (v + mThumbLoader.height > height){
                mThumbLoader.y = height - mThumbLoader.height
            } else {
                mThumbLoader.y = v
            }

            yPosition = mThumbLoader.y / (height -  mThumbLoader.height)
        }

        function checkVisible() {
            var t = qextScrollbarV.target
            if (t) {
                qextScrollbarV.visible = t.contentHeight > t.height
                qextScrollbarV.enabled = qextScrollbarV.visible
            }
        }

        function restoreVisibleState() {
            if (!mMouseArea.containsMouse && !mMouseArea.ishold && !mStateTimer.running) {
                if (qextScrollbarV.narrowed) {
                    qextScrollbarV.state = "narrowed"
                } else {
                    qextScrollbarV.state = "full"
                }
                mStateTimer.rStart()
            }
        }
    }


    trackComponent: Rectangle {
        id: mTrack
        state: qextScrollbarV.state
        color: "#E5E5E5"
        opacity: 0.1
        states: [
            State {
                name: "full"
                PropertyChanges {
                    target: mTrack
                    color:"#5d5d5d"
                    width: 15
                }
            },
            State {
                name: "narrowed"
                PropertyChanges {
                    target: mTrack
                    width:5
                    visible:false
                }
            },
            State {
                name: "hide"
                PropertyChanges {
                    target: mTrack
                    visible:false
                }
            }
        ]
    }

    thumbComponent: Rectangle{
        id: mThumb
        state: qextScrollbarV.state
        radius: width / 2
        color: "#B2B2B2"
        states: [
            State {
                name: "full"
                PropertyChanges {
                    target: mThumb
                    width: 8
                }
            },
            State {
                name: "narrowed"
                PropertyChanges {
                    target: mThumb
                    width: 3
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
        repeat : true
        onTriggered: {
            if (qextScrollbarV.state === "full") {
                if (qextScrollbarV.narrowed) {
                    qextScrollbarV.state = "narrowed"
                } else if (qextScrollbarV.autoHide) {
                    qextScrollbarV.state = "hide"
                }
            } else if (qextScrollbarV.state === "narrowed") {
                if (qextScrollbarV.autoHide) {
                    qextScrollbarV.state = "hide"
                }
            }

            if (qextScrollbarV.state === "hide") {
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
