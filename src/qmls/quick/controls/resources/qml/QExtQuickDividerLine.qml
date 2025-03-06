import QtQuick 2.9

import QExtQuick.Controls 1.3

Rectangle {
    id: root
    color: QExtQuickPalette.borderLevel1Color
    width: verticalLine ? lineWidth : lineLength
    height: verticalLine ? lineLength : lineWidth

    property bool verticalLine: true
    property real lineLength: 40
    property real lineWidth: 2
}
