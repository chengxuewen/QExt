import QtQuick 2.12
import QtQuick.Controls 2.12

import QExtQuick 1.0

Column{
    spacing: 8

    Row{
        spacing: 5
        anchors.horizontalCenter: parent.horizontalCenter

        QExtQuickCheckBox{
            text: "MoviesDFVasdvasdfv"
        }

        QExtQuickCheckBox{
            text: "Music34523462346234"
            width: 100
            checked: true
        }

        QExtQuickCheckBox{
            text: "Running"
        }

        QExtQuickCheckBox{
            text: "Fitness"
            checked: true
        }

        QExtQuickCheckBox{
            text: "Sleeps"
            checked: true
            enabled: false
        }

        CheckBox {
            width: 100
            text: "Sleepsawefarsfgerag"
        }

    }

    Row{
        spacing: 5
        anchors.horizontalCenter: parent.horizontalCenter

        QExtQuickCheckBox{
            text: "Movie"
        }

        QExtQuickCheckBox{
            text: "Music"
            checked: true
        }

        QExtQuickCheckBox{
            text: "Running"
            checkState: Qt.PartiallyChecked
            tristate: true
        }

        QExtQuickCheckBox{
            text: "Fitness"
            tristate: true
            checked: true
        }

        QExtQuickCheckBox{
            text: "Sleeps"
            checkState: Qt.PartiallyChecked
            checked: true
            tristate: true
            enabled: false
        }

    }


    Row{
        spacing: 5
        anchors.horizontalCenter: parent.horizontalCenter

        QExtQuickCheckBox{
            id:cb
            text: "C++"
            checked: Math.random() > 0.5
            textInLeft: true
            backgroundBorderColor: "#F0F9EB"
            backgroundBorderWidth: 1
            states: [
                State {
                    name: "Checked"
                    PropertyChanges {
                        target: cb
                        backgroundBorderColor:"#67C23A"
                    }
                }
            ]
        }

        QExtQuickCheckBox{
            id:cb2
            text: "Lua"
            checked: Math.random() > 0.5
            textInLeft: true
            backgroundColor: "#F0F9EB"
            backgroundBorderWidth: 1
            states: [
                State {
                    name: "Checked"
                    PropertyChanges {
                        target: cb2
                        backgroundBorderColor:"#67C23A"
                    }
                }
            ]
        }

        QExtQuickCheckBox{
            id:cb3
            text: "234523452346"
            checked: Math.random() > 0.5
            textInLeft: true
            backgroundColor: "#FDF6ED"
            backgroundBorderWidth: 1
            states: [
                State {
                    name: "Checked"
                    PropertyChanges {
                        target: cb3
                        backgroundBorderColor:"#E6A23C"
                    }
                }
            ]
        }

        QExtQuickCheckBox{
            id:cb0
            text: "JAVA"
            checked: Math.random() > 0.5
            textInLeft: true
            backgroundColor: "#FDF6ED"
            backgroundBorderWidth: 1
            states: [
                State {
                    name: "Checked"
                    PropertyChanges {
                        target: cb0
                        backgroundBorderColor: "#E6A23C"
                    }
                }
            ]
        }

    }

}
