import QtQml 2.2
import QtQuick 2.6

import QExtQml 1.4
import QExtQml.Theme 1.4

Text {
    id: mControl
    color: "#303133"

    property alias theme: mTheme;

    QExtQmlObject {
        id: mFont

        property alias bold: mControl.font.bold;
        property alias family: mControl.font.family;
        property alias pixelSize: mControl.font.pixelSize;
    }

    QExtQmlThemeBinder {
        id:mTheme
        className: "QExtQuickText"
        state: mControl.state;

        property alias color: mControl.color;
        property alias text:  mControl.text;

        property alias bold: mFont.bold;
        property alias family: mFont.family;
        property alias pixelSize: mFont.pixelSize;

        Component.onCompleted: {
            initialize();
        }
    }
}
