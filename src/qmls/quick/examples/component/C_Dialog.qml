import QtQuick 2.12
import QtQuick.Controls 2.12
import QExtQuick 1.0

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
                        text: "Hi QExtQuick"
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                        font.pixelSize: QExtQuick.PH5
                    }

                    QExtQuickIconButton {
                        padding: 10
                        width: 30
                        height: 30
                        background: null
                        visible: true
                        iconSource: "qrc:/QExtQuick/svg/close-px.svg"
                        iconDisplay: QExtQuick.IconDisplay_IconOnly
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

                QExtQuickDividerLine {
                    width: parent.width * 0.95
                    height: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Item {
                    width: 100
                    height: 45
                    anchors.horizontalCenter: parent.horizontalCenter
                    QExtQuickButton {
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
        QExtQuickButton {
            text: "Open default"
            textColor: "#46A0FC"
            background: null
            onClicked: dialog.open()
        }

        QExtQuickButton {
            text: "Open Not centered"
            textColor: "#46A0FC"
            background: null
            onClicked: dialog2.open()
        }

        QExtQuickButton {
            text: "Open Input"
            textColor: "#46A0FC"
            background: null
            onClicked: dialog_input.open()
        }

        QExtQuickButton {
            text: "Open List view"
            textColor: "#46A0FC"
            background: null
            onClicked: dialog_list.open()
        }

        QExtQuickButton {
            text: "test"
            textColor: "#46A0FC"
            background: null
            onClicked: mTestDialog.open()
        }


        QExtQuickDialog {
            id: dialog
            title: "Hi QExtQuick"
            contentText: "This a dialog style for default"
            buttons: [
                QExtQuickDialogButton {
                    text: "Agree"
                    textFont.bold: true
                    textFont.pixelSize: QExtQuick.PH5
                    textColor: "#46A0FC"
                }
            ]

            onButtonTriggered: accept()
        }


        QExtQuickDialog {
            id: dialog2
            headerText: "Hi QExtQuick"
            layoutInCenter: false

            buttons: [
                QExtQuickDialogButton {
                    text: "Cancel"
                    textFont.pixelSize: QExtQuick.PH5
                },
                QExtQuickDialogButton {
                    text: "Agree"
                    textFont.bold: true
                    textFont.pixelSize: QExtQuick.PH5
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


        QExtQuickDialog {
            id: dialog_input
            headerText: "Tell me your name"
            closeable: false
            buttons: [
                QExtQuickDialogButton {
                    text: "Cancel"
                    textFont.pixelSize: QExtQuick.PH5
                    //                    backgroundVisible: true
                },
                QExtQuickDialogButton {
                    text: "OK"
                    textFont.bold: true
                    textFont.pixelSize: QExtQuick.PH5
                    textColor: "#46A0FC"
                    lighter: true
                }
            ]
            contentItem: Item {
                property alias text: input.text
                implicitWidth: parent.implicitWidth
                implicitHeight: 50
                QExtQuickInputField {
                    id: input
                    width: parent.width - 40
                    height: parent.height - 10
                    anchors.centerIn: parent
                }
            }


            onButtonTriggered: {
                if (button.text === "OK" && item.text) {
                    QExtQuickToast.showSuccess("Hi, " + item.text , 2000)
                } else {
                    QExtQuickToast.showError("What's your name？", 2000)
                }
                accept()
            }
        }
        QExtQuickDialog {
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

        QExtQuickDialog {
            id: mTestDialog

            contentText: "aefwwewfdewfewcfvrasgvafdsvdfsvadfvasdfvcasdfv sdfvdsfvadsvafsdvvasdfv
                            vsdvcDSFVafdsvadfsvadfsvdfsavFDSVvdfsZVasdfvvvadsscvdsAKFBHCIO;UHEBS
                            vsdvcDSFVafdsvadfsvadfsvdfsavFDSVvdfsZVasdfvvvadsscvdsAKFBHCIO;UHEBS
                            vsdvcDSFVafdsvadfsvadfsvdfsavFDSVvdfsZVasdfvvvadsscvdsAKFBHCIO;UHEBS
                            FP;Oihnbsdfoivhnzfiodvhniodfvbu aiodfvhniaohnrvc ;ioZDHUUUV"

            buttons: [
                QExtQuickDialogButton {
                    text: "Cancel"
                    textFont.pixelSize: QExtQuick.PH5
                    //                    backgroundVisible: true
                },
                QExtQuickDialogButton {
                    text: "OK"
                    textFont.bold: true
                    textFont.pixelSize: QExtQuick.PH5
                    //                backgroundVisible: true
                    textColor: "#46A0FC"
                    lighter: true
                },

                QExtQuickDialogButton {
                    text: "OK"
                    textFont.bold: true
                    textFont.pixelSize: QExtQuick.PH5
                    //                backgroundVisible: true
                    textColor: "#46A0FC"
                    lighter: true
                },

                QExtQuickDialogButton {
                    text: "OK"
                    textFont.bold: true
                    textFont.pixelSize: QExtQuick.PH5
                    backgroundVisible: true
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
