import QtQml 2.9
import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQml.FontIcon 1.3
import QExtQuick.Controls 1.3

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

        QExtQuickToolButton{
            text: "Normal"
            textFont.bold: true
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_apple)
            iconColor: textColor
            iconVisible: mIconVisibleCheckBox.checked
        }

        QExtQuickToolButton{
            text: "Primary"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#46A0FC"
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_apple)
            iconColor: textColor
            iconVisible: mIconVisibleCheckBox.checked
        }

        QExtQuickToolButton{
            text: "Success"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#6AC044"
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_android)
            iconColor: textColor
        }

        QExtQuickToolButton{
            text: "Warning"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#E4A147"
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_github)
            iconColor: textColor
        }

        QExtQuickToolButton{
            text: "Danger"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#F36D6F"
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_pencil)
            iconColor: textColor
        }
    }

    Row{
        height: 40
        spacing: 10
        QExtQuickToolButton{
            iconDisplay: QExtQuickControls.IconDisplay_IconOnly
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_apple)
            backgroundRadius: height / 2
        }

        QExtQuickToolButton{
            iconDisplay: QExtQuickControls.IconDisplay_IconOnly
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_android)
            iconColor: "#46A0FC"
            backgroundColor: "#ECF5FF"
            backgroundBorderColor: "#46A0FC"
            backgroundRadius: height / 2
        }

        QExtQuickToolButton{
            iconDisplay: QExtQuickControls.IconDisplay_IconOnly
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_windows)
            iconColor: "#6AC044"
            backgroundColor: "#F0F9EB"
            backgroundBorderColor: "#6AC044"
            backgroundRadius: height / 2
        }

        QExtQuickToolButton{
            iconDisplay: QExtQuickControls.IconDisplay_IconOnly
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_github)
            iconColor: "#E4A147"
            backgroundColor: "#FDF6ED"
            backgroundBorderColor: "#E4A147"
            backgroundRadius: height / 2
        }

        QExtQuickToolButton{
            iconDisplay: QExtQuickControls.IconDisplay_IconOnly
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_star_o)
            iconColor: "#F36D6F"
            backgroundColor: "#FEF0F0"
            backgroundBorderColor: "#F36D6F"
            backgroundRadius: height / 2
        }
    }

    Row{
        height: 40
        spacing: 10
        QExtQuickToolButton{
            text: "Normal"
            textFont.bold: true
            iconDisplay: QExtQuickControls.IconDisplay_TextOnly
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_apple)
            iconColor: textColor
        }

        QExtQuickToolButton{
            text: "Primary"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#46A0FC"
            iconDisplay: QExtQuickControls.IconDisplay_TextOnly
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_apple)
            iconColor: textColor
        }

        QExtQuickToolButton{
            text: "Success"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#6AC044"
            iconDisplay: QExtQuickControls.IconDisplay_TextOnly
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_android)
            iconColor: textColor
        }

        QExtQuickToolButton{
            text: "Warning"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#E4A147"
            iconDisplay: QExtQuickControls.IconDisplay_TextOnly
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_github)
            iconColor: textColor
        }

        QExtQuickToolButton{
            text: "Danger"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#F36D6F"
            iconDisplay: QExtQuickControls.IconDisplay_TextOnly
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_pencil)
            iconColor: textColor
        }
    }

    Row{
        height: 40
        spacing: 10
        QExtQuickToolButton{
            text: "Normal"
            textFont.bold: true
            iconDisplay: QExtQuickControls.IconDisplay_Right
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_apple)
            iconColor: textColor
        }

        QExtQuickToolButton{
            text: "Primary"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#46A0FC"
            iconDisplay: QExtQuickControls.IconDisplay_Right
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_apple)
            iconColor: textColor
        }

        QExtQuickToolButton{
            text: "Success"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#6AC044"
            iconDisplay: QExtQuickControls.IconDisplay_Right
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_android)
            iconColor: textColor
        }

        QExtQuickToolButton{
            text: "Warning"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#E4A147"
            iconDisplay: QExtQuickControls.IconDisplay_Right
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_github)
            iconColor: textColor
        }

        QExtQuickToolButton{
            text: "Danger"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#F36D6F"
            iconDisplay: QExtQuickControls.IconDisplay_Right
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_pencil)
            iconColor: textColor
        }
    }

    Row{
        height: 60
        spacing: 10
        QExtQuickToolButton{
            width: 60
            height: 60
            text: "Normal"
            textFont.bold: true
            backgroundRadius: 10
            iconDisplay: QExtQuickControls.IconDisplay_Bottom
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_apple)
            iconColor: textColor
        }

        QExtQuickToolButton{
            width: 60
            height: 60
            text: "Primary"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#46A0FC"
            backgroundRadius: 10
            iconDisplay: QExtQuickControls.IconDisplay_Bottom
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_apple)
            iconColor: textColor
        }

        QExtQuickToolButton{
            width: 60
            height: 60
            text: "Success"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#6AC044"
            backgroundRadius: 10
            iconDisplay: QExtQuickControls.IconDisplay_Bottom
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_android)
            iconColor: textColor
        }

        QExtQuickToolButton{
            width: 60
            height: 60
            text: "Warning"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#E4A147"
            backgroundRadius: 10
            iconDisplay: QExtQuickControls.IconDisplay_Bottom
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_github)
            iconColor: textColor
        }

        QExtQuickToolButton{
            width: 60
            height: 60
            text: "Danger"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#F36D6F"
            backgroundRadius: 10
            iconDisplay: QExtQuickControls.IconDisplay_Bottom
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_pencil)
            iconColor: textColor
        }
    }

    Row{
        height: 60
        spacing: 10
        QExtQuickToolButton{
            width: 60
            height: 60
            text: "Normal"
            textFont.bold: true
            backgroundRadius: 10
            iconDisplay: QExtQuickControls.IconDisplay_Top
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_apple)
            iconColor: textColor
        }

        QExtQuickToolButton{
            width: 60
            height: 60
            text: "Primary"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#46A0FC"
            backgroundRadius: 10
            iconDisplay: QExtQuickControls.IconDisplay_Top
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_apple)
            iconColor: textColor
        }

        QExtQuickToolButton{
            width: 60
            height: 60
            text: "Success"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#6AC044"
            backgroundRadius: 10
            iconDisplay: QExtQuickControls.IconDisplay_Top
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_android)
            iconColor: textColor
        }

        QExtQuickToolButton{
            width: 60
            height: 60
            text: "Warning"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#E4A147"
            backgroundRadius: 10
            iconDisplay: QExtQuickControls.IconDisplay_Top
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_github)
            iconColor: textColor
        }

        QExtQuickToolButton{
            width: 60
            height: 60
            text: "Danger"
            textFont.bold: true
            textColor: "#FFF"
            backgroundColor: "#F36D6F"
            backgroundRadius: 10
            iconDisplay: QExtQuickControls.IconDisplay_Top
            iconSource: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_pencil)
            iconColor: textColor
        }
    }
}

