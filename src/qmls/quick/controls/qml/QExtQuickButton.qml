import QtQuick 2.6

import QExtQml 1.4
import QExtQml.Theme 1.4
import QExtQuick.Controls 1.4

QExtQuickButtonArea {
    id: mControl
    width: mContentLoader.width + padding
    height: mContentLoader.height + padding
    states: defaultState

    readonly property alias contentWidth: mContentLoader.width;
    readonly property alias contentHeight: mContentLoader.height;

    property int padding: 20;
    property int contentHAlign: Qt.AlignHCenter; //Qt.AlignHCenter 、 Qt.AlignLeft or Qt.AlignRight

    property alias theme: mTheme;
    property alias border: mBorderInfo;
    property alias content: mTextInfo;
    property alias background: mRectangleInfo

    property Component contentComponent;
    property Component backgroundComponent;

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
        anchors.verticalCenter: mControl.verticalCenter
        x: {
            if(contentHAlign == Qt.AlignLeft) {
                return padding;
            } else if(contentHAlign == Qt.AlignRight) {
                return mControl.width - width - padding;
            }
            return (mControl.width - width) / 2;
        }
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

    contentComponent: QExtQuickText {
        enabled: false;
        anchors.centerIn: parent;
        text: mControl.content.text;
        font: mControl.content.font;
        color: mControl.content.color;
        scale: mTheme.scale;

        theme.childName: "text"
        theme.parent: {
            return mTheme;
        }
    }

    QExtQmlTextInfo {
        id: mTextInfo
        color: "#2D2D2D"
        text: "Button"
    }

    QExtQmlBorderInfo {
        id: mBorderInfo
        width: 1
        color: "#DCDCDC"
    }

    QExtQmlRectangleInfo {
        id: mRectangleInfo
        color: "#FCFCFC"
        radius: 2
    }

    QExtQmlThemeBinder {
        id: mTheme;
        className: "QExtQuickButton"
        state: mControl.state;

        property double scale: 1;
        Component.onCompleted: {
            initialize();
        }
    }
}
