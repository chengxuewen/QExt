import QtQuick 2.9

import QExtQml 1.4
import QExtQml.FontIcon 1.4
import QExtQuick.Controls 1.4

Column{
    spacing: 10
    Row{
        spacing: 30

        QExtQuickInputField {
            width: 180
            placeholderText: "Default Input"
        }

        QExtQuickInputField {
            width: 180
            placeholderIcon.source: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_search)
            placeholderText: "Icon Placeholder"
        }
    }


    Row{
        spacing: 30

        QExtQuickInputField{
            width: 180
            background.radius: height/2
            placeholderIcon.source: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_pencil)
            placeholderText: "Left Align"
            placeholderPosition: QExtQml.PositionLeft
        }

        QExtQuickInputField{
            width: 180
            background.radius: height/2
            placeholderIcon.source: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_inbox)
            text: "Clearn Input"
            clearable: true
            placeholderPosition: QExtQml.PositionLeft
        }

    }

}
