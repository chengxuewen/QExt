import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0

import QExtQuick.Qwt 1.2

Window {
    id: root
    visible: true
    width: 550
    height: 700

    title: qsTr("Hello QWT in QML")

    Item {
        id: plotForm
        anchors.fill: parent

        Text {
            id: text
            text: qsTr("Plot form")
        }

        QwtQuick2Plot {
            id: qwtPlot
            anchors.fill: parent

            Component.onCompleted: initQwtPlot()
        }
    }

}
