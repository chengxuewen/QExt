import QtQuick 2.12
import QtQuick.Controls 2.12
import QExtQuick.Controls 1.2

Rectangle {
    color: "lightgray"

    Column{
        spacing: 15

        Row{
            id:layout
            spacing: 10

            QExtQuickSwitch {
                textInLeft: true
                text: "Pay by Year"
                onStateChanged: {
                    console.warn("onStateChanged")
                }
            }

            QExtQuickSwitch {
                text: "Pay by Year"
            }

            QExtQuickSwitch {
                checked: true
                text: "Pay by Month"
            }

            QExtQuickSwitch {
                width: 80
                checked: true
                text: "Pay by Monthds"
            }

            QExtQuickSwitch {
                checked: true
            }

        }

        Row{
            spacing: 10

            QExtQuickSwitch {
                switchItem: switchCircleOutItem
                textInLeft: true
                text: "Pay by Year"
            }

            QExtQuickSwitch {
                switchItem: switchCircleOutItem
                text: "Pay by Year"
            }

            QExtQuickSwitch {
                switchItem: switchCircleOutItem
                checked: true
                text: "Pay by Month"
            }

            QExtQuickSwitch {
                switchItem: switchCircleOutItem
                width: 80
                checked: true
                text: "Pay by Monthds"
            }

            QExtQuickSwitch {
                switchItem: switchCircleOutItem
                checked: true
            }
        }


        Row{
            spacing: 10

            QExtQuickSwitch {
                switchItem: switchRectInItem
                textInLeft: true
                text: "Pay by Year"
            }

            QExtQuickSwitch {
                switchItem: switchRectInItem
                text: "Pay by Year"
            }

            QExtQuickSwitch {
                switchItem: switchRectInItem
                checked: true
                text: "Pay by Month"
            }

            QExtQuickSwitch {
                switchItem: switchRectInItem
                width: 80
                checked: true
                text: "Pay by Monthds"
            }

            QExtQuickSwitch {
                switchItem: switchRectInItem
                checked: true
            }
        }


        Row{
            spacing: 10

            QExtQuickSwitch {
                switchItem: switchRectOutItem
                textInLeft: true
                text: "Pay by Year"
            }

            QExtQuickSwitch {
                switchItem: switchRectOutItem
                text: "Pay by Year"
            }

            QExtQuickSwitch {
                switchItem: switchRectOutItem
                checked: true
                text: "Pay by Month"
            }

            QExtQuickSwitch {
                switchItem: switchRectOutItem
                width: 80
                checked: true
                text: "Pay by Monthds"
            }

            QExtQuickSwitch {
                switchItem: switchRectOutItem
                checked: true
            }
        }
    }

}
