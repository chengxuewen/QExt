import QtQml 2.9
import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQml 1.3
import QExtQuick.Controls 1.3

Item {
    id: root
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

        x: width * (1 - root.percentage) * -1

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

    QExtQuickMask {
        anchors.fill: parent
        sourceItem: mBackgroundComponentLoader
        maskItem: mask
    }

    QExtQmlObject {
        id: mPrivate
        property bool moveing: false

        function percentage() {
            var cv = root.value + root.startValue
            if (root.maxValue <= 0 || cv <= 0) {
                return 0
            } else if (cv >= root.maxValue) {
                return 1
            }
            return cv / root.maxValue
        }

        function format() {
            var str =  root.format
            if (!str) {
                return ""
            }
            str = str.replace(/\$p/g, Math.floor(percentage() * 100))
            str = str.replace(/\$max/g, root.maxValue)
            str = str.replace(/\$s/g, root.startValue)
            str = str.replace(/\$v/g, root.value)
            return str
        }
    }

    QExtQuickBackgroundGadget {
        id: mBackgroundGadget
        color: "#EBEEF5"
        width: root.width
        height: root.height
        radius: height / 2
    }

    QExtQuickBackgroundGadget {
        id: mForegroundGadget
        color: "#46A0FC"
        width: root.width
        height: root.height
        radius: height / 2
    }
}
