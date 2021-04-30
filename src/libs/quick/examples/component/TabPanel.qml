import QtQuick 2.7
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: mTabPanel

    signal tabActived(string uri, string label)

    property string defaultTab
    property alias activedTab: mPrivate.activedTab
    property alias tabModel: mListView.model

    Rectangle {
        id: mListViewWraper
        width: 200
        height: parent.height
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        color: "#f0f0f0"
        ListView {
            id: mListView
            clip: true
            spacing: 1
            anchors.fill: parent
            delegate: Button {
                id: mToolButton
                width: parent.width
                height: 40
                contentItem: Text {
                    leftPadding: 30
                    text: modelData.label
                    font.pixelSize: 14
                    color: mToolButton === mPrivate.activedTab ? "#1A76D3" : "#000000"
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }
                background: Rectangle {
                    anchors.fill: parent
                    color: mToolButton === mPrivate.activedTab ? "#E6F1FC" : "#FFFFFF"
                }
                text: modelData.label
                onClicked: {
                    if (mToolButton !== mPrivate.activedTab) {
                        mPanelLoader.source = modelData.uri
                        mPrivate.activedTab = mToolButton
                        tabActived(modelData.uri, modelData.label)
                    }
                }
                Component.onCompleted: {
                    if (defaultTab === modelData.label) {
                        mPanelLoader.source = modelData.uri
                        mPrivate.activedTab = mToolButton
                        tabActived(modelData.uri, modelData.label)
                    }
                }
            }
            ScrollBar.vertical: ScrollBar {
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
            }
            QtObject {
                id: mPrivate
                property Item activedTab
            }
        }
    }
    Loader {
        id: mPanelLoader
        width: parent.width - mListViewWraper.width - 2
        height: parent.height
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
    }

    Component.onCompleted: {

    }
}
