import QtQuick 2.12
import QtQml 2.12
import QExtQuick.Controls 1.2

QtObject {
    property bool enabled: true
    property bool defaultCollapsed: true

    property string titleText: ""
    property font titleTextFont
    property string titleTextColor: QExtQuickPalette.textPrimaryColor
    property real titleTextOpacity: 1

    property string titleIconSource
    property string titleIconColor: QExtQuickPalette.textPrimaryColor

    property Component contentItem

    contentItem : Rectangle {
        color: "LightGray"
        height: 100
    }
}
