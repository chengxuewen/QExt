import QtQuick 2.12

import QExtQuick.Controls 1.4

Item {
    clip: true

    Rectangle {
        x: 10
        y: 10
        width: 100
        height: 200
        color: "LightGray"

        QExtQuickResizeArea {
            anchors.fill: parent
        }
    }
    Rectangle {
        x: 200
        y: 200
        width: 50
        height: 20
        color: "Red"
        QExtQuickResizeArea {
            anchors.fill: parent
        }
    }
    Rectangle {
        x: 100
        y: 100
        width: 50
        height: 10
        color: "Gray"
        QExtQuickResizeArea {
            anchors.fill: parent
        }
    }
}
