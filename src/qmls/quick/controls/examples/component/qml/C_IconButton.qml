import QtQuick 2.6

import QExtQml 1.4
import QExtQml.FontIcon 1.4
import QExtQuick.Controls 1.4

Column{
    spacing: 10;

    Row{
        height: 40;
        spacing: 10

        QExtQuickIconButton{
            content.text: "Primary"
            content.color: "#FFF"
            content.font.bold: true;
            background.color: "#46A0FC"
            icon.source: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_apple)
            icon.color:content.color;
            theme.enabled: false;
        }

        QExtQuickIconButton{
            content.text: "Success"
            content.font.bold: true;
            content.color: "#FFF"
            background.color: "#6AC044"
            icon.source: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_android)
            icon.color:content.color;
            theme.enabled: false;
        }

        QExtQuickIconButton{
            content.text: "Warning"
            content.font.bold: true;
            content.color: "#FFF"
            background.color: "#E4A147"
            icon.source: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_github)
            icon.color:content.color;
            theme.enabled: false;
        }

        QExtQuickIconButton{
            content.text: "Danger"
            content.font.bold: true;
            content.color: "#FFF"
            background.color: "#F36D6F"
            icon.source: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_pencil)
            icon.color:content.color;
            theme.enabled: false;
        }
    }

    Row{
        height: 40;
        spacing: 10
        QExtQuickIconButton{
            width: implicitWidth
            iconPosition: QExtQml.PositionCenter;
            icon.source: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_apple)
            background.radius: height / 2;
        }

        QExtQuickIconButton{
            width: implicitWidth
            iconPosition: QExtQml.PositionCenter;
            icon.source: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_android)
            icon.color: "#46A0FC"
            background.color: "#ECF5FF"
            border.color: "#46A0FC"
            background.radius: height / 2;
            theme.enabled: false;
        }

        QExtQuickIconButton{
            iconPosition: QExtQml.PositionCenter;
            icon.source: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_windows)
            icon.color: "#6AC044"
            background.color: "#F0F9EB"
            border.color: "#6AC044"
            background.radius: height / 2;
            theme.enabled: false;
        }

        QExtQuickIconButton{
            iconPosition: QExtQml.PositionCenter;
            icon.source: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_github)
            icon.color: "#E4A147"
            background.color: "#FDF6ED"
            border.color: "#E4A147"
            background.radius: height / 2;
            theme.enabled: false;
        }

        QExtQuickIconButton{
            iconPosition: QExtQml.PositionCenter;
            icon.source: QExtQmlFontAwesome.fontUrl(QExtQmlFontAwesome.FA_star_o)
            icon.color: "#F36D6F"
            background.color: "#FEF0F0"
            border.color: "#F36D6F"
            background.radius: height / 2;
            theme.enabled: false;
        }
    }

    Row{
        height: 40;
        spacing: 10
        QExtQuickIconButton{
            width: implicitWidth
            iconPosition: QExtQml.PositionCenter;
            icon.source: "qrc:/images/svg0.svg"
            background.radius: height / 2;
        }

        QExtQuickIconButton{
            iconPosition: QExtQml.PositionCenter;
            icon.source: "qrc:/images/svg1.svg"
            icon.color: "#46A0FC"
            background.color: "#ECF5FF"
            border.color: "#46A0FC"
            background.radius: height / 2;
            theme.enabled: false;
        }

        QExtQuickIconButton{
            iconPosition: QExtQml.PositionCenter;
            icon.source: "qrc:/images/svg2.svg"
            icon.color: "#6AC044"
            background.color: "#F0F9EB"
            border.color: "#6AC044"
            background.radius: height / 2;
            theme.enabled: false;
        }

        QExtQuickIconButton{
            iconPosition: QExtQml.PositionCenter;
            icon.source: "qrc:/images/svg3.svg"
            icon.color: "#E4A147"
            background.color: "#FDF6ED"
            border.color: "#E4A147"
            background.radius: height / 2;
            theme.enabled: false;
        }

        QExtQuickIconButton{
            iconPosition: QExtQml.PositionCenter;
            icon.source: "qrc:/images/svg4.svg"
            icon.color: "#F36D6F"
            background.color: "#FEF0F0"
            border.color: "#F36D6F"
            background.radius: height / 2;
            theme.enabled: false;
        }
    }

    Row{
        height: 40;
        spacing: 10
        QExtQuickIconButton{
            width: implicitWidth
            height: implicitHeight
            text: "PositionBottom"
            iconPosition: QExtQml.PositionBottom
            icon.source: "qrc:/images/svg0.svg"
            background.radius: height / 2
        }

        QExtQuickIconButton{
            width: implicitWidth
            height: implicitHeight
            text: "Bottom"
            iconPosition: QExtQml.PositionBottom
            icon.source: "qrc:/images/svg0.svg"
            radius: 2
        }

        QExtQuickIconButton{
            width: implicitWidth
            height: implicitHeight
            text: "Bottom"
            iconPosition: QExtQml.PositionTop
            icon.source: "qrc:/images/svg0.svg"
            radius: 2
        }

        QExtQuickIconButton{
            width: implicitWidth
            height: implicitHeight
            text: "Bottom"
            iconPosition: QExtQml.PositionRight
            icon.source: "qrc:/images/svg0.svg"
            radius: 2
        }

    }
}

