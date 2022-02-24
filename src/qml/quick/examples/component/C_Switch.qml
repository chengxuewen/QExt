import QtQuick 2.12
import QtQuick.Controls 2.12
import QEXTQmlQuick 1.0

Rectangle {
    color: "lightgray"

    Column{
        spacing: 15

        Row{
            id:layout
            spacing: 10

            QEXTQmlQuickSwitch {
                textInLeft: true
                text: "Pay by Year"
                onStateChanged: {
                    console.warn("onStateChanged")
                }
            }

            QEXTQmlQuickSwitch {
                text: "Pay by Year"
            }

            QEXTQmlQuickSwitch {
                checked: true
                text: "Pay by Month"
            }

            QEXTQmlQuickSwitch {
                width: 80
                checked: true
                text: "Pay by Monthds"
            }

            QEXTQmlQuickSwitch {
                checked: true
            }

        }

        Row{
            spacing: 10

            QEXTQmlQuickSwitch {
                switchItem: switchCircleOutItem
                textInLeft: true
                text: "Pay by Year"
            }

            QEXTQmlQuickSwitch {
                switchItem: switchCircleOutItem
                text: "Pay by Year"
            }

            QEXTQmlQuickSwitch {
                switchItem: switchCircleOutItem
                checked: true
                text: "Pay by Month"
            }

            QEXTQmlQuickSwitch {
                switchItem: switchCircleOutItem
                width: 80
                checked: true
                text: "Pay by Monthds"
            }

            QEXTQmlQuickSwitch {
                switchItem: switchCircleOutItem
                checked: true
            }
        }


        Row{
            spacing: 10

            QEXTQmlQuickSwitch {
                switchItem: switchRectInItem
                textInLeft: true
                text: "Pay by Year"
            }

            QEXTQmlQuickSwitch {
                switchItem: switchRectInItem
                text: "Pay by Year"
            }

            QEXTQmlQuickSwitch {
                switchItem: switchRectInItem
                checked: true
                text: "Pay by Month"
            }

            QEXTQmlQuickSwitch {
                switchItem: switchRectInItem
                width: 80
                checked: true
                text: "Pay by Monthds"
            }

            QEXTQmlQuickSwitch {
                switchItem: switchRectInItem
                checked: true
            }
        }


        Row{
            spacing: 10

            QEXTQmlQuickSwitch {
                switchItem: switchRectOutItem
                textInLeft: true
                text: "Pay by Year"
            }

            QEXTQmlQuickSwitch {
                switchItem: switchRectOutItem
                text: "Pay by Year"
            }

            QEXTQmlQuickSwitch {
                switchItem: switchRectOutItem
                checked: true
                text: "Pay by Month"
            }

            QEXTQmlQuickSwitch {
                switchItem: switchRectOutItem
                width: 80
                checked: true
                text: "Pay by Monthds"
            }

            QEXTQmlQuickSwitch {
                switchItem: switchRectOutItem
                checked: true
            }
        }
    }

}
