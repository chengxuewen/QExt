import QtQml 2.0
import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.2

import QExtQml 1.4

Window {
    width: 600
    height: 400
    visible: true

    property string ver: QExtQml.version

    QExtQmlBorderInfo {
        leftWidth: 2
    }

    QExtQmlPaddingInfo {
        leftPadding: 3
    }

    QExtQmlObject {

    }
    QExtQmlRectangleInfo {
        color: "red"
    }
    QExtQmlTextInfo {
        font.bold: true
    }

    Text {
        id: name
        text: qsTr("text")
    }

    Rectangle {
        color: "red"
        anchors.fill: parent
    }

    Button {
        width: 100
        height: 60
        text: QExtQml.version
        anchors.centerIn: parent
    }

    Component.onCompleted: {
        console.warn("QExtQml.version()=", QExtQml.version);
    }
}
