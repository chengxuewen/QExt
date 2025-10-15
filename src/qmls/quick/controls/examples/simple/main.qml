import QtQuick 2.12
import QtQuick.Window 2.2

import QExtQuick.Controls 1.3

Window {
    id: root
    visible: true
    width: 550
    height: 700

    //    Component.onCompleted: {
    //        root.showMaximized()
    //        root.showNormal()
    //    }


    QExtQuickButton {
        anchors.centerIn: parent
    }

    //    QExtQuickToolButton {
    //        iconColor: "Red"
    //        iconSource: ""

    //    }

    Component.onCompleted: {
        console.log("onCompleted")
    }
}
