import QtQml 2.9
import QtQuick 2.9
import QtQuick.Window 2.9
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.9

import QExtQuick.Controls 1.4

Window {
    id: root
    visible: true
    width: 1024
    height: 700

    // QExtQuickWorld {
    //     mouseAreaCursorShape: Qt.PointingHandCursor
    // }

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
                {label: "Home", uri: "qrc:/qml/Home.qml"},
                {label: "Button", uri: "qrc:/qml/C_Button.qml"},
                {label: "Rectangle", uri: "qrc:/qml/C_Rectangle.qml"},
                {label: "Switch", uri: "qrc:/qml/C_Switch.qml"},
                {label: "FontIcon", uri: "qrc:/qml/C_FontIcon.qml"},
                {label: "SvgIcon", uri: "qrc:/qml/C_SvgIcon.qml"},
                {label: "IconButton", uri: "qrc:/qml/C_IconButton.qml"},
                {label: "CheckBox", uri: "qrc:/qml/C_CheckBox.qml"},
                {label: "RadioButton", uri: "qrc:/qml/C_RadioButton.qml"},
                {label: "DividerLine", uri: "qrc:/qml/C_DividerLine.qml"},
                {label: "InputField", uri: "qrc:/qml/C_InputField.qml"},
                {label: "Toast", uri: "qrc:/qml/C_Toast.qml"},
                {label: "Collapse", uri: "qrc:/qml/C_Collapse.qml"},
                {label: "Triangle", uri: "qrc:/qml/C_Triangle.qml"},
                // {label: "Badge", uri: "qrc:/qml/C_Badge.qml"},
                // {label: "Tag", uri: "qrc:/qml/C_Tag.qml"},
                // {label: "BusyIndicator", uri: "qrc:/qml/C_BusyIndicator.qml"},
                // {label: "FpsMonitor", uri: "qrc:/qml/C_FpsMonitor.qml"},
                // {label: "ProgressBar", uri: "qrc:/qml/C_ProgressBar.qml"},
                // {label: "Dialog", uri: "qrc:/qml/C_Dialog.qml"},
                // {label: "Carousel", uri: "qrc:/C_Carousel.qml"},
                // {label: "Carousel", uri: "qrc:/C_Carousel.qml"},
                // {label: "Pagination", uri: "qrc:/C_Pagination.qml"},
                // {label: "CircularProgressBar", uri: "qrc:/C_CircularProgressBar.qml"},
                // {label: "NavigationBar", uri: "qrc:/C_NavigationBar.qml"},
                // {label: "MoveArea", uri: "qrc:/C_MoveArea.qml"},
                // {label: "ResizeArea", uri: "qrc:/C_ResizeArea.qml"},
                // {label: "Test", uri: "qrc:/Test.qml"},
            ]
            defaultTab: "Home"
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
