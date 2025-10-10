import QtQml 2.9
import QtQuick 2.9

import QExtQml 1.4
import QExtQml.FontIcon 1.4

Item {
    id: mControl

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
            if (mControl.source.toLowerCase().indexOf(".svg") !== -1) {
                return mSvgIconComponent
            } else if (QExtQmlFontIcon.isFontIconUrl(mControl.source)) {
                return mFontIconComponent
            }
            return mDefaultImageComponent
        }
    }

    Component {
        id: mSvgIconComponent
        QExtQuickSvgIcon {
            enabled: false
            scale: mControl.scale
            source: mControl.source
            color: mControl.color
        }
    }

    Component {
        id: mFontIconComponent
        QExtQuickFontIcon {
            enabled: false
            scale: mControl.scale
            source: mControl.source
            color: mControl.color
        }
    }

    Component {
        id: mDefaultImageComponent
        Image {
            enabled: false
            scale: mControl.scale
            source: mControl.source
        }
    }
}
