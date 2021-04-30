import QtQuick 2.7
import QtQuick.Window 2.2
import QEXTQuick 1.2

MouseArea {
    id: qextMoveArea
    anchors.fill: parent
    acceptedButtons: Qt.LeftButton

    property var control: parent
    property point clickPos: "0, 0"
    property bool moveEnable: true
    property int defaultCursorShape: Qt.ArrowCursor

    Component.onCompleted: {
        defaultCursorShape = qextMoveArea.cursorShape
    }
    onPressed: {
        clickPos = Qt.point(mouse.x, mouse.y)
    }
    onReleased: {
        qextMoveArea.cursorShape = defaultCursorShape
    }
    onPositionChanged: {
        if (qextMoveArea.pressed) {
            moveControl(mouse)
        }
    }

    function moveControl(mouse) {
        var enable = (qextRootWindow === control) ? Window.Maximized !== qextRootWindow.visibility : true
        if (moveEnable && enable) {
            if (moveEnable) {
                var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
                control.x += delta.x
                control.y += delta.y
                qextMoveArea.cursorShape = Qt.SizeAllCursor
            }
        }
    }
}
