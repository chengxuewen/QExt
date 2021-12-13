import QtQuick 2.12
import QtQuick.Window 2.2
import QEXTQuick 1.0

Window {
    id: root
    visible: true
    width: 550
    height: 700

    //    Component.onCompleted: {
    //        root.showMaximized()
    //        root.showNormal()
    //    }

    QEXTQuickBorderGadget {

    }

//    QEXTButton {
//        textColor: "Red"
//        anchors.centerIn: parent
//    }

//    QEXTIconButton {
//        iconColor: "Red"
//        iconSource: ""

//    }

    Component.onCompleted: {
        console.log("onCompleted")
    }
}
