import QtQuick 2.7
import QtQuick.Controls 2.12
import QEXTQuick 1.2

Flickable {
    id: qextCollapse
    clip: true
    contentWidth: width
    contentHeight: mCollapseColumn.implicitHeight
    ScrollBar.vertical: ScrollBar {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
    ScrollBar.horizontal: ScrollBar {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }

    property bool separatorLineVisiable: true
    property bool accordionMode: false
    property real padding: 5
    property real spacing: 5

    property bool backgroundVisiable: false
    property color backgroundColor: "#FFFFFF"
    property real backgroundOpacity: 1
    property color backgroundBorderColor: QEXTQuickPalette.borderLevel1Color
    property real backgroundBorderWidth: 1
    property real backgroundRadius: 2

    property real titleHeight: 30
    property real titlePadding: 5
    property int titleTextHorizontalAlignment: Text.AlignHCenter
    property int titleTextElide: Text.ElideRight
    property font titleTextFont
    property bool titleBackgroundVisiable: false
    property color titleBackgroundColor: "#FCFCFC"
    property real titleBackgroundOpacity: 1
    property color titleBackgroundBorderColor: "#DCDCDC"
    property real titleBackgroundBorderWidth: 1
    property real titleBackgroundRadius: 0

    property bool titleIndicatorIconInLeft: false
    property string titleIndicatorIconSource: QEXTQuickFontAwesome.FA_angle_right
    property int titleIndicatorIconExpandRotation: 90
    property color titleIndicatorIconColor: "#2D2D2D"
    property real titleIndicatorIconWidth: titleHeight / 2
    property real titleIndicatorIconHeight: titleHeight / 2
    property real titleIconWidth: titleHeight / 2
    property real titleIconHeight: titleHeight / 2

    default property list<QEXTCollapseElement> childElements
    readonly property alias currentElement: mPrivate.currentElement
    readonly property alias childItems: mPrivate.childItems
    readonly property alias currentItem: mPrivate.currentItem

    function expandAll() {
        for (var i in mPrivate.childItems) {
            if (!!mPrivate.childItems[i]) {
                mPrivate.childItems[i].elementCollapsed = false
            }
        }
    }
    function collapseAll() {
        for (var i in mPrivate.childItems) {
            if (!!mPrivate.childItems[i]) {
                mPrivate.childItems[i].elementCollapsed = true
            }
        }
    }

    QtObject {
        id: mPrivate
        property var currentElement
        property Item currentItem
        property list<Item> childItems
    }

    Component.onCompleted: {
        for (var i in childElements) {
            mCollapseColumnRepeater.model.append(childElements[i])
        }
    }

    Column {
        id: mCollapseColumn
        anchors.fill: parent
        anchors.margins: qextCollapse.padding
        spacing: qextCollapse.spacing

        Repeater {
            id: mCollapseColumnRepeater
            model: ListModel {}
            delegate: Column {
                id: mCollapseItem
                spacing: 5
                padding: 0
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter

                property var modelData: model
                property bool elementEnabled: !!modelData.enabled ? modelData.enabled : false
                property bool elementCollapsed: modelData.defaultCollapsed

                property int elementExpandHeight: 0
                property int elementCollapsedHeight: qextCollapse.titleHeight

                onElementCollapsedChanged: {
                    if (qextCollapse.accordionMode && !mCollapseItem.elementCollapsed) {
                        mPrivate.currentElement = modelData
                        mPrivate.currentItem = mCollapseItem
                        collapseOtherItem()
                    }
                }
                Component.onCompleted: {
                    mPrivate.childItems.push(mCollapseItem)
                    if (qextCollapse.accordionMode && !elementCollapsed) {
                        mPrivate.currentItem = mCollapseItem
                    }
                }

                function expand() {
                    mCollapseElementBackground.height = elementExpandHeight
                    elementCollapsed = false
                }
                function collapse() {
                    mCollapseElementBackground.height = elementCollapsedHeight
                    elementCollapsed = true
                }

                function collapseOtherItem() {
                    for (var i in mPrivate.childItems) {
                        if (mPrivate.childItems[i] !== qextCollapse.currentItem) {
                            mPrivate.childItems[i].collapse()
                        }
                    }
                }

                Loader {
                    width: parent.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    sourceComponent: (0 === index && qextCollapse.separatorLineVisiable ) ? mSeparatorLineComponent : null
                }
                Rectangle {
                    id: mCollapseElementBackground
                    width: parent.width
                    height: mCollapseItem.elementCollapsed ? mCollapseItem.elementCollapsedHeight :
                                                             mCollapseItem.elementExpandHeight
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: qextCollapse.backgroundVisiable ? qextCollapse.backgroundColor : Qt.rgba(0, 0, 0, 0)
                    opacity: qextCollapse.backgroundOpacity
                    border.color: qextCollapse.backgroundVisiable ? qextCollapse.backgroundBorderColor : Qt.rgba(0, 0, 0, 0)
                    border.width: qextCollapse.backgroundBorderWidth
                    radius: qextCollapse.backgroundRadius
                    clip: true

                    Behavior on height {
                        NumberAnimation {
                            duration: 200
                        }
                    }

                    Rectangle {
                        id: mCollapseElementTitle
                        width: parent.width
                        height: qextCollapse.titleHeight
                        anchors.top: parent.top
                        anchors.horizontalCenter: parent.horizontalCenter
                        enabled: mCollapseItem.elementEnabled
                        color: qextCollapse.titleBackgroundVisiable ? qextCollapse.titleBackgroundColor : Qt.rgba(0, 0, 0, 0)
                        opacity: qextCollapse.titleBackgroundOpacity
                        border.color: qextCollapse.titleBackgroundVisiable ? qextCollapse.titleBackgroundBorderColor : Qt.rgba(0, 0, 0, 0)
                        border.width: qextCollapse.titleBackgroundBorderWidth
                        radius: qextCollapse.titleBackgroundRadius
                        clip: true

                        Row {
                            id: mCollapseElementRow
                            anchors.fill: parent
                            padding: qextCollapse.titlePadding
                            layoutDirection: qextCollapse.titleIndicatorIconInLeft ? Qt.RightToLeft : Qt.LeftToRight

                            QEXTIcon {
                                id: mTitleIcon
                                width: qextCollapse.titleIconWidth
                                height: qextCollapse.titleIconHeight
                                anchors.verticalCenter: parent.verticalCenter
                                source: modelData.titleIconSource
                                color: modelData.titleIconColor
                            }
                            Text {
                                id: mTitleText
                                width: parent.width - qextCollapse.titleIconWidth - qextCollapse.titleIndicatorIconWidth -
                                       qextCollapse.titlePadding * 2
                                height: parent.height
                                horizontalAlignment: qextCollapse.titleTextHorizontalAlignment
                                verticalAlignment: Qt.AlignVCenter
                                anchors.verticalCenter: parent.verticalCenter
                                text: modelData.titleText
                                font: qextCollapse.titleTextFont
                                color: modelData.titleTextColor
                                opacity: modelData.titleTextOpacity
                            }
                            QEXTIcon {
                                id: mTitleIndicatorIcon
                                width: qextCollapse.titleIndicatorIconWidth
                                height: qextCollapse.titleIndicatorIconHeight
                                anchors.verticalCenter: parent.verticalCenter
                                color: qextCollapse.titleIndicatorIconColor
                                source: qextCollapse.titleIndicatorIconSource
                                rotation: elementCollapsed ? 0 : qextCollapse.titleIndicatorIconExpandRotation
                                Behavior on rotation {
                                    NumberAnimation {
                                        duration: 200
                                    }
                                }
                            }
                        }


                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if (mCollapseItem.elementEnabled) {
                                    if (mCollapseItem.elementCollapsed) {
                                        mCollapseItem.expand()
                                    } else {
                                        mCollapseItem.collapse()
                                    }
                                }
                            }
                        }

                    }

                    Loader {
                        id: mCollapseElementContentLoader
                        width: parent.width
                        anchors.top: mCollapseElementTitle.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        sourceComponent: modelData.contentItem
                        Component.onCompleted: {
                            mCollapseItem.elementExpandHeight = mCollapseElementTitle.implicitHeight + implicitHeight
                        }
                    }
                }

                Loader {
                    width: parent.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    sourceComponent: qextCollapse.separatorLineVisiable ? mSeparatorLineComponent : null
                }

            }
        }
    }

    Component {
        id: mSeparatorLineComponent
        Rectangle {
            width: parent.width
            height: 1
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#bdbdbd"
        }
    }

}
