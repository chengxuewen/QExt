import QtQuick 2.6

import QExtQml 1.4
import QExtQml.Theme 1.4
import QExtQuick.Controls 1.4

QExtQuickPopup {
    id: mControl

    property int padding: 2;

    property int bodyWidth: 150;
    property alias bodyBackground:mBodyBackground;
    property alias bodyBorder: mBodyBorderInfo

    property alias theme: mTheme

    property Component bodyComponent: mDefaultBodyComponent
    property Component backgroundComponent: null

    onTriggeredBackground: close();

    onBodyWidthChanged: resetLayout();

    function open(posX, posY) {
        mBodyLoader.show();
        privatec.create();
        mBodyLoader.x = posX;
        mBodyLoader.y = posY;

        resetLayout();
        opened();
    }

    function openToGlobal(item , offX , offY) {
        mBodyLoader.show();
        privatec.create();
        var ox = offX ? offX + 2 : 0;
        var oy = offY ? offY + 2 : 0;
        var p = item.parent.mapToGlobal(item.x + ox , item.y + oy);

        mBodyLoader.x = p.x - QExtQml.rootWindow.x;
        mBodyLoader.y = p.y - QExtQml.rootWindow.y;

        resetLayout();
        opened();
    }

    function resetLayout() {
        if(mBodyLoader.width + mBodyLoader.x > QExtQml.rootWindow.width) {
            mBodyLoader.x = QExtQml.rootWindow.width - mBodyLoader.width - 5;
        } else if(mBodyLoader.x <= 0) {
            mBodyLoader.x = 5;
        }

        if (mBodyLoader.height + mBodyLoader.y > QExtQml.rootWindow.height) {
            mBodyLoader.y = QExtQml.rootWindow.height - mBodyLoader.height - 5;
        } else if(mBodyLoader.y <= 0) {
            mBodyLoader.y = 5;
        }
    }

    function close() {
        privatec.close();
        mBodyLoader.hide();
        closeed();
    }

    Connections {
        target: QExtQml.rootWindow
        onWidthChanged:close();
        onHeightChanged:close();
    }

    QExtQmlBackgroundInfo {
        id: mBodyBackground
        radius: 2
        color: "#FCFCFC"
    }

    QExtQmlBorderInfo {
        id: mBodyBorderInfo
        width: 1
        color: Qt.darker(mBodyBackground.color, 1.2)
    }

    Loader {
        id: mBodyLoader
        MouseArea {
            anchors.fill: parent
            z: -1
        }

        function show() {
            sourceComponent = bodyComponent;
        }

        function hide() {
            sourceComponent = null;
        }
    }

    Component{
        id: mDefaultBodyComponent
        QExtQuickRectangle {
            width: bodyWidth  + border.width * 4;
            height: mLayoutColumn.height + 20;
            color: mBodyBackground.color;
            radius: mBodyBackground.radius
            border.width: mBodyBorderInfo.width;
            border.color: mBodyBorderInfo.color;

            Column {
                id: mLayoutColumn
                width: parent.width;
                spacing: 10
                anchors.top: parent.top;
                anchors.topMargin: mControl.padding;

                Rectangle {
                    width: parent.width - 2;
                    anchors.horizontalCenter: parent.horizontalCenter;

                    height: 28
                    Text {
                        text: "TPopover测试"
                        // font.pixelSize: TPixelSizePreset.PH5
                        anchors.centerIn: parent;
                    }
                }

                Text {
                    width: parent.width - 10;
                    text: "重新实现bodyComponent ，可完成高级扩展!请参考 TPopoverMenu";
                    // font.pixelSize: TPixelSizePreset.PH6
                    wrapMode: Text.WordWrap
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            theme.className: mControl.theme.className
            theme.groupName: mControl.theme.groupName
            theme.state: mControl.theme.state
            theme.childName: "Body"
        }
    }

    QExtQmlThemeBinder {
        id: mTheme
        className: "QExtQuickPopover"

        property alias padding: mControl.padding
        property alias bodyWidth: mControl.bodyWidth

        Component.onCompleted: initialize();
    }
}
