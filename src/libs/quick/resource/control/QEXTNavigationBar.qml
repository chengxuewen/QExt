import QtQuick 2.12
import QtQml 2.12
import QtQuick.Controls 2.12
import QEXTQuick 1.2

Item {
    id: qextNavigationBar
    width: mContentLayoutLoader.width
    height: mContentLayoutLoader.height

    signal triggered(var modelData)

    property real itemScale: 1
    property real itemActiveScale: 1
    property real itemWidth: 0
    property real itemHeight: 0
    property real itemSpacing: 10
    property real itemPadding: 8
    property real itemLeftPadding: 8
    property real itemTopPadding: 8
    property real itemRightPadding: 8
    property real itemBottomPadding: 8
    property int orientation: Qt.Horizontal
    property int itemIconDisplay: QEXTQuick.IconDisplay_Left

    property int currentIndex: -1

    property bool backgroundVisiable: true
    property color backgroundColor: "#FFFFFF"
    property real backgroundOpacity: 1
    property color backgroundBorderColor: QEXTQuickPalette.borderLevel1Color
    property real backgroundBorderWidth: 1
    property real backgroundRadius: 2

    property bool itemBackgroundVisiable: false
    property bool itemBackgroundBorderVisiable: false
    property real itemBackgroundRadius: 2
    property color itemBackgroundColor: "#FFFFFF"
    property real itemBackgroundOpacity: 1
    property color itemBackgroundBorderColor: QEXTQuickPalette.borderLevel2Color
    property real itemBackgroundBorderWidth: 1
    property color itemActiveBackgroundColor: "#FFFFFF"
    property real itemActiveBackgroundOpacity: 1
    property color itemActiveBackgroundBorderColor: QEXTQuickPalette.borderLevel1Color
    property real itemActiveBackgroundBorderWidth: 1

    property font itemTextFont
    property color itemTextColor: QEXTQuickPalette.textNormalColor
    property real itemTextOpacity: 1
    property font itemActiveTextFont
    property color itemActiveTextColor: QEXTQuickPalette.textPrimaryColor
    property real itemActiveTextOpacity: 1

    property real itemIconWidth: 25
    property real itemIconHeight: 25
    property real itemIconPadding: 10
    property real itemIconSpacing: 5
    property real itemIconScale: 1
    property color itemIconColor: "#303133"
    property real itemActiveIconScale: 1.2
    property color itemActiveIconColor: "#000"
    property int itemTextHorizontalAlignment: Qt.AlignHCenter
    property int itemTextVerticalAlignment: Qt.AlignVCenter

    default property list<QEXTNavigationElement> childElements
    readonly property alias currentItem: mPrivate.currentItem
    readonly property alias childItems: mPrivate.childItems

    property Component itemComponent

    itemComponent: QEXTIconButton {
        id: mIconButton
        leftPadding: itemLeftPadding
        topPadding: itemTopPadding
        rightPadding: itemRightPadding
        bottomPadding: itemBottomPadding
        scale: isActiveItem ? itemActiveScale : itemScale

        backgroundRadius: itemBackgroundRadius
        backgroundVisiable: itemBackgroundVisiable
        backgroundColor: isActiveItem ? itemActiveBackgroundColor : itemBackgroundColor
        backgroundOpacity: isActiveItem ? itemActiveBackgroundOpacity : itemBackgroundOpacity

        backgroundBorderVisiable: itemBackgroundBorderVisiable
        backgroundBorderColor: isActiveItem ? itemActiveBackgroundBorderColor : itemBackgroundBorderColor
        backgroundBorderWidth: isActiveItem ? itemActiveBackgroundBorderWidth : itemBackgroundBorderWidth

        text: modelData.text || modelData.iconSource ? modelData.text : modelData.index
        textColor: isActiveItem ? itemActiveTextColor : itemTextColor
        textFont: isActiveItem ? itemActiveTextFont : itemTextFont
        textOpacity: isActiveItem ? itemActiveTextOpacity : itemTextOpacity
        textHorizontalAlignment: itemTextHorizontalAlignment
        textVerticalAlignment: itemTextVerticalAlignment

        iconSource: modelData.iconSource
        iconWidth: itemIconWidth
        iconHeight: itemIconHeight
        iconDisplay: itemIconDisplay
        iconScale: isActiveItem ? itemActiveIconScale : itemIconScale
        iconColor: isActiveItem ? itemActiveIconColor : itemIconColor

        onClicked: {
            qextNavigationBar.currentIndex = modelData.index
            triggered(modelData)
        }

        Timer {
            interval: 10
            running: true
            onTriggered: {
                if (itemWidth > 0) {
                    width = itemWidth
                }
                if (itemHeight > 0) {
                    height = itemHeight
                }
            }
        }
    }

    QEXTObject {
        id: mPrivate
        property list<Item> childItems
        property Item currentItem
    }

    Loader {
        id: mContentLayoutLoader
        sourceComponent: Qt.Horizontal === orientation ? mHorizontalContentLayoutComponent : mVerticalContentLayoutComponent
    }

    Component {
        id: mHorizontalContentLayoutComponent
        Row {
            id: mContentLayout
            spacing: qextNavigationBar.itemSpacing
            Repeater {
                id: mHorizontalContentLayoutRepeater
                model: mItemListModel
                delegate: Loader {
                    id: loader
                    property var modelData: model
                    property bool isActiveItem: qextNavigationBar.currentIndex === index

                    anchors.verticalCenter: parent.verticalCenter
                    sourceComponent: itemComponent
                    onIsActiveItemChanged: {
                        if (isActiveItem) {
                            mPrivate.currentItem = loader
                        }
                    }
                    Component.onCompleted: {
                        mPrivate.childItems.push(loader)
                        if (isActiveItem) {
                            mPrivate.currentItem = loader
                        }
                    }
                }
            }
        }
    }

    Component {
        id: mVerticalContentLayoutComponent
        Column {
            id: mContentLayout
            spacing: qextNavigationBar.itemSpacing
            Repeater {
                id: mVerticalContentLayoutRepeater
                model: mItemListModel
                delegate: Loader {
                    id: loader
                    property var modelData: model
                    property bool isActiveItem: qextNavigationBar.currentIndex === index
                    property int itemIndex: index

                    anchors.horizontalCenter: parent.horizontalCenter
                    sourceComponent: itemComponent
                    onIsActiveItemChanged: {
                        if (isActiveItem) {
                            mPrivate.currentItem = loader
                        }
                    }
                    Component.onCompleted: {
                        mPrivate.childItems.push(loader)
                        if (isActiveItem) {
                            mPrivate.currentItem = loader
                        }
                    }
                }
            }
        }
    }

    ListModel {
        id: mItemListModel
    }


    Component.onCompleted: {
        for (var i in childElements) {
            mItemListModel.append(childElements[i])
        }
        if (childElements.length > 0 && qextNavigationBar.currentIndex === -1) {
            qextNavigationBar.currentIndex = 0
        }
    }

    function setCurrentElementByOtherData(otherData) {
        for (var i in childElements) {
            if (childElements[i] === otherData) {
                qextNavigationBar.currentIndex = i
                return
            }
        }
    }

    function setCurrentElementByIndex(index) {
        if (index >= 0 && index < childElements.length) {
            qextNavigationBar.currentIndex = index
        }
    }

    function currentElementData() {
        if (currentIndex >= 0 && currentIndex < childElements.length) {
            return childElements[currentIndex]
        }
    }
}
