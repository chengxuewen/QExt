import QtQuick 2.12
import QExtQuick.Controls 1.2

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
            placeholderIconSource: QExtQuickFontAwesome.FA_search
            placeholderText: "Icon Placeholder"
        }

    }


    Row{
        spacing: 30

        QExtQuickInputField{
            width: 180
            backgroundRadius: height/2
            placeholderIconSource: QExtQuickFontAwesome.FA_pencil
            placeholderText: "Left Align"
            placeholderPosition: QExtQuickControls.Position_Left
        }

        QExtQuickInputField{
            width: 180
            backgroundRadius: height/2
            placeholderIconSource: QExtQuickFontAwesome.FA_inbox
            text: "Clearn Input"
            clearable: true
            placeholderPosition: QExtQuickControls.Position_Left
        }

    }

}
