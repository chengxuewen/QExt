import QtQuick 2.9
import QtQml 2.9
import QEXTQmlQuick 1.0

QtObject {
    property bool enabled: true
    property bool defaultCollapsed: true

    property string titleText: ""
    property font titleTextFont
    property string titleTextColor: QEXTQmlQuickPalette.textPrimaryColor
    property real titleTextOpacity: 1

    property string titleIconSource
    property string titleIconColor: QEXTQmlQuickPalette.textPrimaryColor

    property Component contentItem

    contentItem : Rectangle {
        color: "LightGray"
        height: 100
    }
}
