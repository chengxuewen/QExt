import QtQuick 2.12
import QtQuick.Controls 2.12
import QExtQuick.Controls 1.3

Column{
    spacing: 15

    Row{
        spacing: 40

        Button{
            text: "Button"
            QExtQuickBadge{
                id:b1
                x:parent.width - width /2
                y:height / 2 * -1
            }

            onClicked:b1.value++
        }

        Button{
            text: "Button"
            QExtQuickBadge{
                id:b2
                value: 100
                color: "#6ac044"
                x:parent.width - width /2
                y:height / 2 * -1
            }

            onClicked:b2.value++
        }

        Button{
            text: "Button"
            QExtQuickBadge{
                id:b3
                value: 100
                max:99
                x:parent.width - width /2
                y:height / 2 * -1
            }

            onClicked:b3.value--
        }

    }


}
