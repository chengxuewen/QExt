import QtQml 2.12
import QtQuick 2.12
import QtQuick.Window 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import QExtQml 1.4
import QExtQml.Theme 1.4

Window {
    width: 600
    height: 400
    visible: true

    Rectangle {
        id: rect
        width: 100
        height: 100
        anchors.centerIn: parent
        color: "red"
    }

    QExtQmlThemeBinder {
        id: mTheme;
        className: "Rectangle"

        property alias color: rect.color;
        property alias width: rect.width;
        property alias height: rect.height;
        property alias radius: rect.radius;
        property alias opacity: rect.opacity;

        property double scale: 1;
        Component.onCompleted: {
            QExtQmlThemeManager.generateThemeTemplateEnable = true;
            initialize();
        }
    }

    Component.onCompleted: {
        console.warn("QExtQml.version()=", QExtQmlThemeManager.version);
        console.warn("borderLevel1Color=", QExtQmlThemeManager.palette.borderLevel1Color);
    }
}
