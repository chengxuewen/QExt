import QtQml 2.9
import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQuick.Controls 1.3

Column {
    id: root
    spacing: 20

    Rectangle {
        id:rect4
        width:  360
        height: 80
        color: {
            switch("const_error"){
            case "const_success": return "#F0F9EB"
            case "const_warning": return "#FDF6ED"
            case "const_info":    return "#EDF2FC"
            case "const_error":   return "#FEF0F0"
            }
            return "#FFFFFF"
        }
        radius: 4
        border.width: 1
        border.color: Qt.lighter(ticon4.color,1.2)

        Row{
            x:20
            y:(parent.height - height) / 2
            spacing: 10
            QExtQuickImage {
                id:ticon4
                anchors.verticalCenter: parent.verticalCenter
                source:{
                    switch("const_info"){
                    case "const_success": return "qrc:/QExtQuickControls/resource/image/success.svg"
                    case "const_warning": return "qrc:/QExtQuickControls/resource/image/warning.svg"
                    case "const_info":    return "qrc:/QExtQuickControls/resource/image/info.svg"
                    case "const_error":   return "qrc:/QExtQuickControls/resource/image/error.svg"
                    }
                    return "#FFFFFF"
                }

                width:  more4.visible ? 40 : 22
                height: more4.visible ? 40 : 22

                color: {
                    switch("const_error"){
                    case "const_success": return "#6AC044"
                    case "const_warning": return "#E4A147"
                    case "const_info":    return "#909399"
                    case "const_error":   return "#F36D6F"
                    }
                    return "#FFFFFF"
                }
            }

            Column{
                spacing: 5
                Label {
                    font.bold:more4.visible
                    font.pixelSize: 20
                    text: "Error"
                    color: ticon4.color
                }

                Label {
                    id:more4
                    color:    ticon4.color
                    text:    "User name error\nPassword length error"
                    wrapMode : Text.WordWrap
                    onContentWidthChanged: {
                        width = contentWidth <300 - 100 ? 220 : 300
                    }
                }
            }
        }

        QExtQuickImage {
            y:4
            x:parent.width - width
            width: 12
            height: width
            source: "qrc:/QExtQuickControls/resource/image/close_px.svg"
            color: "#ADADAD"
        }
    }

    Row{
        height: 30
        spacing: 20
        Button {
            text: "Show Success Closeable"
            onClicked: {
                QExtQuickGlobalToast.showSuccess("Welcome to QExtQuickControls", 5000, "No discord, no concord.")
            }
        }
        Button {
            text: "Show Warning Closeable"
            onClicked: QExtQuickGlobalToast.showWarning("Welcome to QExtQuickControls", 2000)
        }

        Button {
            text: "Show Info Closeable"
            onClicked: QExtQuickGlobalToast.showInfo("Welcome to QExtQuickControls", 2000)
        }

        Button{
            text: "Show Error Closeable"
            onClicked: QExtQuickGlobalToast.showError("Welcome to QExtQuickControls", 2000)
        }

        Component {
            id: customComponent
            Rectangle {
                width: 300
                height: 100
                color: "red"
            }
        }
        Button{
            text: "Show custom component"
            onClicked: QExtQuickGlobalToast.showCustom(customComponent, 2000)
        }
    }
    Row{
        height: 30
        spacing: 20
        Button {
            text: "Show Success"
            onClicked: {
                QExtQuickGlobalToast.showSuccess("Welcome to QExtQuickControls", 5000, "No discord, no concord.", false)
            }
        }
        Button {
            text: "Show Warning"
            onClicked: QExtQuickGlobalToast.showWarning("Welcome to QExtQuickControls", 2000, "", false)
        }

        Button {
            text: "Show Info"
            onClicked: QExtQuickGlobalToast.showInfo("Welcome to QExtQuickControls", 2000, "", false)
        }

        Button{
            text: "Show Error"
            onClicked: QExtQuickGlobalToast.showError("Welcome to QExtQuickControls", 2000, "", false)
        }
    }

    Label{
        text: "( Theme! For real effects, please click to show)"
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Component.onCompleted: {
        QExtQuickGlobalToast.setTopLevelWindow(root)
        QExtQuickGlobalToast.horizontalAlignment = Qt.AlignRight
        QExtQuickGlobalToast.verticalAlignment = Qt.AlignBottom
    }
}
