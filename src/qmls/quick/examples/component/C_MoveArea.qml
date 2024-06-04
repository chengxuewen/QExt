import QtQuick 2.12
import QExtQuick 1.2

Item {
    clip: true

    Rectangle {
        x: 10
        y: 10
        width: 100
        height: 200
        color: "LightGray"

        QExtQuickMoveArea {
            anchors.fill: parent
        }
    }
    Rectangle {
        x: 200
        y: 200
        width: 50
        height: 20
        color: "Red"
        QExtQuickMoveArea {
            anchors.fill: parent
        }
    }
    Rectangle {
        x: 100
        y: 100
        width: 50
        height: 10
        color: "Gray"
        QExtQuickMoveArea {
            anchors.fill: parent
        }
    }

}
