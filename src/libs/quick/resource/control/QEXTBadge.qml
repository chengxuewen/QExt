import QtQuick 2.7
import QtQuick.Controls 2.12
import QEXTQuick 1.2

Rectangle {
    id: qextBadge
    radius: height / 2
    color: QEXTQuickPalette.brandPrimaryColor
    border.width: 0
    border.color: QEXTQuickPalette.borderLevel1Color
    width: {
        if (mContentLabel.contentWidth + padding < height) {
            return height
        }
        return mContentLabel.contentWidth + padding * 1.6
    }
    height: {
        return padding + mContentLabel.contentHeight
    }

    property int padding: 6
    property int value : 0
    property int max: 0

    property alias label: mContentLabel

    Label {
        id: mContentLabel
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
