import QtQuick 2.6
import QtQuick.Controls 2.6

import QExtQuick.Controls 1.4

Rectangle {
    color: "lightgray"

    Column{
        spacing: 15

        Row{
            id:layout
            spacing: 10

            QExtQuickSwitch {
                width: 100
                height: 30
                onStateChanged: {
                    // console.warn("onStateChanged")
                }
            }

            QExtQuickSwitch {
            }

            QExtQuickSwitch {
                checked: true
            }

            QExtQuickSwitch {
                width: 80
                height: 40
                checked: true
                contentVisible: true
            }

            QExtQuickSwitch {
                width: 80
                height: 40
                radius: 5
                checked: true
                contentVisible: true
            }

            QExtQuickSwitch {
                id: cusSwitch
                width: 80
                height: 40
                radius: 5
                checked: true
                contentVisible: true
                contentComponent: Item {
                    anchors.fill: parent
                    anchors.margins: 2
                    Text {
                        text: "1"
                        visible: cusSwitch.checked
                        anchors.left: parent.left
                        verticalAlignment: Text.AlignLeft
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Text {
                        text: "0"
                        visible: !cusSwitch.checked
                        anchors.right: parent.right
                        verticalAlignment: Text.AlignRight
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }

        }
    }

}
