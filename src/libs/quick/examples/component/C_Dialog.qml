import QtQuick 2.7
import QtQuick.Controls 2.12
import QEXTQuick 1.2

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
                        text: "Hi QEXTQuick"
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                        font.pixelSize: QEXTQuick.PH5
                    }

                    QEXTIconButton {
                        padding: 10
                        width: 30
                        height: 30
                        background: null
                        visible: true
                        iconSource: "qrc:/QEXTQuick/svg/close-px.svg"
                        iconDisplay: QEXTQuick.IconDisplay_IconOnly
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

                QEXTDividerLine {
                    width: parent.width * 0.95
                    height: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Item {
                    width: 100
                    height: 45
                    anchors.horizontalCenter: parent.horizontalCenter
                    QEXTButton {
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
        QEXTButton {
            text: "Open default"
            textColor: "#46A0FC"
            background: null
            onClicked: dialog.open()
        }

        QEXTButton {
            text: "Open Not centered"
            textColor: "#46A0FC"
            background: null
            onClicked: dialog2.open()
        }

        QEXTButton {
            text: "Open Input"
            textColor: "#46A0FC"
            background: null
            onClicked: dialog_input.open()
        }

        QEXTButton {
            text: "Open List view"
            textColor: "#46A0FC"
            background: null
            onClicked: dialog_list.open()
        }

        QEXTButton {
            text: "test"
            textColor: "#46A0FC"
            background: null
            onClicked: mTestDialog.open()
        }


        QEXTDialog {
            id: dialog
            title: "Hi QEXTQuick"
            contentText: "This a dialog style for default"
            buttons: [
                QEXTDialogButton {
                    text: "Agree"
                    textFont.bold: true
                    textFont.pixelSize: QEXTQuick.PH5
                    textColor: "#46A0FC"
                }
            ]

            onButtonTriggered: accept()
        }


        QEXTDialog {
            id: dialog2
            headerText: "Hi QEXTQuick"
            layoutInCenter: false

            buttons: [
                QEXTDialogButton {
                    text: "Cancel"
                    textFont.pixelSize: QEXTQuick.PH5
                },
                QEXTDialogButton {
                    text: "Agree"
                    textFont.bold: true
                    textFont.pixelSize: QEXTQuick.PH5
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


        QEXTDialog {
            id: dialog_input
            headerText: "Tell me your name"
            closeable: false
            buttons: [
                QEXTDialogButton {
                    text: "Cancel"
                    textFont.pixelSize: QEXTQuick.PH5
                    //                    backgroundVisiable: true
                },
                QEXTDialogButton {
                    text: "OK"
                    textFont.bold: true
                    textFont.pixelSize: QEXTQuick.PH5
                    textColor: "#46A0FC"
                    lighter: true
                }
            ]
            contentItem: Item {
                property alias text: input.text
                implicitWidth: parent.implicitWidth
                implicitHeight: 50
                QEXTInputField {
                    id: input
                    width: parent.width - 40
                    height: parent.height - 10
                    anchors.centerIn: parent
                }
            }


            onButtonTriggered: {
                if (button.text === "OK" && item.text) {
                    QEXTToast.showSuccess("Hi, " + item.text , 2000)
                } else {
                    QEXTToast.showError("What's your name？", 2000)
                }
                accept()
            }
        }
        QEXTDialog {
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

        QEXTDialog {
            id: mTestDialog

            contentText: "aefwwewfdewfewcfvrasgvafdsvdfsvadfvasdfvcasdfv sdfvdsfvadsvafsdvvasdfv
                            vsdvcDSFVafdsvadfsvadfsvdfsavFDSVvdfsZVasdfvvvadsscvdsAKFBHCIO;UHEBS
                            vsdvcDSFVafdsvadfsvadfsvdfsavFDSVvdfsZVasdfvvvadsscvdsAKFBHCIO;UHEBS
                            vsdvcDSFVafdsvadfsvadfsvdfsavFDSVvdfsZVasdfvvvadsscvdsAKFBHCIO;UHEBS
                            FP;Oihnbsdfoivhnzfiodvhniodfvbu aiodfvhniaohnrvc ;ioZDHUUUV"

            buttons: [
                QEXTDialogButton {
                    text: "Cancel"
                    textFont.pixelSize: QEXTQuick.PH5
                    //                    backgroundVisiable: true
                },
                QEXTDialogButton {
                    text: "OK"
                    textFont.bold: true
                    textFont.pixelSize: QEXTQuick.PH5
                    //                backgroundVisiable: true
                    textColor: "#46A0FC"
                    lighter: true
                },

                QEXTDialogButton {
                    text: "OK"
                    textFont.bold: true
                    textFont.pixelSize: QEXTQuick.PH5
                    //                backgroundVisiable: true
                    textColor: "#46A0FC"
                    lighter: true
                },

                QEXTDialogButton {
                    text: "OK"
                    textFont.bold: true
                    textFont.pixelSize: QEXTQuick.PH5
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
