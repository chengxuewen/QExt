import QtQuick 2.6

import QExtQml 1.4
import QExtQml.Theme 1.4
import QExtQml.FontIcon 1.4
import QExtQuick.Controls 1.4

Item {
    id: mControl
    width: 16
    height: 16

    property color color
    property string source
    property alias theme: mTheme
    property alias text: mContent.text
    property alias family: mContent.font.family

    Text {
        id: mContent
        anchors.fill: parent
        enabled: false
        color: mControl.color
        font.pixelSize: Math.max(mControl.width, mControl.height)
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    QExtQmlFontIconInfo {
        id: mFontIconInfo
        property alias source: mControl.source
        onSourceChanged: {
            if (QExtQmlFontIcon.isFontIconUrl(source)) {
                QExtQmlFontIcon.parseFontIconInfoFromUrl(source, mFontIconInfo);
                mContent.font.family = mFontIconInfo.family
                mControl.text = mFontIconInfo.text
            } else {
                mControl.text = source
            }
        }
    }

    QExtQmlThemeBinder {
        id: mTheme
        className: "QExtQuickFontIcon";
        state: mControl.state;

        property alias color: mControl.color
        property alias width: mControl.width
        property alias height: mControl.height
        property alias source: mControl.source

        Component.onCompleted: initialize();
    }
}
