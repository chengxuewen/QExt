import QtQuick 2.12
import QtQml 2.12
import QtQuick.Controls 2.12

import QEXTQuick 1.0

Item {
    id: qextPagination
    width: mContent.width
    height: mContent.height

    signal triggered(var index)

    property int currentIndex: 0
    property int count: 3
    property int spacing: 2

    property alias itemBackground: mItemBackgroundGadget
    property alias itemActiveBg: mItemActiveBackgroundGadget
    property alias itemBorder: mItemBorderGadget
    property alias itemActiveBorder:mItemActiveBorderGadget

    property Component contentItem

    contentItem: QEXTButton {
        background: null
        padding: 12
        opacity: mItemBackgroundGadget.opacity
        contentItem: Rectangle {
            property bool active: currentIndex === index
            width: active ? mItemActiveBackgroundGadget.width : mItemBackgroundGadget.width
            height: active ? mItemActiveBackgroundGadget.height : mItemBackgroundGadget.height
            radius: active ? mItemActiveBackgroundGadget.radius : mItemBackgroundGadget.radius
            border.width: active ? mItemActiveBorderGadget.width : mItemBorderGadget.width
            border.color: active ? mItemActiveBorderGadget.color : mItemBorderGadget.color
            color: active ? mItemActiveBackgroundGadget.color : mItemBackgroundGadget.color
        }
        onClicked: {
            qextPagination.triggered(index)
        }
    }

    Row {
        id: mContent
        spacing: qextPagination.spacing

        Repeater {
            model: qextPagination.count
            delegate: contentItem
        }
    }

    QEXTQuickBackgroundGadget {
        id: mItemBackgroundGadget
        color: "#ECECEC"
        radius: 2
        width: 25
        height: 4
    }

    QEXTQuickBackgroundGadget {
        id: mItemActiveBackgroundGadget
        color: "#FC6A21"
        radius: 2
        width: 25
        height: 4
    }

    QEXTQuickBorderGadget {
        id: mItemBorderGadget
    }

    QEXTQuickBorderGadget {
        id: mItemActiveBorderGadget
    }
}
