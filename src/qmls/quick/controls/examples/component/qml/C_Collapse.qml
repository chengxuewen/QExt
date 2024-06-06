import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQml.FontIcon 1.2
import QExtQuick.Controls 1.2

Rectangle {
    id: root
    clip: true

    QExtQuickCollapse {
        id: mCollapse
        anchors.fill: parent
        titleHeight: 40

        property int rowSpacing: 5
        property int rowHeight: 30
        property color rowColor: "#ffffff"

        QExtQuickCollapseElement {
            titleText: qsTr("Sample information")
            titleIconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_info)
            contentItem: Rectangle {
                width: mCollapse.width
                height: 400
                color: "Yellow"
            }
        }

        QExtQuickCollapseElement {
            titleText: qsTr("Sample information")
            titleIconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_info)
            contentItem: Item {
                id: mSampleInformationGroup
                height: mSampleInformationGroupColumn.implicitHeight + 20
                Column {
                    id: mSampleInformationGroupColumn
                    anchors.fill: parent
                    anchors.margins: 10
                    width: parent.width
                    spacing: 5

                    Rectangle {
                        width: parent.width
                        height: mCollapse.rowHeight
                        color: mCollapse.rowColor
                        Label {
                            anchors.fill: parent
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            text: qsTr("Sample name:")
                        }
                        QExtQuickInputField {
                            height: parent.height
                            width: 200
                            anchors.right: parent.right
                            anchors.rightMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                            placeholderText: qsTr("Name")
                        }
                    }
                    Rectangle {
                        width: parent.width
                        height: mCollapse.rowHeight
                        color: mCollapse.rowColor
                        Label {
                            anchors.fill: parent
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            text: qsTr("People directly:")
                        }
                        QExtQuickInputField {
                            height: parent.height
                            width: 200
                            anchors.right: parent.right
                            anchors.rightMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                            placeholderText: qsTr("People")
                        }
                    }
                    Rectangle {
                        width: parent.width
                        height: mCollapse.rowHeight
                        color: mCollapse.rowColor
                        Label {
                            anchors.fill: parent
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            text: qsTr("Sample size:")
                        }
                        QExtQuickInputField {
                            height: parent.height
                            width: 200
                            anchors.right: parent.right
                            anchors.rightMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                            placeholderText: qsTr("Diameter thickness")
                        }
                    }
                    Rectangle {
                        width: parent.width
                        height: mCollapse.rowHeight
                        color: mCollapse.rowColor
                        Label {
                            anchors.fill: parent
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            text: qsTr("Sample classification:")
                        }
                        QExtQuickInputField {
                            height: parent.height
                            width: 200
                            anchors.right: parent.right
                            anchors.rightMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                            placeholderText: qsTr("Organic, ceramic, coating, metal")
                        }
                    }
                }
            }

        }

        QExtQuickCollapseElement {
            titleText: qsTr("File name directory")
            titleIconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_file)
            contentItem: Item {
                id: mFileNameDirectoryGroup
                height: mFileNameDirectoryGroupColumn.implicitHeight + 20
                Column {
                    id: mFileNameDirectoryGroupColumn
                    anchors.fill: parent
                    anchors.margins: 10
                    width: parent.width
                    spacing: 5


                    Rectangle {
                        width: parent.width
                        height: mCollapse.rowHeight
                        color: mCollapse.rowColor
                        Label {
                            anchors.fill: parent
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            text: qsTr("Measurement file name:")
                        }
                        QExtQuickInputField {
                            height: parent.height
                            width: 200
                            anchors.right: parent.right
                            anchors.rightMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                            placeholderText: qsTr("DB file")
                        }
                    }
                    Rectangle {
                        width: parent.width
                        height: mCollapse.rowHeight
                        color: mCollapse.rowColor
                        Label {
                            anchors.fill: parent
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            text: qsTr("Save directory of measurement file:")
                        }
                        QExtQuickInputField {
                            height: parent.height
                            width: 200
                            anchors.right: parent.right
                            anchors.rightMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                            placeholderText: qsTr("Directory path")
                        }
                    }
                }
            }
        }


        QExtQuickCollapseElement {
            titleText: qsTr("Laboratory information")
            titleIconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_home)
            contentItem: Item {
                id: mWaterGasSupplyGroup
                height: mWaterGasSupplyGroupColumn.implicitHeight + 20
                Column {
                    id: mWaterGasSupplyGroupColumn
                    anchors.fill: parent
                    anchors.margins: 10
                    width: parent.width
                    spacing: 5
                    Rectangle {
                        width: parent.width
                        height: mCollapse.rowHeight
                        color: mCollapse.rowColor
                        Label {
                            anchors.fill: parent
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            text: qsTr("Operation people name:")
                        }
                        QExtQuickInputField {
                            height: parent.height
                            width: 200
                            anchors.right: parent.right
                            anchors.rightMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                            placeholderText: qsTr("Name")
                        }
                    }
                    Rectangle {
                        width: parent.width
                        height: mCollapse.rowHeight
                        color: mCollapse.rowColor
                        Label {
                            anchors.fill: parent
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            text: qsTr("Laboratory site:")
                        }
                        QExtQuickInputField {
                            height: parent.height
                            width: 200
                            anchors.right: parent.right
                            anchors.rightMargin: 10
                            anchors.verticalCenter: parent.verticalCenter
                            placeholderText: qsTr("Place")
                        }
                    }
                }
            }
        }

    }
}
