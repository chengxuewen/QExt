import QtQuick 2.6

import QExtQml 1.4
import QExtQml.Theme 1.4
import QExtQml.FontIcon 1.4
import QExtQuick.Controls 1.4

QExtQuickButtonArea {
    id: mControl
    checkable: true
    width: 120
    height: 40
    // width:  contentLoader.width  + padding;
    // height: contentLoader.height + padding;

    property int spacing: 5
    property int padding: 10
    readonly property int textWidth: width - padding * 2 - spacing - icon.width
    readonly property int textHeight: height - padding * 2
    readonly property int implicitWidth: mContentLoader.implicitTextWidth + padding * 2 + spacing + icon.width + 1
    readonly property int implicitHeight: mContentLoader.implicitTextHeight + padding * 2

    property int groupIndex: -1;

    property alias theme: mTheme
    property alias icon: mIconInfo
    property alias content: mTextInfo
    property alias text: mTextInfo.text
    property alias border: mBackground.border
    property alias background: mBackgroundInfo
    property alias checkedIcon: mIconCheckedInfo

    property Component mIconComponent;

    mIconComponent:  {
        if(!mIconInfo.source) {
            return null;
        } else if(mIconInfo.source.indexOf(".svg") != -1) {
            return mSvgIconComponent;
        }
        return mFontIconComponent;
    }

    state: {
        if(!enabled){
            return "disabled";
        }
        else if(checked){
            return "checked"
        }
        return "none";
    }

    QExtQmlRectangleInfo {
        id: mBackgroundInfo
        color: "#ECF5FF"
        visible: false
        radius: 4
    }

    QExtQmlTextInfo {
        id: mTextInfo
        text: "RadioBox"
        color: mControl.enabled ? "#3D3D3D" : "#9D9D9D"
    }

    QExtQmlIconInfo {
        id: mIconInfo
        width: 18
        height: 18
        // type:   TIconType.Awesome;
        source: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_circle_o)
        color: mControl.enabled ? "#46A0FC" : "#9D9D9D"
    }

    QExtQmlIconInfo {
        id: mIconCheckedInfo
        width: 18
        height: 18
        // type:   TIcosnType.Awesome;
        source: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_dot_circle_o)
        color: mControl.enabled ? "#46A0FC" : "#9D9D9D"
    }

    QExtQuickRectangle {
        id: mBackground
        anchors.fill: parent
        color: mBackgroundInfo.color
        radius: mBackgroundInfo.radius
        visible: mBackgroundInfo.visible
        border.color: Qt.darker(mBackground.color, 1.1)

        theme.parent: mTheme
        theme.childName: "background"
    }

    Loader{
        id: mContentLoader
        anchors.centerIn: parent
        anchors.margins: mControl.padding
        sourceComponent: mContentRowLayoutComponent

        property int implicitTextWidth: 0
        property int implicitTextHeight: 0
    }

    Component{
        id: mContentRowLayoutComponent
        Row {
            spacing: mControl.spacing
            // layoutDirection: mControl.iconPosition === TPosition.Left ? Qt.LeftToRight : Qt.RightToLeft;

            Loader {
                id:icon
                enabled: false;
                sourceComponent: mIconComponent
                anchors.verticalCenter: parent.verticalCenter
            }

            QExtQuickText {
                id: mText
                enabled: false
                elide: Text.ElideRight
                width: mControl.textWidth
                height: mControl.textHeight
                text: mControl.content.text;
                font: mControl.content.font;
                color: mControl.content.color;
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter

                theme.parent: mTheme
                theme.childName: "text"

                onImplicitWidthChanged: {
                    mContentLoader.implicitTextWidth = implicitWidth;
                }
                onImplicitHeightChanged: {
                    mContentLoader.implicitTextHeight = implicitHeight;
                }
            }
        }
    }

    Component{
        id: mFontIconComponent
        QExtQuickFontIcon {
            enabled: false
            theme.enabled: false
            color: !checked ? mIconInfo.color  : mIconCheckedInfo.color
            width: !checked ? mIconInfo.width  : mIconCheckedInfo.width
            height: !checked ? mIconInfo.height : mIconCheckedInfo.height
            source: !checked ? mIconInfo.source : mIconCheckedInfo.source
        }
    }

    Component {
        id: mSvgIconComponent
        QExtQuickSvgIcon {
            enabled: false
            theme.enabled: false
            color: !checked ? mIconInfo.color  : mIconCheckedInfo.color
            width: !checked ? mIconInfo.width  : mIconCheckedInfo.width
            height: !checked ? mIconInfo.height : mIconCheckedInfo.height
            source: !checked ? mIconInfo.source : mIconCheckedInfo.source
        }
    }

    QExtQmlThemeBinder {
        id: mTheme
        className: "QExtQuickRadioBox"
        state: mControl.state

        QExtQmlThemeBinder {
            childName: "icon"
            property alias color:  mIconInfo.color
            property alias width:  mIconInfo.width
            property alias height: mIconInfo.height
        }

        QExtQmlThemeBinder {
            childName: "icon.checked"
            property alias color:  mIconCheckedInfo.color
            property alias width:  mIconCheckedInfo.width
            property alias height: mIconCheckedInfo.height
        }

        Component.onCompleted: initialize();
    }
}
