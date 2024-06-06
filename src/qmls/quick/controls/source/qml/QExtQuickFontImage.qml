import QtQml 2.9
import QtQuick 2.9

import QExtQml 1.2
import QExtQuick.Controls 1.2

Item {
    id: root
    width: 16
    height: 16

    property string source
    property alias text: mContentText.text
    property alias color: mContentText.color
    property alias fontFamily: mContentText.font.family

    Text {
        id: mContentText
        anchors.fill: parent
        enabled: false
        color: root.color
        font.pixelSize: Math.max(root.width, root.height)
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    QExtQmlFontIconInfo {
        id: fontIconInfo
    }

    QtObject {
        id: mWrapper
        property alias source: root.source
        // property QExtQmlFontIconInfo fontIconInfo
        onSourceChanged: {
            if (QExtQml.isFontIconUrl(source)) {
                QExtQml.parseFontIconInfoFromUrl(source, fontIconInfo);
                root.fontFamily = fontIconInfo.family
                root.text = fontIconInfo.text
            } else {
                root.text = source
            }
        }
    }
}
