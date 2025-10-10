import QtQml 2.9
import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQml 1.4
import QExtQml.Theme 1.4
import QExtQuick.Controls 1.4

Flickable {
    id: mControl
    clip: true
    contentWidth: width
    contentHeight: mColumn.implicitHeight
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
    property color backgroundBorderColor: QExtQmlThemePalette.borderLevel1Color
    property real backgroundBorderWidth: 1
    property real backgroundRadius: 2

    property real titleHeight: 30
    property real titlePadding: 5
    property int titleTextHorizontalAlignment: Text.AlignHCenter
    property int titleTextElide: Text.ElideRight
    property font titleTextFont

    property alias titleBorder: mTitleBorderInfo
    property alias titleBackground: mTitleBackgroundInfo

    property bool titleIndicatorIconInLeft: false
    property string titleIndicatorIconSource: "qrc:/QExtQuickControls/resources/image/arrow_caret_collapse.svg"
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
        for (var i in mControl.childItems) {
            if (!!mControl.childItems[i]) {
                mControl.childItems[i].elementCollapsed = false
            }
        }
    }
    function collapseAll() {
        for (var i in mControl.childItems) {
            if (!!mControl.childItems[i]) {
                mControl.childItems[i].elementCollapsed = true
            }
        }
    }

    Component.onCompleted: {
        for (var i in childElements) {
            mColumnRepeater.model.append(childElements[i])
        }
    }

    QExtQmlTextInfo {
        id: mTextInfo
        color: "#2D2D2D"
        text: "Button"
    }

    QExtQmlBorderInfo {
        id: mTitleBorderInfo
        color: "#DCDCDC"
        width: 1
    }

    QExtQmlBackgroundInfo {
        id: mTitleBackgroundInfo
        color: "#FCFCFC"
        visible: false
        radius: 0
    }

    Column {
        id: mColumn
        anchors.fill: parent
        anchors.margins: mControl.padding
        spacing: mControl.spacing

        Repeater {
            id: mColumnRepeater
            model: ListModel {}
            delegate: Column {
                id: mItem
                spacing: 5
                padding: 0
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter

                property var modelData: model
                property bool elementEnabled: !!modelData.enabled ? modelData.enabled : false
                property bool elementCollapsed: modelData.defaultCollapsed

                property int elementExpandHeight: 0
                property int elementCollapsedHeight: mControl.titleHeight

                onElementCollapsedChanged: {
                    if (mControl.accordionMode && !mItem.elementCollapsed) {
                        mControl.currentElement = modelData
                        mControl.currentItem = mItem
                        collapseOtherItem()
                    }
                }
                Component.onCompleted: {
                    mControl.childItems.push(mItem)
                    if (mControl.accordionMode && !elementCollapsed) {
                        mControl.currentItem = mItem
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
                    for (var i in mControl.childItems) {
                        if (mControl.childItems[i] !== mControl.currentItem) {
                            mControl.childItems[i].collapse()
                        }
                    }
                }

                Loader {
                    width: parent.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    sourceComponent: (0 === index && mControl.separatorLineVisible ) ? mSeparatorLineComponent : null
                }
                Rectangle {
                    id: mCollapseElementBackground
                    width: parent.width
                    height: mItem.elementCollapsed ? mItem.elementCollapsedHeight :
                                                            mItem.elementExpandHeight
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: mControl.backgroundVisible ? mControl.backgroundColor : Qt.rgba(0, 0, 0, 0)
                    opacity: mControl.backgroundOpacity
                    border.color: mControl.backgroundVisible ? mControl.backgroundBorderColor : Qt.rgba(0, 0, 0, 0)
                    border.width: mControl.backgroundBorderWidth
                    radius: mControl.backgroundRadius
                    clip: true

                    Behavior on height {
                        NumberAnimation {
                            duration: 200
                        }
                    }

                    Rectangle {
                        id: mElementTitle
                        width: parent.width
                        height: mControl.titleHeight
                        anchors.top: parent.top
                        anchors.horizontalCenter: parent.horizontalCenter
                        enabled: mItem.elementEnabled
                        color: mTitleBackgroundInfo.visible ? mTitleBackgroundInfo.color : Qt.rgba(0, 0, 0, 0)
                        opacity: mTitleBackgroundInfo.opacity
                        border.color: mTitleBackgroundInfo.visible ? mTitleBorderInfo.color : Qt.rgba(0, 0, 0, 0)
                        border.width: mTitleBorderInfo.width
                        radius: mTitleBackgroundInfo.radius
                        clip: true

                        Row {
                            id: mElementRow
                            anchors.fill: parent
                            padding: mControl.titlePadding
                            layoutDirection: mControl.titleIndicatorIconInLeft ? Qt.RightToLeft : Qt.LeftToRight

                            QExtQuickIcon {
                                id: mTitleIcon
                                width: mControl.titleIconWidth
                                height: mControl.titleIconHeight
                                anchors.verticalCenter: parent.verticalCenter
                                source: modelData.titleIconSource
                                color: modelData.titleIconColor
                            }
                            Text {
                                id: mTitleText
                                width: parent.width - mControl.titleIconWidth - mControl.titleIndicatorIconWidth -
                                       mControl.titlePadding * 2
                                height: parent.height
                                horizontalAlignment: mControl.titleTextHorizontalAlignment
                                verticalAlignment: Qt.AlignVCenter
                                anchors.verticalCenter: parent.verticalCenter
                                text: modelData.titleText
                                font: mControl.titleTextFont
                                color: modelData.titleTextColor
                                opacity: modelData.titleTextOpacity
                            }
                            QExtQuickIcon {
                                id: mTitleIndicatorIcon
                                width: mControl.titleIndicatorIconWidth
                                height: mControl.titleIndicatorIconHeight
                                anchors.verticalCenter: parent.verticalCenter
                                color: mControl.titleIndicatorIconColor
                                source: mControl.titleIndicatorIconSource
                                rotation: elementCollapsed ? 0 : mControl.titleIndicatorIconExpandRotation
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
                                if (mItem.elementEnabled) {
                                    if (mItem.elementCollapsed) {
                                        mItem.expand()
                                    } else {
                                        mItem.collapse()
                                    }
                                }
                            }
                        }

                    }

                    Loader {
                        id: mElementContentLoader
                        width: parent.width
                        anchors.top: mElementTitle.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        sourceComponent: modelData.contentItem
                        Component.onCompleted: {
                            mItem.elementExpandHeight = mElementTitle.implicitHeight + implicitHeight
                        }
                    }
                }

                Loader {
                    width: parent.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    sourceComponent: mControl.separatorLineVisible ? mSeparatorLineComponent : null
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
