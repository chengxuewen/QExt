import QtQuick 2.12
import QtQuick.Controls 2.12
import QEXTQuick 1.2

Rectangle {
    id: lfamMeasureSampleView
    clip: true

    QEXTCollapse {
        id: mCollapse
        anchors.fill: parent
        titleHeight: 40

        property int rowSpacing: 5
        property int rowHeight: 30
        property color rowColor: "#ffffff"

        QEXTCollapseElement {
            titleText: qsTr("Sample information")
            titleIconSource: QEXTQuickFontAwesome.FA_info
            contentItem: Rectangle {
                width: mCollapse.width
                height: 400
                color: "Yellow"
            }
        }

        QEXTCollapseElement {
            titleText: qsTr("Sample information")
            titleIconSource: QEXTQuickFontAwesome.FA_info
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
                        QEXTInputField {
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
                        QEXTInputField {
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
                        QEXTInputField {
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
                        QEXTInputField {
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

        QEXTCollapseElement {
            titleText: qsTr("File name directory")
            titleIconSource: QEXTQuickFontAwesome.FA_file
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
                        QEXTInputField {
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
                        QEXTInputField {
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


        QEXTCollapseElement {
            titleText: qsTr("Laboratory information")
            titleIconSource: QEXTQuickFontAwesome.FA_home
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
                        QEXTInputField {
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
                        QEXTInputField {
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
