import QtQuick 2.12
import QExtQuick.Controls 1.2

Rectangle {
    id: qextDividerLine
    color: QExtQuickPalette.borderLevel1Color
    width: verticalLine ? lineWidth : lineLength
    height: verticalLine ? lineLength : lineWidth

    property bool verticalLine: true
    property real lineLength: 40
    property real lineWidth: 2
}
