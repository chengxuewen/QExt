import QtQuick 2.12
import QtQml 2.12
import QtQuick.Controls 2.12
import QExtQuick 1.0

Column{
    spacing: 10

    CheckBox {
        id: mIconVisibleCheckBox
        text: "Icon visiable"
        checked: true
    }

    Row{
        height: 40
        spacing: 10

        QExtQuickIconButton{
            text: "Normal"
            textFont.bold: true
            iconSource: QExtQuickFontAwesome.FA_apple
            iconColor: textColor
            iconVisible: mIconVisibleCheckBox.checked
        }

        QExtQuickIconButton{
            text: "Primary"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#46A0FC"
            iconSource: QExtQuickFontAwesome.FA_apple
            iconColor: textColor
            iconVisible: mIconVisibleCheckBox.checked
        }

        QExtQuickIconButton{
            text: "Success"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#6AC044"
            iconSource: QExtQuickFontAwesome.FA_android
            iconColor: textColor
        }

        QExtQuickIconButton{
            text: "Warning"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#E4A147"
            iconSource: QExtQuickFontAwesome.FA_github
            iconColor: textColor
        }

        QExtQuickIconButton{
            text: "Danger"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#F36D6F"
            iconSource: QExtQuickFontAwesome.FA_pencil
            iconColor: textColor
        }
    }

    Row{
        height: 40
        spacing: 10
        QExtQuickIconButton{
            iconDisplay: QExtQuick.IconDisplay_IconOnly
            iconSource: QExtQuickFontAwesome.FA_apple
            backgroundRadius: height / 2
        }

        QExtQuickIconButton{
            iconDisplay: QExtQuick.IconDisplay_IconOnly
            iconSource: QExtQuickFontAwesome.FA_android
            iconColor: "#46A0FC"
            backgroundColor: "#ECF5FF"
            backgroundBorderColor: "#46A0FC"
            backgroundRadius: height / 2
        }

        QExtQuickIconButton{
            iconDisplay: QExtQuick.IconDisplay_IconOnly
            iconSource: QExtQuickFontAwesome.FA_windows
            iconColor: "#6AC044"
            backgroundColor: "#F0F9EB"
            backgroundBorderColor: "#6AC044"
            backgroundRadius: height / 2
        }

        QExtQuickIconButton{
            iconDisplay: QExtQuick.IconDisplay_IconOnly
            iconSource: QExtQuickFontAwesome.FA_github
            iconColor: "#E4A147"
            backgroundColor: "#FDF6ED"
            backgroundBorderColor: "#E4A147"
            backgroundRadius: height / 2
        }

        QExtQuickIconButton{
            iconDisplay: QExtQuick.IconDisplay_IconOnly
            iconSource: QExtQuickFontAwesome.FA_star_o
            iconColor: "#F36D6F"
            backgroundColor: "#FEF0F0"
            backgroundBorderColor: "#F36D6F"
            backgroundRadius: height / 2
        }
    }

    Row{
        height: 40
        spacing: 10
        QExtQuickIconButton{
            text: "Normal"
            textFont.bold: true
            iconDisplay: QExtQuick.IconDisplay_TextOnly
            iconSource: QExtQuickFontAwesome.FA_apple
            iconColor: textColor
        }

        QExtQuickIconButton{
            text: "Primary"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#46A0FC"
            iconDisplay: QExtQuick.IconDisplay_TextOnly
            iconSource: QExtQuickFontAwesome.FA_apple
            iconColor: textColor
        }

        QExtQuickIconButton{
            text: "Success"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#6AC044"
            iconDisplay: QExtQuick.IconDisplay_TextOnly
            iconSource: QExtQuickFontAwesome.FA_android
            iconColor: textColor
        }

        QExtQuickIconButton{
            text: "Warning"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#E4A147"
            iconDisplay: QExtQuick.IconDisplay_TextOnly
            iconSource: QExtQuickFontAwesome.FA_github
            iconColor: textColor
        }

        QExtQuickIconButton{
            text: "Danger"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#F36D6F"
            iconDisplay: QExtQuick.IconDisplay_TextOnly
            iconSource: QExtQuickFontAwesome.FA_pencil
            iconColor: textColor
        }
    }

    Row{
        height: 40
        spacing: 10
        QExtQuickIconButton{
            text: "Normal"
            textFont.bold: true
            iconDisplay: QExtQuick.IconDisplay_Right
            iconSource: QExtQuickFontAwesome.FA_apple
            iconColor: textColor
        }

        QExtQuickIconButton{
            text: "Primary"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#46A0FC"
            iconDisplay: QExtQuick.IconDisplay_Right
            iconSource: QExtQuickFontAwesome.FA_apple
            iconColor: textColor
        }

        QExtQuickIconButton{
            text: "Success"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#6AC044"
            iconDisplay: QExtQuick.IconDisplay_Right
            iconSource: QExtQuickFontAwesome.FA_android
            iconColor: textColor
        }

        QExtQuickIconButton{
            text: "Warning"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#E4A147"
            iconDisplay: QExtQuick.IconDisplay_Right
            iconSource: QExtQuickFontAwesome.FA_github
            iconColor: textColor
        }

        QExtQuickIconButton{
            text: "Danger"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#F36D6F"
            iconDisplay: QExtQuick.IconDisplay_Right
            iconSource: QExtQuickFontAwesome.FA_pencil
            iconColor: textColor
        }
    }

    Row{
        height: 60
        spacing: 10
        QExtQuickIconButton{
            width: 60
            height: 60
            text: "Normal"
            textFont.bold: true
            backgroundRadius: 10
            iconDisplay: QExtQuick.IconDisplay_Bottom
            iconSource: QExtQuickFontAwesome.FA_apple
            iconColor: textColor
        }

        QExtQuickIconButton{
            width: 60
            height: 60
            text: "Primary"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#46A0FC"
            backgroundRadius: 10
            iconDisplay: QExtQuick.IconDisplay_Bottom
            iconSource: QExtQuickFontAwesome.FA_apple
            iconColor: textColor
        }

        QExtQuickIconButton{
            width: 60
            height: 60
            text: "Success"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#6AC044"
            backgroundRadius: 10
            iconDisplay: QExtQuick.IconDisplay_Bottom
            iconSource: QExtQuickFontAwesome.FA_android
            iconColor: textColor
        }

        QExtQuickIconButton{
            width: 60
            height: 60
            text: "Warning"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#E4A147"
            backgroundRadius: 10
            iconDisplay: QExtQuick.IconDisplay_Bottom
            iconSource: QExtQuickFontAwesome.FA_github
            iconColor: textColor
        }

        QExtQuickIconButton{
            width: 60
            height: 60
            text: "Danger"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#F36D6F"
            backgroundRadius: 10
            iconDisplay: QExtQuick.IconDisplay_Bottom
            iconSource: QExtQuickFontAwesome.FA_pencil
            iconColor: textColor
        }
    }

    Row{
        height: 60
        spacing: 10
        QExtQuickIconButton{
            width: 60
            height: 60
            text: "Normal"
            textFont.bold: true
            backgroundRadius: 10
            iconDisplay: QExtQuick.IconDisplay_Top
            iconSource: QExtQuickFontAwesome.FA_apple
            iconColor: textColor
        }

        QExtQuickIconButton{
            width: 60
            height: 60
            text: "Primary"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#46A0FC"
            backgroundRadius: 10
            iconDisplay: QExtQuick.IconDisplay_Top
            iconSource: QExtQuickFontAwesome.FA_apple
            iconColor: textColor
        }

        QExtQuickIconButton{
            width: 60
            height: 60
            text: "Success"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#6AC044"
            backgroundRadius: 10
            iconDisplay: QExtQuick.IconDisplay_Top
            iconSource: QExtQuickFontAwesome.FA_android
            iconColor: textColor
        }

        QExtQuickIconButton{
            width: 60
            height: 60
            text: "Warning"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#E4A147"
            backgroundRadius: 10
            iconDisplay: QExtQuick.IconDisplay_Top
            iconSource: QExtQuickFontAwesome.FA_github
            iconColor: textColor
        }

        QExtQuickIconButton{
            width: 60
            height: 60
            text: "Danger"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#F36D6F"
            backgroundRadius: 10
            iconDisplay: QExtQuick.IconDisplay_Top
            iconSource: QExtQuickFontAwesome.FA_pencil
            iconColor: textColor
        }
    }
}

