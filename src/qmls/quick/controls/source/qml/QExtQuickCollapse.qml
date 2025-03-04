import QtQml 2.9
import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQuick.Controls 1.3

Flickable {
    id: root
    clip: true
    contentWidth: width
    contentHeight: collapseColumn.implicitHeight
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

    property bool separatorLineVisible: true
    property bool accordionMode: false
    property real padding: 5
    property real spacing: 5

    property bool backgroundVisible: false
    property color backgroundColor: "#FFFFFF"
    property real backgroundOpacity: 1
    property color backgroundBorderColor: QExtQuickPalette.borderLevel1Color
    property real backgroundBorderWidth: 1
    property real backgroundRadius: 2

    property real titleHeight: 30
    property real titlePadding: 5
    property int titleTextHorizontalAlignment: Text.AlignHCenter
    property int titleTextElide: Text.ElideRight
    property font titleTextFont
    property bool titleBackgroundVisible: false
    property color titleBackgroundColor: "#FCFCFC"
    property real titleBackgroundOpacity: 1
    property color titleBackgroundBorderColor: "#DCDCDC"
    property real titleBackgroundBorderWidth: 1
    property real titleBackgroundRadius: 0

    property bool titleIndicatorIconInLeft: false
    property string titleIndicatorIconSource: "qrc:/QExtQuickControls/resource/image/arrow_caret_collapse.svg"
    property int titleIndicatorIconExpandRotation: 90
    property color titleIndicatorIconColor: "#2D2D2D"
    property real titleIndicatorIconWidth: titleHeight / 2
    property real titleIndicatorIconHeight: titleHeight / 2
    property real titleIconWidth: titleHeight / 2
    property real titleIconHeight: titleHeight / 2

    property Item currentItem
    property var currentElement
    property list<Item> childItems
    default property list<QExtQuickCollapseElement> childElements

    function expandAll() {
        for (var i in root.childItems) {
            if (!!root.childItems[i]) {
                root.childItems[i].elementCollapsed = false
            }
        }
    }
    function collapseAll() {
        for (var i in root.childItems) {
            if (!!root.childItems[i]) {
                root.childItems[i].elementCollapsed = true
            }
        }
    }

    Component.onCompleted: {
        for (var i in childElements) {
            collapseColumnRepeater.model.append(childElements[i])
        }
    }

    Column {
        id: collapseColumn
        anchors.fill: parent
        anchors.margins: root.padding
        spacing: root.spacing

        Repeater {
            id: collapseColumnRepeater
            model: ListModel {}
            delegate: Column {
                id: collapseItem
                spacing: 5
                padding: 0
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter

                property var modelData: model
                property bool elementEnabled: !!modelData.enabled ? modelData.enabled : false
                property bool elementCollapsed: modelData.defaultCollapsed

                property int elementExpandHeight: 0
                property int elementCollapsedHeight: root.titleHeight

                onElementCollapsedChanged: {
                    if (root.accordionMode && !collapseItem.elementCollapsed) {
                        root.currentElement = modelData
                        root.currentItem = collapseItem
                        collapseOtherItem()
                    }
                }
                Component.onCompleted: {
                    root.childItems.push(collapseItem)
                    if (root.accordionMode && !elementCollapsed) {
                        root.currentItem = collapseItem
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
                    for (var i in root.childItems) {
                        if (root.childItems[i] !== root.currentItem) {
                            root.childItems[i].collapse()
                        }
                    }
                }

                Loader {
                    width: parent.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    sourceComponent: (0 === index && root.separatorLineVisible ) ? mSeparatorLineComponent : null
                }
                Rectangle {
                    id: mCollapseElementBackground
                    width: parent.width
                    height: collapseItem.elementCollapsed ? collapseItem.elementCollapsedHeight :
                                                            collapseItem.elementExpandHeight
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: root.backgroundVisible ? root.backgroundColor : Qt.rgba(0, 0, 0, 0)
                    opacity: root.backgroundOpacity
                    border.color: root.backgroundVisible ? root.backgroundBorderColor : Qt.rgba(0, 0, 0, 0)
                    border.width: root.backgroundBorderWidth
                    radius: root.backgroundRadius
                    clip: true

                    Behavior on height {
                        NumberAnimation {
                            duration: 200
                        }
                    }

                    Rectangle {
                        id: collapseElementTitle
                        width: parent.width
                        height: root.titleHeight
                        anchors.top: parent.top
                        anchors.horizontalCenter: parent.horizontalCenter
                        enabled: collapseItem.elementEnabled
                        color: root.titleBackgroundVisible ? root.titleBackgroundColor : Qt.rgba(0, 0, 0, 0)
                        opacity: root.titleBackgroundOpacity
                        border.color: root.titleBackgroundVisible ? root.titleBackgroundBorderColor : Qt.rgba(0, 0, 0, 0)
                        border.width: root.titleBackgroundBorderWidth
                        radius: root.titleBackgroundRadius
                        clip: true

                        Row {
                            id: collapseElementRow
                            anchors.fill: parent
                            padding: root.titlePadding
                            layoutDirection: root.titleIndicatorIconInLeft ? Qt.RightToLeft : Qt.LeftToRight

                            QExtQuickImage {
                                id: mTitleIcon
                                width: root.titleIconWidth
                                height: root.titleIconHeight
                                anchors.verticalCenter: parent.verticalCenter
                                source: modelData.titleIconSource
                                color: modelData.titleIconColor
                            }
                            Text {
                                id: mTitleText
                                width: parent.width - root.titleIconWidth - root.titleIndicatorIconWidth -
                                       root.titlePadding * 2
                                height: parent.height
                                horizontalAlignment: root.titleTextHorizontalAlignment
                                verticalAlignment: Qt.AlignVCenter
                                anchors.verticalCenter: parent.verticalCenter
                                text: modelData.titleText
                                font: root.titleTextFont
                                color: modelData.titleTextColor
                                opacity: modelData.titleTextOpacity
                            }
                            QExtQuickImage {
                                id: mTitleIndicatorIcon
                                width: root.titleIndicatorIconWidth
                                height: root.titleIndicatorIconHeight
                                anchors.verticalCenter: parent.verticalCenter
                                color: root.titleIndicatorIconColor
                                source: root.titleIndicatorIconSource
                                rotation: elementCollapsed ? 0 : root.titleIndicatorIconExpandRotation
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
                                if (collapseItem.elementEnabled) {
                                    if (collapseItem.elementCollapsed) {
                                        collapseItem.expand()
                                    } else {
                                        collapseItem.collapse()
                                    }
                                }
                            }
                        }

                    }

                    Loader {
                        id: mCollapseElementContentLoader
                        width: parent.width
                        anchors.top: collapseElementTitle.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        sourceComponent: modelData.contentItem
                        Component.onCompleted: {
                            collapseItem.elementExpandHeight = collapseElementTitle.implicitHeight + implicitHeight
                        }
                    }
                }

                Loader {
                    width: parent.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    sourceComponent: root.separatorLineVisible ? mSeparatorLineComponent : null
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
