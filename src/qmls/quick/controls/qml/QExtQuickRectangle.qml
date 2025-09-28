import QtQml 2.2
import QtQuick 2.6

import QExtQml.Theme 1.4

Rectangle {
    id: mControl

    color: "#FAFAFA";
    border.width: 0;
    border.color: Qt.darker(color,1.1)

    property alias theme: mTheme;

    QExtQmlThemeBinder {
        id: mTheme;
        state: mControl.state;
        className: "QExtQuickRectangle";

        property alias color: mControl.color;
        property alias width: mControl.width;
        property alias height: mControl.height;
        property alias radius: mControl.radius;
        property alias opacity: mControl.opacity;

        QExtQmlThemeBinder {
            target: mControl.border;
            childName: "border";

            property int width: mControl.border.width;
            property color color: mControl.border.color;
        }

        Component.onCompleted: {
            initialize();
        }
    }
}
