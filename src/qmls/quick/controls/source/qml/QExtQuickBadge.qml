import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQuick.Controls 1.2

Rectangle {
    id: root
    radius: height / 2
    color: QExtQuickPalette.brandPrimaryColor
    border.width: 0
    border.color: QExtQuickPalette.borderLevel1Color
    width: {
        if (contentLabel.contentWidth + padding < height) {
            return height
        }
        return contentLabel.contentWidth + padding * 1.6
    }
    height: {
        return padding + contentLabel.contentHeight
    }

    property int max: 0
    property int value : 0
    property int padding: 6

    property alias label: contentLabel

    Label {
        id: contentLabel
        anchors.centerIn: parent

        text: {
            if (max > 0 && value > max) {
                return max + "+"
            }
            return value
        }
        color: "#FFFFFF"
    }
}
