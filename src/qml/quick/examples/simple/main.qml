import QtQuick 2.9
import QtQuick.Window 2.2
import QEXTQmlQuick 1.0

Window {
    id: root
    visible: true
    width: 550
    height: 700

    //    Component.onCompleted: {
    //        root.showMaximized()
    //        root.showNormal()
    //    }

    QEXTQmlQuickBorderGadget {

    }

//    QEXTQmlQuickButton {
//        textColor: "Red"
//        anchors.centerIn: parent
//    }

//    QEXTQmlQuickIconButton {
//        iconColor: "Red"
//        iconSource: ""

//    }

    Component.onCompleted: {
        console.log("onCompleted")
    }
}
