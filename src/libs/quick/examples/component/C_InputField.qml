import QtQuick 2.6
import QEXTQuick 1.2

Column{
    spacing: 10
    Row{
        spacing: 30

        QEXTInputField{
            width: 180
            placeholderText: "Default Input"
        }

        QEXTInputField{
            width: 180
            placeholderIconSource: QEXTQuickFontAwesome.FA_search
            placeholderText: "Icon Placeholder"
        }

    }


    Row{
        spacing: 30

        QEXTInputField{
            width: 180
            backgroundRadius: height/2
            placeholderIconSource: QEXTQuickFontAwesome.FA_pencil
            placeholderText: "Left Align"
            placeholderPosition: QEXTQuick.Position_Left
        }

        QEXTInputField{
            width: 180
            backgroundRadius: height/2
            placeholderIconSource: QEXTQuickFontAwesome.FA_inbox
            text: "Clearn Input"
            clearable: true
            placeholderPosition: QEXTQuick.Position_Left
        }

    }

}
