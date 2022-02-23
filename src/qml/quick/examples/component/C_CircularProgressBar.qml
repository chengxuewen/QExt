import QtQuick 2.9

import QEXTQmlQuick 1.0

Item {
    Row {
        anchors.centerIn: parent
        spacing: 20

        QEXTQmlQuickCircularProgressBar {
            id: progress1
            lineWidth: 10
            value: 0.01
            size: 150
            secondaryColor: "#e0e0e0"
            primaryColor: "#29b6f6"

            Text {
                text: parseInt(progress1.value * 100) + "%"
                anchors.centerIn: parent
                font.pointSize: 20
                color: progress1.primaryColor
            }
        }

        QEXTQmlQuickCircularProgressBar {
            id: progress2
            lineWidth: 10
            value: 0.33
            size: 150
            secondaryColor: "#e0e0e0"
            primaryColor: "#ab47bc"

            Text {
                text: parseInt(progress2.value * 100) + "%"
                anchors.centerIn: parent
                font.pointSize: 20
                color: progress2.primaryColor
            }
        }

        QEXTQmlQuickCircularProgressBar {
            id: progress3
            lineWidth: 10
            value: 0.50
            size: 150
            secondaryColor: "#e0e0e0"
            primaryColor: "#9ccc65"

            Text {
                text: parseInt(progress3.value * 100) + "%"
                anchors.centerIn: parent
                font.pointSize: 20
                color: progress3.primaryColor
            }
        }

        QEXTQmlQuickCircularProgressBar {
            id: progress4
            lineWidth: 10
            value: 0.75
            size: 150
            secondaryColor: "#e0e0e0"
            primaryColor: "#f44336"

            Text {
                text: parseInt(progress4.value * 100) + "%"
                anchors.centerIn: parent
                font.pointSize: 20
                color: progress4.primaryColor
            }
        }

        QEXTQmlQuickCircularProgressBar {
            id: progress5
            lineWidth: 10
            value: 1
            size: 150
            secondaryColor: "#e0e0e0"
            primaryColor: "#4db6ac"

            Text {
                text: parseInt(progress5.value * 100) + "%"
                anchors.centerIn: parent
                font.pointSize: 20
                color: progress5.primaryColor
            }
        }
    }
}
