import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQuick.Controls 1.4

Rectangle {
    QExtQuickPopup {
        id: popup

        // childitem: [Rectangle{
        //         width: 100;
        //         height: 100;
        //         color: "red"
        //         anchors.centerIn: parent;
        //     }]

        onTriggeredBackground:{
            close();
        }
    }

    Button {
        width: 100
        height: 30
        text: "open"
        anchors.centerIn: parent
        onClicked: {
            popup.open();
        }
    }
}
