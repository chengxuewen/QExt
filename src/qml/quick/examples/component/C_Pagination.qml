import QtQuick 2.9
import QEXTQmlQuick 1.0

Column{
    id:layout
    spacing: 15

    property int index: 0

    property int count: 6

    QEXTQmlQuickPagination {
        anchors.horizontalCenter: parent.horizontalCenter
        count: parent.count
        currentIndex: layout.index
        onTriggered: parent.index = index
    }


    QEXTQmlQuickPagination {
        anchors.horizontalCenter: parent.horizontalCenter
        count: parent.count
        currentIndex: layout.index
        itemBackground.width:  10
        itemBackground.height: 10
        itemBackground.radius: 5
        itemActiveBg.width: 10
        itemActiveBg.height: 10
        itemActiveBg.radius: 5
        itemActiveBg.color: "#46A0FC"
        onTriggered:  parent.index = index
    }


    QEXTQmlQuickPagination {
        id:pagination
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 15
        count: parent.count
        currentIndex: layout.index
        onTriggered:  layout.index = index


        itemBackground.width: 25
        itemBackground.height: 25

        itemBackground.color: "#FDFDFD"
        itemActiveBg.color:"#F56C6C"

        contentItem: QEXTQmlQuickButton{
            id:customItem
            property bool active: layout.index === index
            text: index + 1

            width:  pagination.itemBackground.width
            height: pagination.itemBackground.height
            backgroundRadius: pagination.itemActiveBg.radius

            backgroundBorderWidth: 1
            backgroundBorderColor: active ? pagination.itemActiveBorder.color : pagination.itemBorder.color
            backgroundColor: active ? pagination.itemActiveBg.color : pagination.itemBackground.color
            textColor: active ? "#FFF" : "#5d5d5d"
            textFont.bold: active
            onClicked: layout.index = index
        }
    }

}
