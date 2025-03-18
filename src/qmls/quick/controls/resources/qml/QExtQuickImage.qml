import QtQml 2.9
import QtQuick 2.9

import QExtQml 1.3
import QExtQuick.Controls 1.3

Item {
    id: root

    property color color
    property bool smooth: true
    property bool mipmap: false
    property bool asynchronous: true
    property string source: image.source
    property int status: Image.Null
    property int fillMode: Image.PreserveAspectCrop

    Loader {
        anchors.fill: parent
        sourceComponent: {
            if (root.source.toLowerCase().indexOf(".svg") !== -1) {
                return mSvgImageComponent
            } else if (QExtQml.isFontIconUrl(root.source)) {
                return mFontImageComponent
            }
            return mDefaultImageComponent
        }
    }

    Component {
        id: mSvgImageComponent
        QExtQuickSvgImage {
            enabled: false
            scale: root.scale
            source: root.source
            color: root.color
        }
    }

    Component {
        id: mFontImageComponent
        QExtQuickFontImage {
            enabled: false
            scale: root.scale
            source: root.source
            color: root.color
        }
    }

    Component {
        id: mDefaultImageComponent
        Image {
            enabled: false
            scale: root.scale
            source: root.source
        }
    }
}
