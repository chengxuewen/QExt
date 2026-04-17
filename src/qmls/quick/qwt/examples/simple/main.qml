import QtQml 2.0
import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0

import QExtQuick.Qwt 1.4
import MYQExtQuickQwtPlot 1.1

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

        Rectangle {
            anchors.fill: parent
            color: "blue"
            MYQExtQuickQwtPlot {
                id: qwtPlot
//                opacity: 0.3
                anchors.fill: parent
                Component.onCompleted: {
                    setAxisVisible(QExtQuickQwtPlot.AxisBottom, false)
                }
            }
        }
    }
}
