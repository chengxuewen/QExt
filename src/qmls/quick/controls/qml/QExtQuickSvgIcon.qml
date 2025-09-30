import QtQuick 2.6

import QExtQml 1.4
import QExtQml.Theme 1.4

Item {
    id: mControl
    width: 16
    height: 16

    property color color
    property string source
    property bool smooth: true
    property bool asynchronous: true
    readonly property alias status: mLoader.itemStatus

    property alias theme: mTheme

    Loader {
        id: mLoader
        anchors.fill: parent
        onLoaded: {
            if (item) {
                item.statusChanged.connect(function () {
                    mLoader.itemStatus = item.status;
                });
            }
        }
        property int itemStatus: Image.Null
    }

    Component.onCompleted: {
        mLoader.setSource("qrc:/QExtQuickControls/qml/QExtQuickSvgIcon" + QExtQml.svgIconVersion() + ".qml", {
                              color: mControl.color,
                              source: mControl.source,
                              smooth: mControl.smooth,
                              asynchronous: mControl.asynchronous,
                          });
    }
    onColorChanged: {
        if (mLoader.item) {
            mLoader.item.color = mControl.color;
        }
    }
    onSourceChanged: {
        if (mLoader.item) {
            mLoader.item.source = mControl.source;
        }
    }
    onSmoothChanged: {
        if (mLoader.item) {
            mLoader.item.smooth = mControl.smooth;
        }
    }
    onAsynchronousChanged: {
        if (mLoader.item) {
            mLoader.item.asynchronous = mControl.asynchronous;
        }
    }

    QExtQmlThemeBinder {
        id: mTheme
        className: "QExtQuickSVGImage";
        state: mControl.state

        property alias color: mControl.color
        property alias width: mControl.width
        property alias height: mControl.height
        property alias source: mControl.source

        Component.onCompleted: initialize();
    }
}
