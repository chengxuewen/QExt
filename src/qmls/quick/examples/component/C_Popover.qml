import QtQuick 2.12
import QEXTQmlQuick 1.0

Column{
    Row{
        spacing: 20
        QEXTQmlQuickButton{
            id:button
            height: 40
            label.text: "Loose"
            label.color: "#46A0FC"
            onClicked: popover.openToGlobal(button,mouseX,mouseY)
        }

        QEXTQmlQuickButton{
            id:bmenu
            height: 40
            label.text: "Popover Menu"
            label.color: "#46A0FC"
            onClicked: popoverMenu.openToGlobal(bmenu,mouseX,mouseY)
        }


        QEXTQmlQuickButton{
            id:b2
            height: 40
            label.text: "Fixed"
            label.color: "#46A0FC"
            onClicked: popover.openToGlobal(b2,0,b2.height)
        }
    }

    QEXTPopover{
        id:popover
    }

    QEXTMenu{
        id:popoverMenu

        QEXTMenuElement{
            type:"group"
            text: "BUILDING BLOCKS"
        }

        QEXTMenuElement{
            iconSource: QEXTAwesomeType.FA_apple
            text:  "Request"
        }

        QEXTMenuElement{
            iconSource: QEXTAwesomeType.FA_android
            text: "Collection"
        }

        QEXTMenuElement{
            iconSource: QEXTAwesomeType.FA_git
            text: "Environment"
        }

        QEXTMenuElement{
            type:"group"
            text: "ADVANCED"
        }


        QEXTMenuElement{
            iconSource: QEXTAwesomeType.FA_music
            text: "Document"
        }

        QEXTMenuElement{
            iconSource: QEXTAwesomeType.FA_heartbeat
            text: "Mock Server"
        }

        QEXTMenuElement{
            iconSource: QEXTAwesomeType.FA_car
            text: "Monitor"
        }

    }
}
