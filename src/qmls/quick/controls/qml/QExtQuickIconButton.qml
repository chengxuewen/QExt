import QtQuick 2.6

import QExtQml 1.4
import QExtQml.Theme 1.4
import QExtQuick.Controls 1.4

QExtQuickButtonArea {
    id: mControl
    scale: 1
    width: 120
    height: 40
    states: defaultState

    property int spacing: 5
    property int padding: 10
    property int contentHAlign: Qt.AlignHCenter //Qt.AlignHCenter 、 Qt.AlignLeft or Qt.AlignRight

    readonly property int textWidth: width - padding * 2 - mIconInfo.layoutWidth
    readonly property int textHeight: height - padding * 2 - mIconInfo.layoutHeight
    readonly property alias implicitTextWidth: mContentLoader.implicitTextWidth
    readonly property alias implicitTextHeight: mContentLoader.implicitTextHeight

    readonly property int implicitWidth: implicitTextWidth + padding * 2 + mIconInfo.layoutWidth
    readonly property int implicitHeight: implicitTextHeight + padding * 2 + mIconInfo.layoutHeight

    property alias theme: mTheme

    property alias icon: mIconInfo
    property int iconPosition: QExtQml.PositionLeft

    property alias content: mTextInfo
    property alias text: mTextInfo.text
    property alias font: mTextInfo.font
    property alias color: mTextInfo.color

    property alias border: mBorderInfo
    property alias background: mBackgroundInfo
    property alias radius: mBackgroundInfo.radius

    property Component mIconComponent
    property Component contentComponent
    property Component backgroundComponent

    property list<State> defaultState: [
        State {
            name: QExtQml.stateToString(QExtQml.StatePressed)
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
        theme.childName: "Background"
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
        if (mControl.iconPosition === QExtQml.PositionLeft || mControl.iconPosition === QExtQml.PositionRight) {
            return mContentRowLayoutComponent;
        } else if (mControl.iconPosition === QExtQml.PositionTop) {
            return mContentColumnTopLayoutComponent;
        } else if (mControl.iconPosition === QExtQml.PositionBottom) {
            return mContentColumnBottomLayoutComponent;
        }
        return contentOnlyIconItem;
    }

    mIconComponent: {
        if(!mIconInfo.source) {
            return null;
        } else if(mIconInfo.source.indexOf(".svg") != -1) {
            return mSvgIconComponent;
        }
        return mFontIconComponent;
    }

    QExtQmlBackgroundInfo {
        id: mBackgroundInfo
        color: "#FCFCFC"
        radius: 2
    }

    QExtQmlIconInfo {
        id: mIconInfo
        width: 18
        height: 18
        color:"#2D2D2D"

        property int layoutWidth: 0
        property int layoutHeight: 0

        function updateLayoutSize() {
            if (QExtQml.PositionLeft == mControl.iconPosition || QExtQml.PositionRight == mControl.iconPosition) {
                layoutWidth = mControl.spacing + width + 1;
                layoutHeight = 0;
            } else if (QExtQml.PositionTop == mControl.iconPosition || QExtQml.PositionBottom == mControl.iconPosition) {
                layoutWidth = 0;
                layoutHeight = mControl.spacing + height + 1;
            } else {
                layoutWidth = width;
                layoutHeight = height;
            }
        }
        Component.onCompleted: updateLayoutSize();
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
        id: contentOnlyIconItem;
        Loader {
            scale: mControl.theme.scale
            sourceComponent: mIconComponent
        }
    }

    Component{
        id: mContentRowLayoutComponent
        Row {
            spacing: mControl.spacing
            scale: mControl.scale
            layoutDirection: QExtQml.PositionLeft === mControl.iconPosition ? Qt.LeftToRight
                                                                            : Qt.RightToLeft

            Loader {
                id: mIconLoader
                enabled: false
                visible: mIconComponent
                sourceComponent: mIconComponent
                anchors.verticalCenter: parent.verticalCenter
            }

            QExtQuickText {
                id: mText
                enabled: false
                text: mTextInfo.text
                font: mTextInfo.font
                color: mTextInfo.color
                anchors.verticalCenter: parent.verticalCenter

                theme.parent: mControl.theme
                theme.childName: "Text"

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
        id: mContentColumnTopLayoutComponent
        Column {
            spacing: mControl.spacing
            scale: mControl.theme.scale

            Loader {
                enabled: false;
                sourceComponent: mIconComponent
                anchors.horizontalCenter: parent.horizontalCenter
            }

            QExtQuickText {
                id: mText
                enabled: false
                text: mTextInfo.text
                font: mTextInfo.font
                color: mTextInfo.color
                anchors.horizontalCenter: parent.horizontalCenter

                theme.parent: mControl.theme
                theme.childName: "Text"

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
        id: mContentColumnBottomLayoutComponent
        Column {
            spacing: mControl.spacing
            scale: mControl.theme.scale

            QExtQuickText {
                id: mText
                enabled: false
                text: mTextInfo.text
                font: mTextInfo.font
                color: mTextInfo.color
                anchors.horizontalCenter: parent.horizontalCenter

                theme.parent: mControl.theme
                theme.childName: "Text"

                onImplicitWidthChanged: {
                    mContentLoader.implicitTextWidth = implicitWidth;
                }
                onImplicitHeightChanged: {
                    mContentLoader.implicitTextHeight = implicitHeight;
                }
            }

            Loader {
                enabled: false;
                sourceComponent: mIconComponent
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    Component{
        id: mFontIconComponent
        QExtQuickFontIcon {
            enabled: false
            theme.childName: "Icon"
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
            theme.childName: "Icon"

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

        property alias scale: mControl.scale;

        QExtQmlThemeBinder {
            childName: "Icon"
            property alias color: mIconInfo.color
            property alias width: mIconInfo.width
            property alias height: mIconInfo.height
        }

        Component.onCompleted: initialize();
    }
}
