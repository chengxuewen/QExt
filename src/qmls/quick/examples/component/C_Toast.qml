import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQml 2.12
import QExtQuick 1.0

Column {
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
            QExtQuickSVGIcon {
                id:ticon4
                anchors.verticalCenter: parent.verticalCenter
                source:{
                    switch("const_info"){
                    case "const_success": return "qrc:/QExtQuick/svg/success.svg"
                    case "const_warning": return "qrc:/QExtQuick/svg/warning.svg"
                    case "const_info":    return "qrc:/QExtQuick/svg/info.svg"
                    case "const_error":   return "qrc:/QExtQuick/svg/error.svg"
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

        QExtQuickIconButton {
            y:4
            x:parent.width - width
            width: height
            iconWidth: 12
            iconHeight: 12
            iconDisplay: QExtQuick.IconDisplay_IconOnly
            iconSource: "qrc:/QExtQuick/svg/close-px.svg"
            iconColor: "#ADADAD"
            background: null
        }
    }

    Row{
        height: 30
        QExtQuickButton {
            background: null
            text: "Show Success"
            textColor: "#46A0FC"
            onClicked: {
                QExtQuickToast.showSuccess("Welcome to QExtQuick", 5000, "No discord, no concord.")
            }
        }

        QExtQuickButton {
            background: null
            text: "Show Warning"
            textColor: "#46A0FC"
            onClicked: QExtQuickToast.showWarning("Welcome to QExtQuick", 2000)
        }

        QExtQuickButton {
            background: null
            text: "Show Info"
            textColor: "#46A0FC"
            onClicked: QExtQuickToast.showInfo("Welcome to QExtQuick", 2000)
        }

        QExtQuickButton{
            background: null
            text: "Show Error"
            textColor: "#46A0FC"
            onClicked: QExtQuickToast.showError("Welcome to QExtQuick", 2000)
        }
    }

    Label{
        text: "( Theme! For real effects, please click to show)"
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Component.onCompleted: {
        QExtQuickToast.horizontalAlignment = Qt.AlignRight
        QExtQuickToast.verticalAlignment = Qt.AlignBottom
    }
}
