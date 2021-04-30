import QtQuick 2.6
import QtQuick.Window 2.2
import QEXTQuick 1.2

Window {
    id: root
    visible: true
    width: 1024
    height: 700

    QEXTQuickWorld {
        mouseAreaCursorShape: Qt.PointingHandCursor
    }

    Rectangle {
        id: tBodyRectangle
        anchors.fill: parent
        color: "#FFF"

        Topbar {
            id: mTopbar
            width: parent.width
            height: 45
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }

        TabPanel {
            id: mTabPanel
            width: parent.width
            anchors.top: mTopbar.bottom
            anchors.bottom: mFooterbar.top
            anchors.horizontalCenter: parent.horizontalCenter
            tabModel: [
                {label: "Home", uri: "qrc:/Home.qml"},
                {label: "Awesome", uri: "qrc:/C_Awesome.qml"},
                {label: "Icon", uri: "qrc:/C_Icon.qml"},
                {label: "Avatar", uri: "qrc:/C_Avatar.qml"},
                {label: "Badge", uri: "qrc:/C_Badge.qml"},
                {label: "Button", uri: "qrc:/C_Button.qml"},
                {label: "IconButton", uri: "qrc:/C_IconButton.qml"},
                {label: "InputField", uri: "qrc:/C_InputField.qml"},
                {label: "FpsMonitor", uri: "qrc:/C_FpsMonitor.qml"},
                {label: "Carousel", uri: "qrc:/C_Carousel.qml"},
                {label: "Pagination", uri: "qrc:/C_Pagination.qml"},
                {label: "BusyIndicator", uri: "qrc:/C_BusyIndicator.qml"},
                {label: "DividerLine", uri: "qrc:/C_DividerLine.qml"},
                {label: "Tag", uri: "qrc:/C_Tag.qml"},
                {label: "ProgressBar", uri: "qrc:/C_ProgressBar.qml"},
                {label: "CheckBox", uri: "qrc:/C_CheckBox.qml"},
                {label: "Switch", uri: "qrc:/C_Switch.qml"},
                {label: "RadioButton", uri: "qrc:/C_RadioButton.qml"},
                {label: "Toast", uri: "qrc:/C_Toast.qml"},
                {label: "Dialog", uri: "qrc:/C_Dialog.qml"},
                {label: "NavigationBar", uri: "qrc:/C_NavigationBar.qml"},
                {label: "MoveArea", uri: "qrc:/C_MoveArea.qml"},
                {label: "ResizeArea", uri: "qrc:/C_ResizeArea.qml"},
                {label: "Collapse", uri: "qrc:/C_Collapse.qml"},
                {label: "Test", uri: "qrc:/Test.qml"},
            ]
            defaultTab: "InputField"
        }

        Footerbar {
            id: mFooterbar
            width: parent.width
            height: 45
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Component.onCompleted: {
        root.showMaximized()
        root.showNormal()
    }
}
