import QtQuick 2.7
import QtQuick.Controls 2.12
import QEXTQuick 1.2

Column{
    spacing: 8

    Row{
        spacing: 5
        anchors.horizontalCenter: parent.horizontalCenter

        QEXTCheckBox{
            text: "MoviesDFVasdvasdfv"
        }

        QEXTCheckBox{
            text: "Music34523462346234"
            width: 100
            checked: true
        }

        QEXTCheckBox{
            text: "Running"
        }

        QEXTCheckBox{
            text: "Fitness"
            checked: true
        }

        QEXTCheckBox{
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

        QEXTCheckBox{
            text: "Movie"
        }

        QEXTCheckBox{
            text: "Music"
            checked: true
        }

        QEXTCheckBox{
            text: "Running"
            checkState: Qt.PartiallyChecked
            tristate: true
        }

        QEXTCheckBox{
            text: "Fitness"
            tristate: true
            checked: true
        }

        QEXTCheckBox{
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

        QEXTCheckBox{
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

        QEXTCheckBox{
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

        QEXTCheckBox{
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

        QEXTCheckBox{
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
