import QtQuick 2.9
import QEXTQmlQuick 1.0

Item {
    clip: true

    Rectangle {
        x: 10
        y: 10
        width: 100
        height: 200
        color: "LightGray"

        QEXTQmlQuickResizeArea {
            anchors.fill: parent
        }
    }
    Rectangle {
        x: 200
        y: 200
        width: 50
        height: 20
        color: "Red"
        QEXTQmlQuickResizeArea {
            anchors.fill: parent
        }
    }
    Rectangle {
        x: 100
        y: 100
        width: 50
        height: 10
        color: "Gray"
        QEXTQmlQuickResizeArea {
            anchors.fill: parent
        }
    }
}
