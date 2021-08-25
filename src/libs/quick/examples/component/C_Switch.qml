import QtQuick 2.12
import QtQuick.Controls 2.12
import QEXTQuick 1.2

Rectangle {
    color: "lightgray"

    Column{
        spacing: 15

        Row{
            id:layout
            spacing: 10

            QEXTSwitch {
                textInLeft: true
                text: "Pay by Year"
                onStateChanged: {
                    console.warn("onStateChanged")
                }
            }

            QEXTSwitch {
                text: "Pay by Year"
            }

            QEXTSwitch {
                checked: true
                text: "Pay by Month"
            }

            QEXTSwitch {
                width: 80
                checked: true
                text: "Pay by Monthds"
            }

            QEXTSwitch {
                checked: true
            }

        }

        Row{
            spacing: 10

            QEXTSwitch {
                switchItem: switchCircleOutItem
                textInLeft: true
                text: "Pay by Year"
            }

            QEXTSwitch {
                switchItem: switchCircleOutItem
                text: "Pay by Year"
            }

            QEXTSwitch {
                switchItem: switchCircleOutItem
                checked: true
                text: "Pay by Month"
            }

            QEXTSwitch {
                switchItem: switchCircleOutItem
                width: 80
                checked: true
                text: "Pay by Monthds"
            }

            QEXTSwitch {
                switchItem: switchCircleOutItem
                checked: true
            }
        }


        Row{
            spacing: 10

            QEXTSwitch {
                switchItem: switchRectInItem
                textInLeft: true
                text: "Pay by Year"
            }

            QEXTSwitch {
                switchItem: switchRectInItem
                text: "Pay by Year"
            }

            QEXTSwitch {
                switchItem: switchRectInItem
                checked: true
                text: "Pay by Month"
            }

            QEXTSwitch {
                switchItem: switchRectInItem
                width: 80
                checked: true
                text: "Pay by Monthds"
            }

            QEXTSwitch {
                switchItem: switchRectInItem
                checked: true
            }
        }


        Row{
            spacing: 10

            QEXTSwitch {
                switchItem: switchRectOutItem
                textInLeft: true
                text: "Pay by Year"
            }

            QEXTSwitch {
                switchItem: switchRectOutItem
                text: "Pay by Year"
            }

            QEXTSwitch {
                switchItem: switchRectOutItem
                checked: true
                text: "Pay by Month"
            }

            QEXTSwitch {
                switchItem: switchRectOutItem
                width: 80
                checked: true
                text: "Pay by Monthds"
            }

            QEXTSwitch {
                switchItem: switchRectOutItem
                checked: true
            }
        }
    }

}
