import QtQuick 2.12
import QEXTQuick 1.0

Column{
    spacing: 10
    Row{
        height: 40
        spacing: 10
        QEXTButton{
            text: "Default"
        }

        QEXTButton{
            text: "Primary"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#46A0FC"
        }

        QEXTButton{
            text: "Success"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#6AC044"
        }

        QEXTButton{
            text: "Warning"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#E4A147"
        }

        QEXTButton{
            text: "Danger"
            textColor: "#FFF"
            textFont.bold: true
            backgroundColor: "#F36D6F"
        }
    }

    Row{
        height: 40
        spacing: 10
        QEXTButton{
            text: "Default"
        }

        QEXTButton{
            text: "Primary"
            textColor: "#46A0FC"
            textFont.bold: true
            backgroundColor: "#ECF5FF"
            backgroundBorderColor: "#46A0FC"
        }

        QEXTButton{
            text: "Success"
            textFont.bold: true
            textColor: "#6AC044"
            backgroundColor: "#F0F9EB"
            backgroundBorderColor: "#6AC044"
        }

        QEXTButton{
            text: "Warning"
            textFont.bold: true
            textColor: "#E4A147"
            backgroundColor: "#FDF6ED"
            backgroundBorderColor: "#E4A147"
        }

        QEXTButton{
            text: "Danger"
            textFont.bold: true
            textColor: "#F36D6F"
            backgroundColor: "#FEF0F0"
            backgroundBorderColor: "#F36D6F"
        }
    }

}

