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
                checked: true
            }

            QExtQuickSwitch {
                checked: true
            }

        }
    }

}
