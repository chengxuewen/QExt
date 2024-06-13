import QtQml 2.9
import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQml 1.2
import QExtQuick.Controls 1.2

/*!
    QExtQuickToast.showSuccess(text, duration, moremsg)
    QExtQuickToast.showInfo(text, duration, moremsg)
    QExtQuickToast.showWarning(text, duration, moremsg)
    QExtQuickToast.showError(text, duration, moremsg)
    QExtQuickToast.showCustom(itemComponent, duration)
*/

QExtQmlObject {
    id: root

    property alias padding : mPadding
    property alias rootWindow: mData.rootWindow
    property alias messageBoxComponent: mData.messageBoxComponent

    readonly property alias screenLayout: mData.screenLayout

    readonly property alias const_success: mData.const_success
    readonly property alias const_warning: mData.const_warning
    readonly property alias const_error: mData.const_error
    readonly property alias const_info: mData.const_info

    property real spacing: 20
    property bool defaultCloseable: true
    property int verticalAlignment: Qt.AlignTop
    property int horizontalAlignment: Qt.AlignHCenter

    function showSuccess(text, duration, moremsg, closeable) {
        closeable = (undefined === closeable) ? root.defaultCloseable : closeable;
        mData.create(mData.const_success, text, duration, moremsg ? moremsg : "", closeable)
    }

    function showInfo(text, duration, moremsg, closeable) {
        closeable = (undefined === closeable) ? root.defaultCloseable : closeable;
        mData.create(mData.const_info, text, duration, moremsg ? moremsg : "", closeable);
    }

    function showWarning(text, duration, moremsg, closeable) {
        closeable = (undefined === closeable) ? root.defaultCloseable : closeable;
        mData.create(mData.const_warning, text,duration, moremsg ? moremsg : "", closeable);
    }

    function showError(text, duration, moremsg, closeable) {
        closeable = (undefined === closeable) ? root.defaultCloseable : closeable;
        mData.create(mData.const_error, text, duration, moremsg ? moremsg : "", closeable);
    }

    function showCustomWithProperties(itemComponent, itemProperties, duration) {
        mData.createCustom(itemComponent, itemProperties, duration)
    }

    function showCustom(itemComponent, duration) {
        mData.createCustom(itemComponent, null, duration)
    }

    QExtQuickPadding {
        id: mPadding
        padding: 10
    }

    QExtQmlObject {
        id: mData
        property int maxWidth: 300
        property var rootWindow: null
        property var screenLayout: null
        property string const_success: "success"
        property string const_warning: "warning"
        property string const_error: "error"
        property string const_info: "info"

        function create(type, text, duration, moremsg, closeable) {
            if(screenLayout) {
                var last = screenLayout.getLastloader();
                if (type === last.type && text === last.text && moremsg === last.moremsg && closeable === last.closeable) {
                    last.restart();
                    return;
                }
            }

            initScreenLayout();
            mContentComponent.createObject(screenLayout, {
                                               type: type,
                                               text: text,
                                               duration: duration,
                                               moremsg: moremsg,
                                               closeable: closeable,
                                           });
        }

        function createCustom(itemComponent, itemProperties, duration) {
            if(screenLayout) {
                var last = screenLayout.getLastloader();
                if (JSON.stringify(itemProperties) === JSON.stringify(last.itemProperties)) {
                    last.restart();
                    return;
                }
            }

            initScreenLayout();
            if (itemComponent) {
                mContentComponent.createObject(screenLayout, {
                                                   itemComponent: itemComponent,
                                                   itemProperties: itemProperties,
                                                   duration: duration
                                               });
            }
        }

        function initScreenLayout() {
            if (null == screenLayout) {
                screenLayout = screenlayoutComponent.createObject(rootWindow);
                screenLayout.z = Number.MAX_VALUE;
            }
        }

        Component {
            id: screenlayoutComponent
            Column {
                spacing: root.spacing
                width: parent.width
                move: Transition {
                    NumberAnimation {
                        properties: "y"
                        easing.type: Easing.OutBack
                        duration: 300
                    }
                }

                property real parentHeight: parent.height

                Component.onCompleted: {
                    updatePos();
                }

                onParentHeightChanged: {
                    updatePos();
                }

                onHeightChanged: {
                    updatePos();
                }

                onChildrenChanged: {
                    if (children.length === 0)  {
                        destroy();
                    }
                }
                function getLastloader() {
                    if (children.length > 0) {
                        return children[children.length - 1];
                    }
                    return null;
                }
                function updatePos() {
                    switch (root.verticalAlignment) {
                    case Qt.AlignVCenter:
                        y = (parentHeight - height) / 2;
                        break;
                    case Qt.AlignBottom:
                        y = parentHeight - height - root.padding.bottomPadding;
                        break;
                    case Qt.AlignTop:
                    default:
                        y = root.padding.topPadding;
                        break;
                    }
                }
            }
        }

        Component {
            id: mContentComponent
            Item {
                id: mContent
                property var itemProperties
                property var itemComponent
                property int duration: 3000
                property string type
                property string text
                property string moremsg
                property bool closeable

                width: parent.width
                height: mLoader.height

                function close() {
                    mContent.destroy()
                }

                function restart() {
                    mDelayTimer.restart()
                }

                Timer {
                    id: mDelayTimer
                    interval: duration
                    running: true
                    repeat: true
                    onTriggered: mContent.close()
                }

                Loader {
                    id: mLoader

                    property var superItem: mContent
                    property real parentWidth: parent.width

                    onWidthChanged: {
                        updatePos()
                    }
                    onParentWidthChanged: {
                        updatePos()
                    }

                    onLoaded: {
                        if (item && superItem.itemProperties && superItem.itemComponent) {
                            for (const key in superItem.itemProperties) {
                                if (superItem.itemProperties.hasOwnProperty(key)) {
                                    // console.log(key + ": " + superItem.itemProperties[key]);
                                    item[key] = superItem.itemProperties[key];
                                }
                            }
                        }
                    }
                    Component.onCompleted: {
                        updatePos();
                    }
                    sourceComponent: superItem.itemComponent ? superItem.itemComponent : mData.messageBoxComponent

                    scale: item ? 1 : 0
                    // asynchronous: true

                    Behavior on scale {
                        NumberAnimation {
                            easing.type: Easing.OutBack
                            duration: 100
                        }
                    }

                    function updatePos() {
                        switch (root.horizontalAlignment) {
                        case Qt.AlignHCenter:
                            x = (parentWidth - width) / 2
                            break
                        case Qt.AlignRight:
                            x = parentWidth - width - root.padding.rightPadding
                            break
                        case Qt.AlignLeft:
                        default:
                            x = root.padding.leftPadding
                            break
                        }
                    }
                }
            }
        }

        property Component messageBoxComponent: Rectangle {
            id: rect
            width: mRowlayout.width  + (superItem.moremsg ? 25 : 80)
            height: mRowlayout.height + 20
            color: {
                switch(superItem.type) {
                case mData.const_success:
                    return "#F0F9EB"
                case mData.const_warning:
                    return "#FDF6ED"
                case mData.const_info:
                    return "#EDF2FC"
                case mData.const_error:
                    return "#FEF0F0"
                }
                return "#FFFFFF"
            }
            radius: 4
            border.width: 1
            border.color: Qt.lighter(mImage.color, 1.2)

            Row {
                id: mRowlayout
                x: 20
                y: (parent.height - height) / 2
                spacing: 10
                QExtQuickImage {
                    id: mImage
                    anchors.verticalCenter: mRowlayout.verticalCenter
                    source: {
                        switch(superItem.type) {
                        case mData.const_success:
                            return "qrc:/QExtQuickControls/resource/image/success.svg"
                        case mData.const_warning:
                            return "qrc:/QExtQuickControls/resource/image/warning.svg"
                        case mData.const_info:
                            return "qrc:/QExtQuickControls/resource/image/info.svg"
                        case mData.const_error:
                            return "qrc:/QExtQuickControls/resource/image/error.svg"
                        }
                        return ""
                    }

                    width: more.visible ? 40 : 22
                    height: more.visible ? 40 : 22

                    color: {
                        switch(superItem.type) {
                        case mData.const_success:
                            return "#6AC044"
                        case mData.const_warning:
                            return "#E4A147"
                        case mData.const_info:
                            return "#909399"
                        case mData.const_error:
                            return "#F36D6F"
                        }
                        return "#FFFFFF"
                    }
                }

                Column {
                    spacing: 5
                    Label {
                        font.bold: more.visible
                        font.pixelSize: 20
                        text: superItem.text
                        color: mImage.color
                    }

                    Label {
                        id: more
                        color: mImage.color
                        text: superItem.moremsg
                        visible: superItem.moremsg
                        wrapMode: Text.WordWrap

                        onContentWidthChanged: {
                            width = contentWidth < mData.maxWidth - 100 ? 220 : mData.maxWidth
                        }
                    }
                }
            }

            QExtQuickImage {
                anchors.top: parent.top
                anchors.topMargin: 8
                anchors.right: parent.right
                anchors.rightMargin: 8
                width: 12
                height: width
                color: "#ADADAD"
                source: "qrc:/QExtQuickControls/resource/image/close_px.svg"
                visible: superItem.closeable
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        superItem.close()
                    }
                }
            }

        }
    }
}
