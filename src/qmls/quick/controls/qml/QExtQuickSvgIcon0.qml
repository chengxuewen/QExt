import QtQuick 2.6
import QtQuick.Effects

Item {
    id: mControl
    anchors.fill: parent

    property color color
    property string source
    property bool smooth: true
    property bool asynchronous: true

    property alias status: mImage.status

    Image {
        id: mImage
        asynchronous: mControl.asynchronous
        anchors.fill: mControl
        source:  mControl.source
        smooth: mControl.smooth
        visible: false
        enabled: false
    }
    MultiEffect {
        source: mImage
        anchors.fill: mImage
        brightness: 1
        colorization: 1.0
        colorizationColor: mControl.color
    }
}
