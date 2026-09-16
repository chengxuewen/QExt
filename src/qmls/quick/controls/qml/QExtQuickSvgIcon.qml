import QtQuick 2.6
import QtQuick.Window 2.12
import QtQml 2.6

import QExtQml 1.4
import QExtQml.Theme 1.4
import QExtQuick.Controls 1.4

Item {
    id: mControl
    width: 16
    height: 16

    // ↓ 对外契约与改前逐项一致（color/source/smooth/asynchronous/fillMode/status/theme）
    property color color
    property string source
    property bool smooth: true
    property bool asynchronous: false  // 默认同步出图：新色首访无空帧（R-1）
    property int fillMode: Image.Stretch
    readonly property alias status: mImage.status

    property alias theme: mTheme

    property var rootWindow: Window.window                        // 附加属性，入窗后自动重算
    readonly property real dpr: (rootWindow && rootWindow.devicePixelRatio !== undefined)
                                ? rootWindow.devicePixelRatio : 1.0   // 入窗前/析构中 attached 值可能为 undefined

    function hex2(v) {
        var s = Math.round(Math.max(0, Math.min(255, v))).toString(16);
        return s.length < 2 ? "0" + s : s;
    }

    // 量化表与 C++ urlFor()/sizeBucket()/dprBucket() 完全一致（单测对拍锁定，改一处必改另一处）
    function bucketPx(v) {
        var b = [8, 12, 16, 24, 32, 48, 64, 96, 128, 192, 256];
        for (var i = 0; i < b.length; ++i)
            if (v <= b[i])
                return b[i];
        return Math.ceil(v / 256) * 256;
    }
    function bucketDpr(v) {
        var s = [0.5, 1, 1.5, 2, 3, 4];
        for (var i = 0; i < s.length; ++i)
            if (v <= s[i])
                return s[i];
        return 4;                                   // 上限钳制（R-2）
    }

    readonly property url tintUrl: {
        if (mControl.source.length === 0 || mControl.width <= 0 || mControl.height <= 0)
            return "";
        var c = mControl.color;
        return "image://qextsvg/"
             + bucketPx(mControl.width) + "/" + bucketPx(mControl.height) + "/"
             + Math.round(bucketDpr(mControl.dpr) * 100) + "/"
             + hex2(c.a * 255) + hex2(c.r * 255) + hex2(c.g * 255) + hex2(c.b * 255) + "/"
             + encodeURIComponent(mControl.source);
    }

    Image {
        id: mImage
        anchors.fill: parent
        asynchronous: mControl.asynchronous
        smooth: mControl.smooth
        fillMode: mControl.fillMode          // 缩放语义完全交回 Image（D2）
        cache: true
        source: mControl.tintUrl
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
