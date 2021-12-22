import QtQuick 2.12
import QtQml 2.12
import QtQuick.Controls 2.12

import QEXTQuick 1.0

Item {
    id: qextProgressBar
    clip: true
    width: 300
    height: 10

    property string format:"loading $p %"
    property double value : 0
    property double maxValue: 100
    property double startValue: 0

    readonly property double percentage: mPrivate.percentage()
    readonly property string formatText : mPrivate.format()

    property alias background: mBackgroundGadget
    property alias foreground: mForegroundGadget

    property Component maskItem: null
    property Component backgroundItem
    property Component foregroundItem

    Loader {
        id: mBackgroundComponentLoader
        anchors.fill: parent
        sourceComponent: backgroundItem

        Loader {
            id: mForegroundComponentLoader
            width: parent.width
            height: parent.height
            sourceComponent: foregroundItem
            z: 1
        }
    }

    backgroundItem: Rectangle {
        color: mBackgroundGadget.color
        radius: mBackgroundGadget.radius
    }

    foregroundItem: Rectangle {
        color: mForegroundGadget.color
        radius: mForegroundGadget.radius

        x: width * (1 - qextProgressBar.percentage) * -1

        Behavior on x {
            id: behavior
            enabled: false
            NumberAnimation {
                duration: 200
            }
        }
        Timer {
            interval: 20
            running: true
            onTriggered: behavior.enabled = true
        }
    }

    maskItem: Rectangle {
        width: mBackgroundComponentLoader.width
        height: mBackgroundComponentLoader.height
        radius: mBackgroundGadget.radius
    }

    Loader {
        id: mask
        sourceComponent: maskItem
    }

    QEXTMask {
        anchors.fill: parent
        sourceItem: mBackgroundComponentLoader
        maskItem: mask
    }

    QEXTObject {
        id: mPrivate
        property bool moveing: false

        function percentage() {
            var cv = qextProgressBar.value + qextProgressBar.startValue
            if (qextProgressBar.maxValue <= 0 || cv <= 0) {
                return 0
            } else if (cv >= qextProgressBar.maxValue) {
                return 1
            }
            return cv / qextProgressBar.maxValue
        }

        function format() {
            var str =  qextProgressBar.format
            if (!str) {
                return ""
            }
            str = str.replace(/\$p/g, Math.floor(percentage() * 100))
            str = str.replace(/\$max/g, qextProgressBar.maxValue)
            str = str.replace(/\$s/g, qextProgressBar.startValue)
            str = str.replace(/\$v/g, qextProgressBar.value)
            return str
        }
    }

    QEXTQuickBackgroundGadget {
        id: mBackgroundGadget
        color: "#EBEEF5"
        width: qextProgressBar.width
        height: qextProgressBar.height
        radius: height / 2
    }

    QEXTQuickBackgroundGadget {
        id: mForegroundGadget
        color: "#46A0FC"
        width: qextProgressBar.width
        height: qextProgressBar.height
        radius: height / 2
    }
}
