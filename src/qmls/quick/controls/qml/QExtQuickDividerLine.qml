import QtQuick 2.6

import QExtQml.Theme 1.4

Rectangle {
    id: mControl
    color: "#DCDFE6"

    property alias theme: mTheme

    QExtQmlThemeBinder {
        id: mTheme
        state: mControl.state
        className: "QExtQuickDividerLine"

        property alias color: mControl.color

        Component.onCompleted: initialize();
    }
}
