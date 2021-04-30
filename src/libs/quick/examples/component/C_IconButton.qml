import QtQuick 2.6
import QtQml 2.12
import QtQuick.Controls 2.12
import QEXTQuick 1.2

Column{
    spacing: 10

    CheckBox {
        id: mIconVisiableCheckBox
        text: "Icon visiable"
        checked: true
    }

    Row{
        height: 40
        spacing: 10

        QEXTIconButton{
            text: "Normal"
            textFont.bold: true
            iconSource: QEXTQuickFontAwesome.FA_apple
            iconColor: textColor
            iconVisiable: mIconVisiableCheckBox.checked
        }

        QEXTIconButton{
            text: "Primary"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#46A0FC"
            iconSource: QEXTQuickFontAwesome.FA_apple
            iconColor: textColor
            iconVisiable: mIconVisiableCheckBox.checked
        }

        QEXTIconButton{
            text: "Success"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#6AC044"
            iconSource: QEXTQuickFontAwesome.FA_android
            iconColor: textColor
        }

        QEXTIconButton{
            text: "Warning"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#E4A147"
            iconSource: QEXTQuickFontAwesome.FA_github
            iconColor: textColor
        }

        QEXTIconButton{
            text: "Danger"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#F36D6F"
            iconSource: QEXTQuickFontAwesome.FA_pencil
            iconColor: textColor
        }
    }

    Row{
        height: 40
        spacing: 10
        QEXTIconButton{
            iconDisplay: QEXTQuick.IconDisplay_IconOnly
            iconSource: QEXTQuickFontAwesome.FA_apple
            backgroundRadius: height / 2
        }

        QEXTIconButton{
            iconDisplay: QEXTQuick.IconDisplay_IconOnly
            iconSource: QEXTQuickFontAwesome.FA_android
            iconColor: "#46A0FC"
            backgroundColor: "#ECF5FF"
            backgroundBorderColor: "#46A0FC"
            backgroundRadius: height / 2
        }

        QEXTIconButton{
            iconDisplay: QEXTQuick.IconDisplay_IconOnly
            iconSource: QEXTQuickFontAwesome.FA_windows
            iconColor: "#6AC044"
            backgroundColor: "#F0F9EB"
            backgroundBorderColor: "#6AC044"
            backgroundRadius: height / 2
        }

        QEXTIconButton{
            iconDisplay: QEXTQuick.IconDisplay_IconOnly
            iconSource: QEXTQuickFontAwesome.FA_github
            iconColor: "#E4A147"
            backgroundColor: "#FDF6ED"
            backgroundBorderColor: "#E4A147"
            backgroundRadius: height / 2
        }

        QEXTIconButton{
            iconDisplay: QEXTQuick.IconDisplay_IconOnly
            iconSource: QEXTQuickFontAwesome.FA_star_o
            iconColor: "#F36D6F"
            backgroundColor: "#FEF0F0"
            backgroundBorderColor: "#F36D6F"
            backgroundRadius: height / 2
        }
    }

    Row{
        height: 40
        spacing: 10
        QEXTIconButton{
            text: "Normal"
            textFont.bold: true
            iconDisplay: QEXTQuick.IconDisplay_TextOnly
            iconSource: QEXTQuickFontAwesome.FA_apple
            iconColor: textColor
        }

        QEXTIconButton{
            text: "Primary"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#46A0FC"
            iconDisplay: QEXTQuick.IconDisplay_TextOnly
            iconSource: QEXTQuickFontAwesome.FA_apple
            iconColor: textColor
        }

        QEXTIconButton{
            text: "Success"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#6AC044"
            iconDisplay: QEXTQuick.IconDisplay_TextOnly
            iconSource: QEXTQuickFontAwesome.FA_android
            iconColor: textColor
        }

        QEXTIconButton{
            text: "Warning"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#E4A147"
            iconDisplay: QEXTQuick.IconDisplay_TextOnly
            iconSource: QEXTQuickFontAwesome.FA_github
            iconColor: textColor
        }

        QEXTIconButton{
            text: "Danger"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#F36D6F"
            iconDisplay: QEXTQuick.IconDisplay_TextOnly
            iconSource: QEXTQuickFontAwesome.FA_pencil
            iconColor: textColor
        }
    }

    Row{
        height: 40
        spacing: 10
        QEXTIconButton{
            text: "Normal"
            textFont.bold: true
            iconDisplay: QEXTQuick.IconDisplay_Right
            iconSource: QEXTQuickFontAwesome.FA_apple
            iconColor: textColor
        }

        QEXTIconButton{
            text: "Primary"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#46A0FC"
            iconDisplay: QEXTQuick.IconDisplay_Right
            iconSource: QEXTQuickFontAwesome.FA_apple
            iconColor: textColor
        }

        QEXTIconButton{
            text: "Success"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#6AC044"
            iconDisplay: QEXTQuick.IconDisplay_Right
            iconSource: QEXTQuickFontAwesome.FA_android
            iconColor: textColor
        }

        QEXTIconButton{
            text: "Warning"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#E4A147"
            iconDisplay: QEXTQuick.IconDisplay_Right
            iconSource: QEXTQuickFontAwesome.FA_github
            iconColor: textColor
        }

        QEXTIconButton{
            text: "Danger"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#F36D6F"
            iconDisplay: QEXTQuick.IconDisplay_Right
            iconSource: QEXTQuickFontAwesome.FA_pencil
            iconColor: textColor
        }
    }

    Row{
        height: 60
        spacing: 10
        QEXTIconButton{
            width: 60
            height: 60
            text: "Normal"
            textFont.bold: true
            backgroundRadius: 10
            iconDisplay: QEXTQuick.IconDisplay_Bottom
            iconSource: QEXTQuickFontAwesome.FA_apple
            iconColor: textColor
        }

        QEXTIconButton{
            width: 60
            height: 60
            text: "Primary"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#46A0FC"
            backgroundRadius: 10
            iconDisplay: QEXTQuick.IconDisplay_Bottom
            iconSource: QEXTQuickFontAwesome.FA_apple
            iconColor: textColor
        }

        QEXTIconButton{
            width: 60
            height: 60
            text: "Success"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#6AC044"
            backgroundRadius: 10
            iconDisplay: QEXTQuick.IconDisplay_Bottom
            iconSource: QEXTQuickFontAwesome.FA_android
            iconColor: textColor
        }

        QEXTIconButton{
            width: 60
            height: 60
            text: "Warning"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#E4A147"
            backgroundRadius: 10
            iconDisplay: QEXTQuick.IconDisplay_Bottom
            iconSource: QEXTQuickFontAwesome.FA_github
            iconColor: textColor
        }

        QEXTIconButton{
            width: 60
            height: 60
            text: "Danger"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#F36D6F"
            backgroundRadius: 10
            iconDisplay: QEXTQuick.IconDisplay_Bottom
            iconSource: QEXTQuickFontAwesome.FA_pencil
            iconColor: textColor
        }
    }

    Row{
        height: 60
        spacing: 10
        QEXTIconButton{
            width: 60
            height: 60
            text: "Normal"
            textFont.bold: true
            backgroundRadius: 10
            iconDisplay: QEXTQuick.IconDisplay_Top
            iconSource: QEXTQuickFontAwesome.FA_apple
            iconColor: textColor
        }

        QEXTIconButton{
            width: 60
            height: 60
            text: "Primary"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#46A0FC"
            backgroundRadius: 10
            iconDisplay: QEXTQuick.IconDisplay_Top
            iconSource: QEXTQuickFontAwesome.FA_apple
            iconColor: textColor
        }

        QEXTIconButton{
            width: 60
            height: 60
            text: "Success"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#6AC044"
            backgroundRadius: 10
            iconDisplay: QEXTQuick.IconDisplay_Top
            iconSource: QEXTQuickFontAwesome.FA_android
            iconColor: textColor
        }

        QEXTIconButton{
            width: 60
            height: 60
            text: "Warning"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#E4A147"
            backgroundRadius: 10
            iconDisplay: QEXTQuick.IconDisplay_Top
            iconSource: QEXTQuickFontAwesome.FA_github
            iconColor: textColor
        }

        QEXTIconButton{
            width: 60
            height: 60
            text: "Danger"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#F36D6F"
            backgroundRadius: 10
            iconDisplay: QEXTQuick.IconDisplay_Top
            iconSource: QEXTQuickFontAwesome.FA_pencil
            iconColor: textColor
        }
    }
}

