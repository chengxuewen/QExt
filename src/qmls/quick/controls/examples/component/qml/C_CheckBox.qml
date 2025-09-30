import QtQuick 2.12
import QtQuick.Controls 2.12

import QExtQml 1.4
import QExtQuick.Controls 1.4

Column{
    spacing: 8

    Row{
        spacing: 5

        QExtQuickCheckBox{
            text: "MoviesDFVasdvasdfv"
        }

        QExtQuickCheckBox{
            text: "Music34523462346234"
            width: 100
            checked: true
            checkedIcon.color: "red"
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

    }

    Row{
        spacing: 5

        QExtQuickCheckBox{
            text: "Movie"
        }

        QExtQuickCheckBox{
            text: "Music"
            checked: true
        }

        QExtQuickCheckBox{
            text: "Running"
            // checkState: Qt.PartiallyChecked
            // tristate: true
        }

        QExtQuickCheckBox{
            text: "Fitness"
            // tristate: true
            checked: true
        }

        QExtQuickCheckBox{
            text: "Sleeps"
            // checkState: Qt.PartiallyChecked
            checked: true
            // tristate: true
            enabled: false
        }

    }


    Row{
        spacing: 5

        QExtQuickCheckBox{
            id:cb
            text: "C++"
            checked: Math.random() > 0.5
            iconPosition: QExtQml.PositionRight
            background.visible: true
            background.color: "#F0F9EB"
            border.color: "#F0F9EB"
            border.width: 1
            states: [
                State {
                    name: "checked"
                    PropertyChanges {
                        target: cb
                        border.color:"#67C23A"
                    }
                }
            ]
        }

        QExtQuickCheckBox{
            id:cb2
            text: "Lua"
            checked: Math.random() > 0.5
            iconPosition: QExtQml.PositionRight
            background.visible: true
            background.color: "#F0F9EB"
            border.color: "#F0F9EB"
            border.width: 1
            states: [
                State {
                    name: "checked"
                    PropertyChanges {
                        target: cb2
                        border.color:"#67C23A"
                    }
                }
            ]
        }

        QExtQuickCheckBox{
            id:cb3
            width: implicitWidth
            height: implicitHeight
            text: "234523452346aefdaqswefgrws|"
            checked: Math.random() > 0.5
            iconPosition: QExtQml.PositionRight
            background.visible: true
            background.color: "#FDF6ED"
            border.color: "#FDF6ED"
            border.width: 1
            states: [
                State {
                    name: "checked"
                    PropertyChanges {
                        target: cb3
                        border.color:"#E6A23C"
                    }
                }
            ]
        }

        QExtQuickCheckBox{
            id:cb0
            text: "JAVA"
            checked: Math.random() > 0.5
            iconPosition: QExtQml.PositionRight
            background.visible: true
            background.color: "#FDF6ED"
            border.color: "#FDF6ED"
            border.width: 1
            states: [
                State {
                    name: "checked"
                    PropertyChanges {
                        target: cb0
                        border.color: "#E6A23C"
                    }
                }
            ]
        }
    }

    Row{
        spacing: 5

        QExtQuickCheckBox{
            width: implicitWidth
            text: "C++ascdefg"
            checked: Math.random() > 0.5
            background.visible: true
            background.color: "#F0F9EB"
            border.color: "#F0F9EB"
            border.width: 1
        }

        QExtQuickCheckBox{
            width: 100
            text: "C++ascdefg1234"
            checked: Math.random() > 0.5
            background.visible: true
            background.color: "#F0F9EB"
            border.color: "#F0F9EB"
            border.width: 1
        }
        QExtQuickCheckBox{
            width: implicitWidth
            text: "C++ascdefg567"
            checked: Math.random() > 0.5
            background.visible: true
            background.color: "#F0F9EB"
            border.color: "#F0F9EB"
            border.width: 1
        }
        QExtQuickCheckBox{
            width: implicitWidth
            text: "C++asc"
            checked: Math.random() > 0.5
            background.visible: true
            background.color: "#F0F9EB"
            border.color: "#F0F9EB"
            border.width: 1
        }
        QExtQuickCheckBox{
            width: implicitWidth
            text: ""
            checked: Math.random() > 0.5
            background.visible: true
            background.color: "#F0F9EB"
            border.color: "#F0F9EB"
            border.width: 1
        }

    }

}
