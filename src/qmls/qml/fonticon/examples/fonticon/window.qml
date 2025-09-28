import QtQml 2.0
import QtQuick 2.0
import QtQuick.Window 2.2

import QExtQml.FontIcon 1.4

Window {
    width: 600
    height: 400
    visible: true

    Component.onCompleted: {
        console.warn("QExtQmlFontIcon.version():", QExtQmlFontIcon.version())
    }

    Rectangle {
        width: 100
        height: 100
        color: "red"
        anchors.centerIn: parent
    }
}
