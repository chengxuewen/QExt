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
    readonly property int implicitWidth: mContentLoader.implicitTextWidth + padding * 2 + spacing + icon.width + 1
    readonly property int implicitHeight: mContentLoader.implicitTextHeight + padding * 2

    property alias theme: mTheme
    property alias icon: mIconInfo
    property alias content: mTextInfo
    property alias text: mTextInfo.text
    property alias iconChecked: mIconCheckedInfo

    property alias background: mRectangleInfo
    property alias border: mBackground.border

    property Component iconComponent

    iconComponent: {
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
        color: mRectangleInfo.color
        radius: mRectangleInfo.radius
        visible: mRectangleInfo.visible
        border.color: Qt.darker(mBackground.color, 1.1)

        theme.parent: mTheme
        theme.childName: "background"
    }

    QExtQmlRectangleInfo {
        id: mRectangleInfo
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
        id: mIconCheckedInfo
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

            Loader {
                id: mIconLoader
                enabled: false
                sourceComponent: iconComponent
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
            color: !checked ? mIconInfo.color : mIconCheckedInfo.color
            width: !checked ? mIconInfo.width : mIconCheckedInfo.width
            height: !checked ? mIconInfo.height : mIconCheckedInfo.height
            source: !checked ? mIconInfo.source : mIconCheckedInfo.source
        }
    }

    Component{
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
            property alias color: mIconCheckedInfo.color
            property alias width: mIconCheckedInfo.width
            property alias height: mIconCheckedInfo.height
        }

        Component.onCompleted: initialize();
    }
}
