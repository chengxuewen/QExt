import QtQuick 2.12
import QtQml 2.12

import QExtQml.Theme 1.4

QtObject {
    property bool enabled: true
    property bool defaultCollapsed: true

    property string titleText: ""
    property font titleTextFont
    property string titleTextColor: QExtQmlThemePalette.textPrimaryColor
    property real titleTextOpacity: 1

    property string titleIconSource
    property string titleIconColor: QExtQmlThemePalette.textPrimaryColor

    property Component contentItem

    contentItem : Rectangle {
        color: "LightGray"
        height: 100
    }
}
