import QtQuick 2.12

import QExtQuick.Controls 1.3

Column{
    spacing: 10
    Row{
        height: 40
        spacing: 10
        QExtQuickButton{
            text: "Default"
        }

        QExtQuickButton{
            text: "Primary"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#46A0FC"
        }

        QExtQuickButton{
            text: "Success"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#6AC044"
        }

        QExtQuickButton{
            text: "Warning"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#E4A147"
        }

        QExtQuickButton{
            text: "Danger"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#F36D6F"
        }
    }

    Row{
        height: 40
        spacing: 10
        QExtQuickButton{
            text: "Default"
        }

        QExtQuickButton{
            text: "Primary"
            textColor: "#46A0FC"
            textFont.bold: true
            backgroundColor: "#ECF5FF"
            backgroundBorderColor: "#46A0FC"
        }

        QExtQuickButton{
            text: "Success"
            textFont.bold: true
            textColor: "#6AC044"
            backgroundColor: "#F0F9EB"
            backgroundBorderColor: "#6AC044"
        }

        QExtQuickButton{
            text: "Warning"
            textFont.bold: true
            textColor: "#E4A147"
            backgroundColor: "#FDF6ED"
            backgroundBorderColor: "#E4A147"
        }

        QExtQuickButton{
            text: "Danger"
            textFont.bold: true
            textColor: "#F36D6F"
            backgroundColor: "#FEF0F0"
            backgroundBorderColor: "#F36D6F"
        }
    }

}

