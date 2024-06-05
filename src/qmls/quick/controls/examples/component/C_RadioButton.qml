import QtQuick 2.12
import QtQuick.Controls 2.12
import QExtQuick.Controls 1.2

Column{
    spacing: 15

    ButtonGroup { id: mBtnGroup1 }
    ButtonGroup { id: mBtnGroup2 }

    Row{
        id:layout
        spacing: 3

        QExtQuickRadioButton {
            text: "Guangzhou"
            checked: true
            ButtonGroup.group: mBtnGroup1
        }

        QExtQuickRadioButton {
            text: "Shanghai"
            ButtonGroup.group: mBtnGroup1
        }

        QExtQuickRadioButton {
            enabled: false
            text: "Hong Kong"
            ButtonGroup.group: mBtnGroup1
        }

        QExtQuickRadioButton {
            id:result
            text: "esDF"
            width: 40
            anchors.verticalCenter: parent.verticalCenter
            ButtonGroup.group: mBtnGroup1
        }
    }

    Row{
        id:layoutborder
        spacing: 25

        QExtQuickRadioButton {
            id:tb
            text: "Primary"
            textInLeft: true
            backgroundVisible: true
            backgroundBorderWidth: 1
            radioItem: radioFlatItem
            ButtonGroup.group: mBtnGroup2

            states: [
                State {
                    name: "Checked"
                    PropertyChanges {
                        target: tb
                        backgroundBorderColor: "#409EFF"
                    }
                }
            ]
        }

        QExtQuickRadioButton {
            id:tb2
            text: "Success"
            textInLeft: true
            backgroundVisible: true
            backgroundBorderWidth: 1
            backgroundColor: "#F0F9EB"
            radioItem: radioFlatItem
            ButtonGroup.group: mBtnGroup2
            states: [
                State {
                    name: "Checked"
                    PropertyChanges {
                        target: tb2
                        backgroundBorderColor: "#67C23A"
                    }
                }
            ]
        }

        QExtQuickRadioButton {
            id:tb3
            text: "Warning"
            textInLeft: true
            backgroundVisible: true
            backgroundBorderWidth: 1
            backgroundColor: "#FDF6ED"
            radioItem: radioFlatItem
            ButtonGroup.group: mBtnGroup2
            states: [
                State {
                    name: "Checked"
                    PropertyChanges {
                        target: tb3
                        backgroundBorderColor: "#E6A23C"
                    }
                }
            ]
        }

        QExtQuickRadioButton {
            id:tb4
            text: "Danger"
            textInLeft: true
            backgroundVisible: true
            backgroundBorderWidth: 1
            backgroundColor: "#FEF0F0"
            radioItem: radioFlatItem
            ButtonGroup.group: mBtnGroup2
            states: [
                State {
                    name: "Checked"
                    PropertyChanges {
                        target: tb4
                        backgroundBorderColor: "#F56C6C"
                    }
                }
            ]
        }
    }

}
