import QtQuick 2.9

import QExtQml.FontIcon 1.2
import QExtQuick.Controls 1.3

Column{
    spacing: 10
    Row{
        spacing: 30

        QExtQuickInputField{
            width: 180
            placeholderText: "Default Input"
        }

        QExtQuickInputField{
            width: 180
            placeholderIconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_search)
            placeholderText: "Icon Placeholder"
        }

    }


    Row{
        spacing: 30

        QExtQuickInputField{
            width: 180
            backgroundRadius: height/2
            placeholderIconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_pencil)
            placeholderText: "Left Align"
            placeholderPosition: QExtQuickControls.Position_Left
        }

        QExtQuickInputField{
            width: 180
            backgroundRadius: height/2
            placeholderIconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_inbox)
            text: "Clearn Input"
            clearable: true
            placeholderPosition: QExtQuickControls.Position_Left
        }

    }

}
