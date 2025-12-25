import QtQml 2.0
import QtQuick 2.6

import QExtQml 1.4
import QExtQml.Theme 1.4
import QExtQuick.Controls 1.4

Canvas {
    id: mControl

    property bool smooth: true

    property real topLeftRadius: 0
    property real topRightRadius: 0
    property real bottomLeftRadius: 0
    property real bottomRightRadius: 0

    property alias border: mBorderInfo
    property alias background: mBackgroundInfo
    property alias color: mBackgroundInfo.color
    property alias radius: mBackgroundInfo.radius

    QExtQmlBorderInfo {
        id: mBorderInfo
        width: 1
        color: "#DCDCDC"
        onWidthChanged: {
            requestPaint();
        }
        onColorChanged: {
            requestPaint();
        }
    }

    QExtQmlBackgroundInfo {
        id: mBackgroundInfo
        color: "#FCFCFC"
        radius: 2
        onColorChanged: {
            requestPaint();
        }
        onRadiusChanged: {
            requestPaint();
        }
    }

    onTopLeftRadiusChanged: {
        requestPaint();
    }
    onTopRightRadiusChanged: {
        requestPaint();
    }
    onBottomLeftRadiusChanged: {
        requestPaint();
    }
    onBottomRightRadiusChanged: {
        requestPaint();
    }

    Component.onCompleted: {
        requestPaint();
    }

    onPaint: {
        var ctx = getContext("2d");

        ctx.reset();
        ctx.imageSmoothingEnabled = smooth;

        // Calculate the actual usable size (considering the border)
        var x = mBorderInfo.width / 2;
        var y = mBorderInfo.width / 2;
        var w = width - mBorderInfo.width;
        var h = height - mBorderInfo.width;

        // Limit the radius to no more than half of the available size
        var maxRadius = Math.min(w, h);
        var tl = Math.min(topLeftRadius, maxRadius);
        var tr = Math.min(topRightRadius, maxRadius);
        var br = Math.min(bottomRightRadius, maxRadius);
        var bl = Math.min(bottomLeftRadius, maxRadius);

        ctx.beginPath();

        // Starting point: after the upper left corner (if the upper left corner is rounded)
        if (tl > 0) {
            ctx.moveTo(x + tl, y);
        } else {
            ctx.moveTo(x, y);
        }

        // Top line&upper right corner
        if (tr > 0) {
            // Top line (to the starting point of the upper right arc)
            ctx.lineTo(x + w - tr, y);
            // Upper right arc
            ctx.arcTo(x + w, y, x + w, y + tr, tr);
        } else {
            // Go directly to the top right corner
            ctx.lineTo(x + w, y);
        }

        // Right line&bottom right corner
        if (br > 0) {
            // Right line (to the starting point of the lower right arc)
            ctx.lineTo(x + w, y + h - br);
            // Bottom right arc
            ctx.arcTo(x + w, y + h, x + w - br, y + h, br);
        } else {
            // Go directly to the bottom right corner
            ctx.lineTo(x + w, y + h);
        }

        // Bottom line&bottom left corner
        if (bl > 0) {
            // Bottom line (to the starting point of the lower left arc)
            ctx.lineTo(x + bl, y + h);
            // Bottom left arc
            ctx.arcTo(x, y + h, x, y + h - bl, bl);
        } else {
            // Go directly to the bottom left corner
            ctx.lineTo(x, y + h);
        }

        // Left line&upper left corner
        if (tl > 0) {
            // Left line (to the starting point of the upper left arc)
            ctx.lineTo(x, y + tl);
            // Upper left arc
            ctx.arcTo(x, y, x + tl, y, tl);
        } else {
            // Directly return to the starting point
            ctx.lineTo(x, y);
        }

        ctx.closePath();

        // =====fill======
        ctx.fillStyle = mBackgroundInfo.color;
        ctx.fill();

        // =====stroke=====
        if (mBorderInfo.width > 0) {
            ctx.lineWidth = mBorderInfo.width;
            ctx.strokeStyle = mBorderInfo.color;
            ctx.stroke();
        }
    }
}
