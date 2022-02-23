import QtQuick 2.12
import QEXTQmlQuick 1.0

Column{
    spacing: 10
    Row{
        spacing: 30

        QEXTQmlQuickInputField{
            width: 180
            placeholderText: "Default Input"
        }

        QEXTQmlQuickInputField{
            width: 180
            placeholderIconSource: QEXTQmlQuickFontAwesome.FA_search
            placeholderText: "Icon Placeholder"
        }

    }


    Row{
        spacing: 30

        QEXTQmlQuickInputField{
            width: 180
            backgroundRadius: height/2
            placeholderIconSource: QEXTQmlQuickFontAwesome.FA_pencil
            placeholderText: "Left Align"
            placeholderPosition: QEXTQmlQuick.Position_Left
        }

        QEXTQmlQuickInputField{
            width: 180
            backgroundRadius: height/2
            placeholderIconSource: QEXTQmlQuickFontAwesome.FA_inbox
            text: "Clearn Input"
            clearable: true
            placeholderPosition: QEXTQmlQuick.Position_Left
        }

    }

}
