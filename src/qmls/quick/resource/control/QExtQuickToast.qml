pragma Singleton
import QtQuick 2.12
import QtQml 2.12
import QtQuick.Controls 2.12

import QExtQuick 1.2

/*!
    QEXTQmlQuickToast.showSuccess(text, duration, moremsg)
    QEXTQmlQuickToast.showInfo(text, duration, moremsg)
    QEXTQmlQuickToast.showWarning(text, duration, moremsg)
    QEXTQmlQuickToast.showError(text, duration, moremsg)
    QEXTQmlQuickToast.showCustom(itemcomponent, duration)
*/

QEXTQmlQuickObject {
    id: qextToast

    property int horizontalAlignment: Qt.AlignHCenter
    property int verticalAlignment: Qt.AlignTop
    property real leftPadding: 10
    property real topPadding: 10
    property real rightPadding: 10
    property real bottomPadding: 10

    function showSuccess(text, duration, moremsg) {
        mControl.create(mControl.const_success, text, duration, moremsg ? moremsg : "")
    }

    function showInfo(text, duration, moremsg) {
        mControl.create(mControl.const_info, text, duration, moremsg ? moremsg : "")
    }

    function showWarning(text, duration, moremsg) {
        mControl.create(mControl.const_warning, text,duration, moremsg ? moremsg : "")
    }

    function showError(text, duration, moremsg) {
        mControl.create(mControl.const_error, text, duration, moremsg ? moremsg : "")
    }

    function showCustom(itemcomponent, duration) {
        mControl.createCustom(itemcomponent, duration)
    }

    QEXTQmlQuickObject {
        id: mControl
        property var rootWindow: qextRootWindow
        property var screenLayout: null
        property string const_success: qsTr("success")
        property string const_info: qsTr("info")
        property string const_warning: qsTr("warning")
        property string const_error: qsTr("error")
        property int maxWidth: 300

        function create(type, text, duration, moreMsg) {
            if(screenLayout) {
                var last = screenLayout.getLastloader()
                if (last.type === type && last.text === text && moreMsg === last.moreMsg) {
                    last.restart()
                    return
                }
            }

            initScreenLayout()
            mContentComponent.createObject(screenLayout, {
                                               type:type,
                                               text:text,
                                               duration:duration,
                                               moreMsg:moreMsg,
                                           })
        }

        function createCustom(itemcomponent, duration) {
            initScreenLayout()
            if (itemcomponent) {
                mContentComponent.createObject(screenLayout, {itemcomponent:itemcomponent, duration:duration})
            }
        }

        function initScreenLayout() {
            if (screenLayout == null) {
                screenLayout = screenlayoutComponent.createObject(rootWindow)
                screenLayout.z = Number.MAX_VALUE
            }
        }

        Component {
            id: screenlayoutComponent
            Column {
                spacing: 20
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
                    updatePos()
                }

                onParentHeightChanged: {
                    updatePos()
                }

                onHeightChanged: {
                    updatePos()
                }

                onChildrenChanged: {
                    if (children.length === 0)  {
                        destroy()
                    }
                }
                function getLastloader() {
                    if (children.length > 0) {
                        return children[children.length - 1]
                    }
                    return null
                }
                function updatePos() {
                    switch (qextToast.verticalAlignment) {
                    case Qt.AlignVCenter:
                        y = (parentHeight - height) / 2
                        break
                    case Qt.AlignBottom:
                        y = parentHeight - height - qextToast.bottomPadding
                        break
                    case Qt.AlignTop:
                    default:
                        y = qextToast.topPadding
                        break
                    }
                }
            }
        }

        Component {
            id: mContentComponent
            Item {
                id: mContent
                property int duration: 3000
                property var itemComponent
                property string type
                property string text
                property string moreMsg

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

                    property var _super: mContent
                    property real parentWidth: parent.width

                    onWidthChanged: {
                        updatePos()
                    }
                    onParentWidthChanged: {
                        updatePos()
                    }

                    Component.onCompleted: {
                        updatePos()
                    }

                    scale: item ? 1 : 0
                    asynchronous: true

                    Behavior on scale {
                        NumberAnimation {
                            easing.type: Easing.OutBack
                            duration: 100
                        }
                    }

                    function updatePos() {
                        switch (qextToast.horizontalAlignment) {
                        case Qt.AlignHCenter:
                            x = (parentWidth - width) / 2
                            break
                        case Qt.AlignRight:
                            x = parentWidth - width - qextToast.rightPadding
                            break
                        case Qt.AlignLeft:
                        default:
                            x = qextToast.leftPadding
                            break
                        }
                    }

                    sourceComponent: itemComponent ? itemComponent : mControl.messageSytleItem
                }

            }
        }

        // -- QEXTQmlQuick Message style
        property Component messageSytleItem: Rectangle {
            id: rect
            width: mRowlayout.width  + (_super.moremsg ? 25 : 80)
            height: mRowlayout.height + 20
            color: {
                switch(_super.type) {
                    case mControl.const_success:
                    return "#F0F9EB"
                    case mControl.const_warning:
                    return "#FDF6ED"
                    case mControl.const_info:
                    return "#EDF2FC"
                    case mControl.const_error:
                    return "#FEF0F0"
                }
                return "#FFFFFF"
            }
            radius: 4
            border.width: 1
            border.color: Qt.lighter(mSVGIcon.color, 1.2)

            Row {
                id: mRowlayout
                x: 20
                y: (parent.height - height) / 2
                spacing: 10
                QEXTQmlQuickSVGIcon {
                    id: mSVGIcon
                    anchors.verticalCenter: mRowlayout.verticalCenter
                    source: {
                        switch(_super.type) {
                            case mControl.const_success:
                            return "qrc:/QEXTQmlQuick/svg/success.svg"
                            case mControl.const_warning:
                            return "qrc:/QEXTQmlQuick/svg/warning.svg"
                            case mControl.const_info:
                            return "qrc:/QEXTQmlQuick/svg/info.svg"
                            case mControl.const_error:
                            return "qrc:/QEXTQmlQuick/svg/error.svg"
                        }
                        return "#FFFFFF"
                    }

                    width: more.visible ? 40 : 22
                    height: more.visible ? 40 : 22

                    color: {
                        switch(_super.type) {
                            case mControl.const_success:
                            return "#6AC044"
                            case mControl.const_warning:
                            return "#E4A147"
                            case mControl.const_info:
                            return "#909399"
                            case mControl.const_error:
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
                        text: _super.text
                        color: mSVGIcon.color
                    }

                    Label {
                        id: more
                        color: mSVGIcon.color
                        text: _super.moreMsg
                        visible: _super.moreMsg
                        wrapMode: Text.WordWrap

                        onContentWidthChanged: {
                            width = contentWidth < mControl.maxWidth - 100 ? 220 : mControl.maxWidth
                        }
                    }
                }
            }

            QEXTQmlQuickIconButton {
                y: 4
                x: parent.width - width
                width: height
                iconWidth: 12
                iconHeight: 12
                iconDisplay: QEXTQmlQuick.IconDisplay_IconOnly
                iconSource: "qrc:/QEXTQmlQuick/svg/close-px.svg"
                iconColor: "#ADADAD"
                background: null
                onClicked: _super.close()
            }

        }
    }
}
