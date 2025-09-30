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

    property int spacing: 5
    property int padding: 10
    readonly property int textWidth: width - padding * 2 - spacing - icon.width
    readonly property int textHeight: height - padding * 2
    readonly property alias implicitTextWidth: mContentLoader.implicitTextWidth
    readonly property alias implicitTextHeight: mContentLoader.implicitTextHeight
    readonly property int implicitWidth: mContentLoader.implicitTextWidth + padding * 2 + spacing + icon.width + 1
    readonly property int implicitHeight: mContentLoader.implicitTextHeight + padding * 2

    property alias theme: mTheme

    property alias icon: mIconInfo
    property alias checkedIcon: mCheckedIconInfo
    property int iconPosition: QExtQml.PositionLeft

    property alias content: mTextInfo
    property alias text: mTextInfo.text
    property alias font: mTextInfo.font
    property alias color: mTextInfo.color

    property alias border: mBackground.border
    property alias background: mBackgroundInfo

    property Component mIconComponent

    mIconComponent: {
        if(!mIconInfo.source) {
            return null;
        } else if(mIconInfo.source.indexOf(".svg") != -1) {
            return mSvgIconComponent;
        }
        return mFontIconComponent;
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

    QExtQmlBackgroundInfo {
        id: mBackgroundInfo
        color: "#ECF5FF"
        visible: false
        radius: 4
    }

    QExtQmlTextInfo {
        id: mTextInfo
        text: "CheckBox"
        color: mControl.enabled ? "#3D3D3D" : "#9D9D9D"
    }

    QExtQmlIconInfo {
        id: mIconInfo
        width: 18
        height: 18
        source: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_square_o)
        color: mControl.enabled ? "#46A0FC" : "#9D9D9D"
    }

    QExtQmlIconInfo {
        id: mCheckedIconInfo
        width: 18
        height: 18
        source: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_check_square)
        color: mControl.enabled ? "#46A0FC" : "#9D9D9D"
    }

    Loader {
        id: mContentLoader
        sourceComponent: mContentRowLayoutComponent
        anchors.margins: mControl.padding
        anchors.centerIn: parent

        property int implicitTextWidth: 0
        property int implicitTextHeight: 0
    }

    Component {
        id: mContentRowLayoutComponent
        Row {
            id:row
            spacing: mControl.spacing
            layoutDirection: mControl.iconPosition === QExtQml.PositionLeft ? Qt.LeftToRight : Qt.RightToLeft;

            Loader {
                id: mIconLoader
                enabled: false
                sourceComponent: mIconComponent
                anchors.verticalCenter: row.verticalCenter
            }

            QExtQuickText {
                id: mText
                enabled: false
                elide: Text.ElideRight
                width: mControl.textWidth
                height: mControl.textHeight
                text: mControl.content.text
                font: mControl.content.font
                color: mControl.content.color
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: row.verticalCenter

                theme.parent: mTheme
                theme.childName: "text"

                onImplicitWidthChanged: {
                    mContentLoader.implicitTextWidth = mText.implicitWidth;
                }
                onImplicitHeightChanged: {
                    mContentLoader.implicitTextHeight = mText.implicitHeight;
                }
            }
        }
    }

    Component{
        id: mFontIconComponent
        QExtQuickFontIcon {
            enabled: false
            theme.enabled: false
            color: !checked ? mIconInfo.color : mCheckedIconInfo.color
            width: !checked ? mIconInfo.width : mCheckedIconInfo.width
            height: !checked ? mIconInfo.height : mCheckedIconInfo.height
            source: !checked ? mIconInfo.source : mCheckedIconInfo.source
        }
    }

    Component{
        id: mSvgIconComponent
        QExtQuickSvgIcon {
            enabled: false
            theme.enabled: false
            color: !checked ? mIconInfo.color  : mCheckedIconInfo.color
            width: !checked ? mIconInfo.width  : mCheckedIconInfo.width
            height: !checked ? mIconInfo.height : mCheckedIconInfo.height
            source: !checked ? mIconInfo.source : mCheckedIconInfo.source
        }
    }


    QExtQmlThemeBinder {
        id: mTheme
        className: "QExtQuickCheckBox"
        state: mControl.state

        QExtQmlThemeBinder {
            childName: "icon"
            property alias color: mIconInfo.color
            property alias width: mIconInfo.width
            property alias height: mIconInfo.height
        }

        QExtQmlThemeBinder {
            childName: "icon.checked"
            property alias color: mCheckedIconInfo.color
            property alias width: mCheckedIconInfo.width
            property alias height: mCheckedIconInfo.height
        }

        Component.onCompleted: initialize();
    }
}
