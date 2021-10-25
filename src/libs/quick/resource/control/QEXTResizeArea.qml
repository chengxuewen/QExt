import QtQuick 2.12
import QtQuick.Window 2.2
import QEXTQuick 1.2

Item {
    id: qextResizeArea
    anchors.fill: parent
    focus: true

    property var control: parent
    property int enableSize: 4
    property bool isPressed: false
    property point customPoint

    Item {
        id: mLeftTopItem
        width: enableSize
        height: enableSize
        anchors.left: parent.left
        anchors.top: parent.top
        z: 10000
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.SizeFDiagCursor

            onPressed: press(mouse)
            onReleased: release()
            onPositionChanged: positionChange(mouse, -1, -1)
        }
    }

    Item {
        id: mTopItem
        height: enableSize
        anchors.left: mLeftTopItem.right
        anchors.right: mRightTopItem.left
        anchors.top: parent.top
        z: 10000
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.SizeVerCursor

            onPressed: press(mouse)
            onReleased: release()
            onMouseYChanged: positionChange(Qt.point(customPoint.x, mouseY), 1, -1)
        }
    }

    Item {
        id: mRightTopItem
        width: enableSize
        height: enableSize
        anchors.right: parent.right
        anchors.top: parent.top
        z: 10000
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.SizeBDiagCursor

            onPressed: press(mouse)
            onReleased: release()
            onPositionChanged: positionChange(mouse, 1, -1)
        }
    }

    Item {
        id: mLeftItem
        width: enableSize
        anchors.left: parent.left
        anchors.top: mLeftTopItem.bottom
        anchors.bottom: mLeftBottomItem.top
        z: 10000
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.SizeHorCursor

            onPressed: press(mouse)
            onReleased: release()
            onMouseXChanged: positionChange(Qt.point(mouseX, customPoint.y), -1, 1)
        }
    }

    Item {
        id: mRightItem
        width: enableSize
        anchors.right: parent.right
        anchors.top: mRightTopItem.bottom
        anchors.bottom: mRightBottomItem.top
        z: 10000
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.SizeHorCursor

            onPressed: press(mouse)
            onReleased: release()
            onMouseXChanged: positionChange(Qt.point(mouseX, customPoint.y), 1, 1)
        }
    }

    Item {
        id: mLeftBottomItem
        width: enableSize
        height: enableSize
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        z: 10000
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.SizeBDiagCursor

            onPressed: press(mouse)
            onReleased: release()
            onPositionChanged: positionChange(mouse, -1, 1)
        }
    }

    Item {
        id: mBottomItem
        height: enableSize
        anchors.left: mLeftBottomItem.right
        anchors.right: mRightBottomItem.left
        anchors.bottom: parent.bottom
        z: 10000
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.SizeVerCursor

            onPressed: press(mouse)
            onReleased: release()
            onMouseYChanged: positionChange(Qt.point(customPoint.x, mouseY), 1, 1)
        }
    }

    Item {
        id: mRightBottomItem
        width: enableSize
        height: enableSize
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        z: 10000
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.SizeFDiagCursor

            onPressed: press(mouse)
            onReleased: release()
            onPositionChanged: positionChange(mouse,1,1)
        }
    }

    function press(mouse) {
        isPressed = true
        customPoint = Qt.point(mouse.x, mouse.y)
    }

    function release() {
        isPressed = false
    }

    function positionChange(newPosition, directX, directY) {
        if (!isPressed) {
            return
        }

        var delta = Qt.point(newPosition.x - customPoint.x, newPosition.y - customPoint.y)
        var tmpW, tmpH

        if (directX >= 0) {
            tmpW = control.width + delta.x
        } else {
            tmpW = control.width - delta.x
        }
        if (directY >= 0) {
            tmpH = control.height + delta.y
        } else {
            tmpH = control.height - delta.y
        }
        if (tmpW < control.minimumWidth) {
            if (directX < 0) {
                control.x += (control.width - control.minimumWidth)
            }
            control.width = control.minimumWidth
        } else {
            control.width = tmpW
            if (directX < 0) {
                control.x += delta.x
            }
        }

        if (tmpH < control.minimumHeight) {
            if (directY < 0) {
                control.y += (control.height - control.minimumHeight)
            }
            control.height = control.minimumHeight
        } else {
            control.height = tmpH
            if (directY < 0) {
                control.y += delta.y
            }
        }
    }
}
