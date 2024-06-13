import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQuick.Controls 1.2

Column{
    Row{
        spacing: 20
        Button{
            id:button
            height: 40
            text: "Loose"
            onClicked: popover.openToGlobal(button,mouseX,mouseY)
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

    // QExtQuickPopoverMenu {
    //     id:popoverMenu

    //     QExtQuickPopoverElement{
    //         type:"group"
    //         text: "BUILDING BLOCKS";
    //     }

    //     QExtQuickPopoverElement{
    //         iconSource: TAwesomeType.FA_apple
    //         text:  "Request";
    //     }

    //     QExtQuickPopoverElement{
    //         iconSource: TAwesomeType.FA_android
    //         text: "Collection";
    //     }

    //     QExtQuickPopoverElement{
    //         iconSource: TAwesomeType.FA_git
    //         text: "Environment";
    //     }

    //     QExtQuickPopoverElement{
    //         type:"group"
    //         text: "ADVANCED";
    //     }


    //     QExtQuickPopoverElement{
    //         iconSource: TAwesomeType.FA_music
    //         text: "Document";
    //     }

    //     QExtQuickPopoverElement{
    //         iconSource: TAwesomeType.FA_heartbeat
    //         text: "Mock Server";
    //     }

    //     QExtQuickPopoverElement{
    //         iconSource: TAwesomeType.FA_car
    //         text: "Monitor";
    //     }
    // }
}
