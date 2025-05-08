import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQuick.Controls 1.3

Column{
    Row{
        spacing: 20
        Button{
            id:button
            height: 40
            text: "Loose"
            onClicked: popover.openToGlobal(button, mouseX, mouseY)
        }

        // Button{
        //     id:bmenu
        //     height: 40
        //     text: "Popover Menu"
        //     onClicked: popoverMenu.openToGlobal(bmenu,mouseX,mouseY)
        // }


        Button{
            id:b2
            height: 40
            text: "Fixed"
            onClicked: popover.openToGlobal(b2,0,b2.height)
        }
    }

    QExtQuickPopover {
        id:popover
    }
}
