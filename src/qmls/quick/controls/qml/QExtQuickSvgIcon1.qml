import QtQuick 2.6
import Qt5Compat.GraphicalEffects

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
    ColorOverlay {
        source: mImage
        anchors.fill: mImage
        color: mControl.color
    }
}
