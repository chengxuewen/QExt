import QtQuick 2.9
import QtQml 2.9
import QtQuick.Window 2.2
import QEXTQmlQuick 1.0

Rectangle {
    id: tWindowTitleBar
    height: 40
    color: QEXTQmlQuickPalette.brandPrimaryColor

    signal closeButtonTriggered();

    property bool autoCloseEnable: true

    property real windowsIconBarHeight: 30
    property real windowsIconWidth: 20
    property real windowsIconHeight: 20
    property color windowsIconColor: "white"
    property string windowsMinimizeIconSource: QEXTQmlQuickFontAwesome.FA_window_minimize
    property string windowsMaximizeIconSource: QEXTQmlQuickFontAwesome.FA_window_maximize
    property string windowsRestoreIconSource: QEXTQmlQuickFontAwesome.FA_window_restore
    property string windowsCloseIconSource: QEXTQmlQuickFontAwesome.FA_window_close

    property Component additionalButtonBarItem
    property Component minimizeIconBackgroundItem
    property Component maxRestoreIconBackgroundItem
    property Component closeIconBackgroundItem: Rectangle {
        anchors.fill: parent
        color: "Red"
    }

    QEXTQmlQuickMoveArea {
        id: mTitleBarMoveArea
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        control: qextRootWindow

        property bool isDoubleClicked: false
        property bool isMaximizedBeforeMinimized: false

        onPressed: {
            isDoubleClicked = false
            updateMoveEnable()
        }
        onDoubleClicked: {
            isDoubleClicked = true;
            updateMoveEnable()
            if (Window.Windowed === qextRootWindow.visibility) {
                qextRootWindow.showMaximized()
                mWindowsSizeIcon.source = windowsRestoreIconSource
            } else {
                qextRootWindow.showNormal()
                mWindowsSizeIcon.source = windowsMaximizeIconSource
            }
        }
        Connections {
            target: qextRootWindow
            onVisibilityChanged: {
                mTitleBarMoveArea.updateMoveEnable()
                //fix minimized to show in windowed visibility when window is maximized Before minimized action bug
                if(mTitleBarMoveArea.isMaximizedBeforeMinimized && Window.Windowed === qextRootWindow.visibility) {
                    mTitleBarMoveArea.isMaximizedBeforeMinimized = false
                    qextRootWindow.showMaximized()
                }
            }
        }

        function updateMoveEnable() {
            mTitleBarMoveArea.moveEnable = !isDoubleClicked
        }
    }

    Row {
        id: mButtonLayout
        height: windowsIconBarHeight
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 5
        spacing: 5

        Loader {
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            sourceComponent: additionalButtonBarItem
        }

        Item {
            width: parent.height
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter

            QEXTQmlQuickIcon {
                id: mWindowsMinimizeIcon
                anchors.centerIn: parent
                width: windowsIconWidth
                height: windowsIconHeight
                source: windowsMinimizeIconSource
                color: windowsIconColor
                z: mWindowsMinimizeIconBgLoader.z + 1
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (Window.Maximized == qextRootWindow.visibility) {
                            mTitleBarMoveArea.isMaximizedBeforeMinimized = true
                        } else {
                            mTitleBarMoveArea.isMaximizedBeforeMinimized = false
                        }
                        qextRootWindow.showMinimized()
                    }
                }
            }
            Loader {
                id: mWindowsMinimizeIconBgLoader
                anchors.fill: parent
                sourceComponent: minimizeIconBackgroundItem
            }
        }


        Item {
            width: parent.height
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter

            QEXTQmlQuickIcon {
                id: mWindowsSizeIcon
                anchors.centerIn: parent
                width: windowsIconWidth
                height: windowsIconHeight
                source: !!qextRootWindow && qextRootWindow.Maximized ? windowsRestoreIconSource : windowsMaximizeIconSource
                color: windowsIconColor
                z: mWindowsSizeIconBgLoader.z + 1
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (Window.Windowed != qextRootWindow.visibility) {
                            qextRootWindow.showNormal()
                            mWindowsSizeIcon.source = windowsMaximizeIconSource
                        } else {
                            qextRootWindow.showMaximized()
                            mWindowsSizeIcon.source = windowsRestoreIconSource
                        }
                    }
                }
            }
            Loader {
                id: mWindowsSizeIconBgLoader
                anchors.fill: parent
                sourceComponent: maxRestoreIconBackgroundItem
            }
        }

        Item {
            width: parent.height
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter

            QEXTQmlQuickIcon {
                id: mWindowsCloseIcon
                anchors.centerIn: parent
                width: windowsIconWidth
                height: windowsIconHeight
                source: windowsCloseIconSource
                color: windowsIconColor
                z: mWindowsCloseIconBgLoader.z + 1
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        closeButtonTriggered()
                        if (autoCloseEnable) {
                            console.log("onClicked")
                            qextRootWindow.close()
                        }
                    }
                    onPressed: {
                        mWindowsCloseIcon.scale = 0.95
                    }
                    onReleased: {
                        mWindowsCloseIcon.scale = 1
                    }
                }
            }
            Loader {
                id: mWindowsCloseIconBgLoader
                anchors.fill: parent
                sourceComponent: closeIconBackgroundItem
            }
        }
    }
}
