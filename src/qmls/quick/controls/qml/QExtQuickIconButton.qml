import QtQuick 2.6

import QExtQml 1.4
import QExtQml.Theme 1.4
import QExtQuick.Controls 1.4

QExtQuickButtonArea {
    id: mControl
    width: 120
    height: 40
    states: defaultState

    property int spacing: 5
    property int padding: 10
    property int contentHAlign: Qt.AlignHCenter //Qt.AlignHCenter 、 Qt.AlignLeft or Qt.AlignRight
    readonly property int textWidth: width - padding * 2 - spacing - icon.width
    readonly property int textHeight: height - padding * 2
    readonly property int implicitWidth: mContentLoader.implicitTextWidth + padding * 2 + spacing + icon.width + 1
    readonly property int implicitHeight: mContentLoader.implicitTextHeight + padding * 2

    property alias theme: mTheme
    property alias icon: mIconInfo
    property alias border: mBorderInfo
    property alias content: mTextInfo
    property alias text: mTextInfo.text
    property alias background: mRectangleInfo

    property Component iconComponent
    property Component contentComponent
    property Component backgroundComponent

    property list<State> defaultState: [
        State {
            name: QExtQuickControls.buttonStateToString(QExtQuickControls.ButtonStatePressed)
            PropertyChanges {
                target: mTheme
                scale: 0.92
            }
        }
    ]

    Loader{
        id: mBackgroundLoader
        anchors.fill: mControl
        sourceComponent: backgroundComponent
        visible: mControl.background.visible
    }

    Loader {
        id: mContentLoader
        sourceComponent: contentComponent
        anchors.margins: mControl.padding
        anchors.verticalCenter: mControl.verticalCenter
        x: {
            if(contentHAlign == Qt.AlignLeft) {
                return padding;
            } else if(contentHAlign == Qt.AlignRight) {
                return mControl.width - width - padding;
            }
            return (mControl.width - width) / 2;
        }

        property int implicitTextWidth: 0
        property int implicitTextHeight: 0
    }

    backgroundComponent: QExtQuickRectangle {
        enabled: false;
        theme.parent: mControl.theme
        theme.childName: "background"
        theme.filterPropertyName: ["width", "height"];
        color: mControl.background.color;
        radius: mControl.background.radius;
        visible: mControl.background.visible;
        opacity: mControl.background.opacity;
        border.color: mControl.border.color;
        border.width: mControl.border.width;
        scale: mTheme.scale;
    }

    contentComponent: {
        if(mIconInfo.position === QExtQuickControls.PositionCenter) {
            return contentOnlyiconItem;
        } else if(mIconInfo.position === QExtQuickControls.PositionLeft ||
                  mIconLoader.position === QExtQuickControls.PositionRight) {
            return mContentRowLayoutComponent;
        } else if(mIconInfo.position === QExtQuickControls.PositionTop) {
            return mContentColumnLayoutComponent;
        }
        return null;
    }

    iconComponent: {
        if(!mIconInfo.source) {
            return null;
        } else if(mIconInfo.source.indexOf(".svg") != -1) {
            return mSvgIconComponent;
        }
        return mFontIconComponent;
    }

    QExtQmlRectangleInfo {
        id: mRectangleInfo
        color: "#FCFCFC"
        radius: 2
    }

    QExtQmlIconInfo {
        id: mIconInfo
        width: 18
        height: 18
        color:"#2D2D2D"
        position: QExtQuickControls.PositionLeft
    }

    QExtQmlBorderInfo {
        id: mBorderInfo
        width: 1
        color: "#DCDCDC"
    }

    QExtQmlTextInfo {
        id: mTextInfo
        color: "#2D2D2D"
        text: "Button"
    }

    Component {
        id: contentOnlyiconItem;
        Loader {
            scale:  mControl.theme.scale;
            sourceComponent: iconComponent;
        }
    }

    Component{
        id: mContentRowLayoutComponent
        Row {
            id: row
            spacing: mControl.spacing
            scale: mControl.theme.scale
            layoutDirection: mControl.icon.position === QExtQuickControls.PositionLeft ? Qt.LeftToRight
                                                                                       : Qt.RightToLeft

            Loader {
                id: mIconLoader
                enabled: false
                visible: iconComponent
                sourceComponent: iconComponent
                anchors.verticalCenter: row.verticalCenter
            }

            QExtQuickText {
                id: mText
                enabled: false
                text: mControl.content.text
                font: mControl.content.font
                color: mControl.content.color
                anchors.verticalCenter: row.verticalCenter

                theme.parent: mControl.theme
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

    Component {
        id: mContentColumnLayoutComponent
        Column {
            spacing: mControl.spacing
            scale: mControl.theme.scale

            Loader {
                enabled: false;
                sourceComponent: iconComponent
                anchors.horizontalCenter: parent.horizontalCenter
            }

            QExtQuickText {
                id: mText
                enabled: false
                theme.parent: mControl.theme
                theme.childName: "text"

                text: mControl.content.text
                font: mControl.content.font
                color: mControl.content.color

                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    Component{
        id: mFontIconComponent
        QExtQuickFontIcon {
            enabled: false
            theme.childName: "icon"
            theme.parent: mControl.theme

            color: mIconInfo.color
            width: mIconInfo.width
            height: mIconInfo.height
            source: mIconInfo.source
        }
    }

    Component{
        id: mSvgIconComponent
        QExtQuickSvgIcon {
            enabled: false;
            theme.parent: mControl.theme
            theme.childName: "icon"

            color: mIconInfo.color
            width: mIconInfo.width
            height: mIconInfo.height
            source: mIconInfo.source
        }
    }

    QExtQmlThemeBinder {
        id: mTheme
        className: "QExtQuickIconButton"
        state: mControl.state

        property double scale: 1;

        QExtQmlThemeBinder {
            childName: "icon"
            property alias color: mIconInfo.color
            property alias width: mIconInfo.width
            property alias height: mIconInfo.height
        }

        Component.onCompleted: initialize();
    }
}
