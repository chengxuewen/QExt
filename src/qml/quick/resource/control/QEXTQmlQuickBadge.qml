import QtQuick 2.9
import QtQuick.Controls 2.9
import QEXTQmlQuick 1.0

Rectangle {
    id: qextBadge
    radius: height / 2
    color: QEXTQmlQuickPalette.brandPrimaryColor
    border.width: 0
    border.color: QEXTQmlQuickPalette.borderLevel1Color
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
