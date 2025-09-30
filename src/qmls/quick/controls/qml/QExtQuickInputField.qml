import QtQuick 2.6

import QExtQml 1.4
import QExtQml.Theme 1.4
import QExtQml.FontIcon 1.4
import QExtQuick.Controls 1.4

Item {
    id: mControl
    width: 160
    height: 38
    state: inputing ? "inputing" : "none";
    clip: true

    signal cleared()

    property alias inputing: mInput.focus

    property int verticalMargin: 5
    property int horizontalMargin: verticalMargin + (background.radius >= height / 2 ? 10 : 5)

    property int placeholderPosition: QExtQml.PositionCenter
    property int placeholderSpacing: 10
    property alias placeholderText: mPlaceholderTextInfo.text
    property alias placeholderContent: mPlaceholderTextInfo
    property alias placeholderIcon: mIconInfo

    property alias theme: mTheme

    property bool clearable: true
    property alias clearIcon: mClearIconInfo

    property alias border: mBorderInfo
    property alias background: mBackgroundInfo

    property alias input: mInput
    property alias text: mInput.text
    property alias content: mTextInfo

    property Component cursorDelegate;

    property color cursorColor: "#000000"
    property alias acceptableInput: mInput.acceptableInput
    property alias activeFocusOnPress: mInput.activeFocusOnPress
    property alias canPaste: mInput.canPaste
    property alias canRedo: mInput.canRedo
    property alias canUndo: mInput.canUndo
    property alias echoMode: mInput.echoMode

    property alias inputMask: mInput.inputMask
    property alias inputMethodComposing: mInput.inputMethodComposing
    property alias inputMethodHints: mInput.inputMethodHints

    property alias length: mInput.length
    property alias maximumLength: mInput.maximumLength

    property alias selectByMouse: mInput.selectByMouse
    property alias selectedText: mInput.selectedText
    property alias selectionEnd: mInput.selectionEnd
    property alias selectionStart: mInput.selectionStart

    QExtQmlRectangleInfo {
        id: mBackgroundInfo
        color: "#FCFCFC"
        radius: 2
    }

    QExtQmlTextInfo {
        id: mPlaceholderTextInfo
        text: "InputField"
        color: "#9D9D9D"
    }

    QExtQmlTextInfo {
        id: mTextInfo
    }

    QExtQmlIconInfo {
        id: mIconInfo
        color: "#9D9D9D"
    }

    QExtQmlIconInfo {
        id: mClearIconInfo
        color: border.color
        width: 12;
        height:12;
        source: "qrc:/QExtQuickControls/resources/image/close_px.svg"
    }

    QExtQmlBorderInfo {
        id: mBorderInfo
        width: 1
        color: "#9D9D9D"
    }

    QExtQuickRectangle {
        anchors.fill: parent
        border.width: mBorderInfo.width
        border.color: mBorderInfo.color
        color: mBackgroundInfo.color
        radius: mBackgroundInfo.radius
        opacity:mBackgroundInfo.opacity

        theme.parent: mTheme
        theme.childName: "background"
    }

    QtObject {
        id: mPrivate
        property bool hold: mInput.focus || mInput.length > 0 || placeholderPosition === QExtQml.PositionLeft;
    }

    cursorDelegate: QExtQuickDividerLine {
        id: mCursor
        width: 1
        height: mInput.contentHeight
        visible: false
        color: mControl.cursorColor
        Timer {
            interval: 500
            running: mInput.focus
            repeat: true
            onTriggered: mCursor.visible = !mCursor.visible
            onRunningChanged: !running ? mCursor.visible = false : false
        }

        theme.parent: mTheme
        theme.childName: "cursor"
    }

    TextInput {
        id: mInput
        clip: true
        anchors.fill: parent
        color: mTextInfo.color
        verticalAlignment: TextInput.AlignVCenter
        cursorDelegate: mControl.cursorDelegate
        anchors.topMargin: mControl.verticalMargin
        anchors.bottomMargin: mControl.verticalMargin
        anchors.rightMargin: {
            if (clearable && mClearButton.visible) {
                return mClearButton.width;
            }
            return mControl.horizontalMargin;
        }

        anchors.leftMargin:  {
            if (mPrivate.hold) {
                return mPlaceholderRow.leftPadding;
            }
            return mControl.horizontalMargin;
        }

        Keys.onReleased: mInput.focus = event.key !== Qt.Key_Escape
    }

    Row {
        id: mPlaceholderRow
        spacing: 4
        opacity: 0.7
        x: mInput.focus || mInput.length > 0 ? holdX : startX;
        anchors.verticalCenter: parent.verticalCenter;
        property int holdX: mControl.horizontalMargin;
        property int leftPadding: {
            if(!iconloader.visible && background.radius >= mControl.height / 2){
                return horizontalMargin;
            }
            return iconloader.width + spacing / 2 + x;
        }

        property int startX:{
            if(placeholderPosition !== QExtQml.PositionLeft) {
                return (parent.width - width) / 2;
            }
            return holdX;
        }

        Loader{
            id:iconloader;
            visible: sourceComponent !== null;
            anchors.verticalCenter: parent.verticalCenter
            sourceComponent: {
                if(!mIconInfo.source) {
                    return null;
                } else if(mIconInfo.source.indexOf(".svg") != -1) {
                    return mSvgIconComponent;
                }
                return mFontIconComponent;
            }
        }

        Behavior on x {
            NumberAnimation {
                duration: 100
                onRunningChanged: mText.vout = running;
            }
        }

        QExtQuickText {
            id: mText
            text: mPlaceholderTextInfo.text
            color: mPlaceholderTextInfo.color
            font.pixelSize: mPlaceholderTextInfo.font.pixelSize
            font.bold: mPlaceholderTextInfo.font.bold

            theme.parent: mTheme
            theme.childName: "PlaceholderText"

            property bool vout
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: {
                vout;
                if(!vout && mInput.focus || mInput.length > 0){
                    return -50;
                }
                return 0;
            }

            Behavior on anchors.verticalCenterOffset {
                NumberAnimation {
                    duration: 200
                }
            }
        }
    }

    QExtQuickIconButton {
        id: mClearButton
        width: implicitWidth
        backgroundComponent: null
        padding: 15
        focus: false
        content.text: ""
        iconPosition: QExtQml.PositionCenter
        icon.width:  mClearIconInfo.width
        icon.height: mClearIconInfo.height
        icon.color:  mClearIconInfo.color
        icon.source: mClearIconInfo.source
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        visible: clearable && mInput.length > 0
        onClicked: mInput.text = ""

        theme.parent: mTheme;
        theme.childName: "ClearButton"
    }

    Component{
        id: mFontIconComponent
        QExtQuickFontIcon {
            enabled: false
            source: mIconInfo.source
            color: mIconInfo.color
            width: mIconInfo.width
            height: mIconInfo.height

            theme.childName: "PlaceHolderIcon"
            theme.parent: mTheme
        }
    }

    Component{
        id: mSvgIconComponent
        QExtQuickSvgIcon {
            enabled: false;
            source: mIconInfo.source
            color: mIconInfo.color
            width: mIconInfo.width
            height: mIconInfo.height

            theme.childName: "PlaceholderIcon"
            theme.parent: mTheme
        }
    }

    QExtQmlThemeBinder {
        id: mTheme
        className: "QExtQuickInputField"
        state: mControl.state

        property alias width: mControl.width
        property alias height: mControl.height
        property alias inputTextColor: mInput.color

        Component.onCompleted: initialize()
    }
}
