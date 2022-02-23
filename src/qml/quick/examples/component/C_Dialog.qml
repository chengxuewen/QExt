import QtQuick 2.9
import QtQuick.Controls 2.9
import QEXTQmlQuick 1.0

Column {
    spacing: 10

    Item {
        width: 10
        height: 10
    }
    Item {
        id:simulation
        width: 270
        height: content.height

        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id:content
            anchors.fill: parent
            height: layout.height

            Column {
                spacing: 2
                id:layout
                Item{
                    width: 260
                    height: label.height < 30 ? 30 : label.height
                    anchors.horizontalCenter: parent.horizontalCenter
                    Label {
                        id: label
                        text: "Hi QEXTQmlQuick"
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                        font.pixelSize: QEXTQmlQuick.PH5
                    }

                    QEXTQmlQuickIconButton {
                        padding: 10
                        width: 30
                        height: 30
                        background: null
                        visible: true
                        iconSource: "qrc:/QEXTQmlQuick/svg/close-px.svg"
                        iconDisplay: QEXTQmlQuick.IconDisplay_IconOnly
                        anchors.right: parent.right
                        anchors.rightMargin: 5
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Item {
                    width: tlabel.width
                    height: 55
                    anchors.horizontalCenter: parent.horizontalCenter
                    Label {
                        id:tlabel
                        anchors.centerIn: parent
                        text: "This is a text message"
                    }
                }

                QEXTQmlQuickDividerLine {
                    width: parent.width * 0.95
                    height: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Item {
                    width: 100
                    height: 45
                    anchors.horizontalCenter: parent.horizontalCenter
                    QEXTQmlQuickButton {
                        background: null
                        anchors.centerIn: parent
                        text: "Agree"
                        textFont.bold: true
                        textColor: "#409EFF"
                    }
                }

            }

            border.width: 1
            border.color: "#DCDCDC"
            color: "#FFF"
            radius: 4
        }
    }


    Row{
        QEXTQmlQuickButton {
            text: "Open default"
            textColor: "#46A0FC"
            background: null
            onClicked: dialog.open()
        }

        QEXTQmlQuickButton {
            text: "Open Not centered"
            textColor: "#46A0FC"
            background: null
            onClicked: dialog2.open()
        }

        QEXTQmlQuickButton {
            text: "Open Input"
            textColor: "#46A0FC"
            background: null
            onClicked: dialog_input.open()
        }

        QEXTQmlQuickButton {
            text: "Open List view"
            textColor: "#46A0FC"
            background: null
            onClicked: dialog_list.open()
        }

        QEXTQmlQuickButton {
            text: "test"
            textColor: "#46A0FC"
            background: null
            onClicked: mTestDialog.open()
        }


        QEXTQmlQuickDialog {
            id: dialog
            title: "Hi QEXTQmlQuick"
            contentText: "This a dialog style for default"
            buttons: [
                QEXTQmlQuickDialogButton {
                    text: "Agree"
                    textFont.bold: true
                    textFont.pixelSize: QEXTQmlQuick.PH5
                    textColor: "#46A0FC"
                }
            ]

            onButtonTriggered: accept()
        }


        QEXTQmlQuickDialog {
            id: dialog2
            headerText: "Hi QEXTQmlQuick"
            layoutInCenter: false

            buttons: [
                QEXTQmlQuickDialogButton {
                    text: "Cancel"
                    textFont.pixelSize: QEXTQmlQuick.PH5
                },
                QEXTQmlQuickDialogButton {
                    text: "Agree"
                    textFont.bold: true
                    textFont.pixelSize: QEXTQmlQuick.PH5
                    textColor: "#46A0FC"
                    lighter:true
                }
            ]

            contentItem: Item {
                implicitWidth: parent.implicitWidth
                implicitHeight: 40
                Label {
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    text: "This a dialog ,text is not centered"
                }
            }

            onButtonTriggered: accept()
        }


        QEXTQmlQuickDialog {
            id: dialog_input
            headerText: "Tell me your name"
            closeable: false
            buttons: [
                QEXTQmlQuickDialogButton {
                    text: "Cancel"
                    textFont.pixelSize: QEXTQmlQuick.PH5
                    //                    backgroundVisiable: true
                },
                QEXTQmlQuickDialogButton {
                    text: "OK"
                    textFont.bold: true
                    textFont.pixelSize: QEXTQmlQuick.PH5
                    textColor: "#46A0FC"
                    lighter: true
                }
            ]
            contentItem: Item {
                property alias text: input.text
                implicitWidth: parent.implicitWidth
                implicitHeight: 50
                QEXTQmlQuickInputField {
                    id: input
                    width: parent.width - 40
                    height: parent.height - 10
                    anchors.centerIn: parent
                }
            }


            onButtonTriggered: {
                if (button.text === "OK" && item.text) {
                    QEXTQmlQuickToast.showSuccess("Hi, " + item.text , 2000)
                } else {
                    QEXTQmlQuickToast.showError("What's your name？", 2000)
                }
                accept()
            }
        }
        QEXTQmlQuickDialog {
            id: dialog_list
            headerText: "ListView Dialog"
            closeable: true
            footer: null
            contentItem: Item {
                implicitWidth: parent.implicitWidth
                implicitHeight: lv.height
                ListView {
                    id:lv
                    width: 240
                    height: 500
                    model: 99
                    anchors.horizontalCenter: parent.horizontalCenter
                    delegate: Label {
                        text: "ListView Item " + index
                    }
                }
            }
        }

        QEXTQmlQuickDialog {
            id: mTestDialog

            contentText: "aefwwewfdewfewcfvrasgvafdsvdfsvadfvasdfvcasdfv sdfvdsfvadsvafsdvvasdfv
                            vsdvcDSFVafdsvadfsvadfsvdfsavFDSVvdfsZVasdfvvvadsscvdsAKFBHCIO;UHEBS
                            vsdvcDSFVafdsvadfsvadfsvdfsavFDSVvdfsZVasdfvvvadsscvdsAKFBHCIO;UHEBS
                            vsdvcDSFVafdsvadfsvadfsvdfsavFDSVvdfsZVasdfvvvadsscvdsAKFBHCIO;UHEBS
                            FP;Oihnbsdfoivhnzfiodvhniodfvbu aiodfvhniaohnrvc ;ioZDHUUUV"

            buttons: [
                QEXTQmlQuickDialogButton {
                    text: "Cancel"
                    textFont.pixelSize: QEXTQmlQuick.PH5
                    //                    backgroundVisiable: true
                },
                QEXTQmlQuickDialogButton {
                    text: "OK"
                    textFont.bold: true
                    textFont.pixelSize: QEXTQmlQuick.PH5
                    //                backgroundVisiable: true
                    textColor: "#46A0FC"
                    lighter: true
                },

                QEXTQmlQuickDialogButton {
                    text: "OK"
                    textFont.bold: true
                    textFont.pixelSize: QEXTQmlQuick.PH5
                    //                backgroundVisiable: true
                    textColor: "#46A0FC"
                    lighter: true
                },

                QEXTQmlQuickDialogButton {
                    text: "OK"
                    textFont.bold: true
                    textFont.pixelSize: QEXTQmlQuick.PH5
                    backgroundVisiable: true
                    textColor: "#46A0FC"
                    lighter: true
                }
            ]
        }

    }


    Label {
        text: "( Theme! For real effects, please click to show)"
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
