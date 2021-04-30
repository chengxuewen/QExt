import QtQuick 2.7
import QtQml 2.12
import QtQuick.Window 2.2
import QEXTQuick 1.2

Window {
    id: root
    contentItem.clip: true
    visible: true
    flags: framelessEnable ? Qt.Window | Qt.FramelessWindowHint : Qt.Window
    x: (Screen.desktopAvailableWidth - width) / 2
    y: (Screen.desktopAvailableHeight - height) / 2

    property real resizeHandlerSize: 5
    property real resizeHandlerZValue: 1000
    property bool resizeEnable: true
    property bool framelessEnable: true

    MouseArea {
        id: mLeftTopResizeHandler
        visible: root.resizeEnable && root.framelessEnable
        enabled: root.resizeEnable && root.framelessEnable
        width: root.resizeHandlerSize
        height: root.resizeHandlerSize
        anchors.left: root.contentItem.left
        anchors.top: root.contentItem.top
        z: root.resizeHandlerZValue
        hoverEnabled: true
        cursorShape: Qt.SizeFDiagCursor
        onPressed: mPrivate.resizeHandlerPressed(QEXTQuick.DragDirection_LeftTop, mapToGlobal(mouseX, mouseY))
        onReleased: mPrivate.resizeHandlerReleased(QEXTQuick.DragDirection_LeftTop)
        onPositionChanged: mPrivate.positionChange(mapToGlobal(mouseX, mouseY))
    }

    MouseArea {
        id: mRightTopResizeHandler
        visible: root.resizeEnable && root.framelessEnable
        enabled: root.resizeEnable && root.framelessEnable
        width: root.resizeHandlerSize
        height: root.resizeHandlerSize
        anchors.right: root.contentItem.right
        anchors.top: root.contentItem.top
        z: root.resizeHandlerZValue
        hoverEnabled: true
        cursorShape: Qt.SizeBDiagCursor
        onPressed: mPrivate.resizeHandlerPressed(QEXTQuick.DragDirection_RightTop, mapToGlobal(mouseX, mouseY))
        onReleased: mPrivate.resizeHandlerReleased(QEXTQuick.DragDirection_RightTop)
        onPositionChanged: mPrivate.positionChange(mapToGlobal(mouseX, mouseY))
    }

    MouseArea {
        id: mLeftBottomResizeHandler
        visible: root.resizeEnable && root.framelessEnable
        enabled: root.resizeEnable && root.framelessEnable
        width: root.resizeHandlerSize
        height: root.resizeHandlerSize
        anchors.left: root.contentItem.left
        anchors.bottom: root.contentItem.bottom
        z: root.resizeHandlerZValue
        hoverEnabled: true
        cursorShape: Qt.SizeBDiagCursor
        onPressed: mPrivate.resizeHandlerPressed(QEXTQuick.DragDirection_LeftBottom, mapToGlobal(mouseX, mouseY))
        onReleased: mPrivate.resizeHandlerReleased(QEXTQuick.DragDirection_LeftBottom)
        onPositionChanged: mPrivate.positionChange(mapToGlobal(mouseX, mouseY))
    }

    MouseArea {
        id: mRightBottomResizeHandler
        visible: root.resizeEnable && root.framelessEnable
        enabled: root.resizeEnable && root.framelessEnable
        width: root.resizeHandlerSize
        height: root.resizeHandlerSize
        anchors.right: root.contentItem.right
        anchors.bottom: root.contentItem.bottom
        z: root.resizeHandlerZValue
        hoverEnabled: true
        cursorShape: Qt.SizeFDiagCursor
        onPressed: mPrivate.resizeHandlerPressed(QEXTQuick.DragDirection_RightBottom, mapToGlobal(mouseX, mouseY))
        onReleased: mPrivate.resizeHandlerReleased(QEXTQuick.DragDirection_RightBottom)
        onPositionChanged: mPrivate.positionChange(mapToGlobal(mouseX, mouseY))
    }

    MouseArea {
        id: mLeftResizeHandler
        visible: root.resizeEnable && root.framelessEnable
        enabled: root.resizeEnable && root.framelessEnable
        width: root.resizeHandlerSize
        anchors.left: root.contentItem.left
        anchors.top: mLeftTopResizeHandler.bottom
        anchors.bottom: mLeftBottomResizeHandler.top
        anchors.verticalCenter: root.verticalCenter
        z: root.resizeHandlerZValue
        hoverEnabled: true
        cursorShape: Qt.SizeHorCursor
        onPressed: mPrivate.resizeHandlerPressed(QEXTQuick.DragDirection_Left, mapToGlobal(mouseX, mouseY))
        onReleased: mPrivate.resizeHandlerReleased(QEXTQuick.DragDirection_Left)
        onPositionChanged: mPrivate.positionChange(mapToGlobal(mouseX, mouseY))
    }

    MouseArea {
        id: mTopResizeHandler
        visible: root.resizeEnable && root.framelessEnable
        enabled: root.resizeEnable && root.framelessEnable
        height: root.resizeHandlerSize
        anchors.top: root.contentItem.top
        anchors.left: mLeftTopResizeHandler.right
        anchors.right: mRightTopResizeHandler.left
        anchors.horizontalCenter: root.horizontalCenter
        z: root.resizeHandlerZValue
        hoverEnabled: true
        cursorShape: Qt.SizeVerCursor
        onPressed: mPrivate.resizeHandlerPressed(QEXTQuick.DragDirection_Top, mapToGlobal(mouseX, mouseY))
        onReleased: mPrivate.resizeHandlerReleased(QEXTQuick.DragDirection_Top)
        onPositionChanged: mPrivate.positionChange(mapToGlobal(mouseX, mouseY))
    }

    MouseArea {
        id: mRightResizeHandler
        visible: root.resizeEnable && root.framelessEnable
        enabled: root.resizeEnable && root.framelessEnable
        width: root.resizeHandlerSize
        anchors.right: root.contentItem.right
        anchors.top: mRightTopResizeHandler.bottom
        anchors.bottom: mRightBottomResizeHandler.top
        anchors.verticalCenter: root.verticalCenter
        z: root.resizeHandlerZValue
        hoverEnabled: true
        cursorShape: Qt.SizeHorCursor
        onPressed: mPrivate.resizeHandlerPressed(QEXTQuick.DragDirection_Right, mapToGlobal(mouseX, mouseY))
        onReleased: mPrivate.resizeHandlerReleased(QEXTQuick.DragDirection_Right)
        onPositionChanged: mPrivate.positionChange(mapToGlobal(mouseX, mouseY))
    }

    MouseArea {
        id: mBottomResizeHandler
        visible: root.resizeEnable && root.framelessEnable
        enabled: root.resizeEnable && root.framelessEnable
        height: root.resizeHandlerSize
        anchors.bottom: root.contentItem.bottom
        anchors.left: mLeftBottomResizeHandler.right
        anchors.right: mRightBottomResizeHandler.left
        anchors.horizontalCenter: root.horizontalCenter
        z: root.resizeHandlerZValue
        hoverEnabled: true
        cursorShape: Qt.SizeVerCursor
        onPressed: mPrivate.resizeHandlerPressed(QEXTQuick.DragDirection_Bottom, mapToGlobal(mouseX, mouseY))
        onReleased: mPrivate.resizeHandlerReleased(QEXTQuick.DragDirection_Bottom)
        onPositionChanged: mPrivate.positionChange(mapToGlobal(mouseX, mouseY))
    }

    QtObject {
        id: mPrivate

        property bool isPressed: false
        property int resizeHandlerType
        property point pressedMouse
        property real positionX
        property real positionY
        property real oldWidth
        property real oldHeight

        function resizeHandlerPressed(dragDirection, mouse) {
            isPressed = true
            resizeHandlerType = dragDirection
            pressedMouse = mouse
            positionX = root.x
            positionY = root.y
            oldWidth = root.width
            oldHeight = root.height
        }

        function resizeHandlerReleased(dragDirection) {
            isPressed = false
        }

        function positionChange(mouse) {
            if (!isPressed) {
                return
            }

            var deltaWidth = mouse.x - pressedMouse.x
            var deltaHeight = mouse.y - pressedMouse.y

            switch (resizeHandlerType) {
            case QEXTQuick.DragDirection_Right:
                root.x = positionX
                root.y = positionY
                root.width = oldWidth + deltaWidth
                break
            case QEXTQuick.DragDirection_Bottom:
                root.x = positionX
                root.y = positionY
                root.height = oldHeight + deltaHeight
                break
            case QEXTQuick.DragDirection_RightBottom:
                root.x = positionX
                root.y = positionY
                root.width = oldWidth + deltaWidth
                root.height = oldHeight + deltaHeight
                break
            case QEXTQuick.DragDirection_Left:
                root.x = positionX + deltaWidth
                root.y = positionY
                root.width = oldWidth - deltaWidth
                break
            case QEXTQuick.DragDirection_Top:
                root.x = positionX
                root.y = positionY + deltaHeight
                root.height = oldHeight - deltaHeight
                break
            case QEXTQuick.DragDirection_LeftTop:
                root.x = positionX + deltaWidth
                root.y = positionY + deltaHeight
                root.width = oldWidth - deltaWidth
                root.height = oldHeight - deltaHeight
                break
            case QEXTQuick.DragDirection_RightTop:
                root.x = positionX
                root.y = positionY + deltaHeight
                root.width = oldWidth + deltaWidth
                root.height = oldHeight - deltaHeight
                break
            case QEXTQuick.DragDirection_LeftBottom:
                root.x = positionX + deltaWidth
                root.y = positionY
                root.width = oldWidth - deltaWidth
                root.height = oldHeight + deltaHeight
                break
            }
        }
    }


}
