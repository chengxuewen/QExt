import QtQuick 2.12
import QExtQuick.Controls 1.2

QExtQuickObject {
    id: qextDialogButton

    property var otherData
    property bool lighter: false

    property string text
    property font textFont
    property color textColor

    property string iconSource
    property real iconWidth
    property real iconHeight
    property color iconColor

    property bool backgroundVisible: false
    property color backgroundColor: "#FFFFFF"
    property color backgroundBorderColor: QExtQuickPalette.borderLevel1Color
    property real backgroundBorderWidth: 1
    property real backgroundRadius: 5
}
