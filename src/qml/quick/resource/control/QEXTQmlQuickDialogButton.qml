import QtQuick 2.12
import QEXTQmlQuick 1.0

QEXTQmlQuickObject {
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

    property bool backgroundVisiable: false
    property color backgroundColor: "#FFFFFF"
    property color backgroundBorderColor: QEXTQmlQuickPalette.borderLevel1Color
    property real backgroundBorderWidth: 1
    property real backgroundRadius: 5
}
