import QtQuick 2.6

import QExtQuick.Controls 1.4

Column{
    spacing: 10;
    Row{
        height: 40;
        spacing: 10
        QExtQuickButton {
            width: implicitWidth
            content.text: "Default"
        }

        QExtQuickButton{
            content.text: "Primary"
            content.color: "#FFF"
            content.font.bold: true;
            background.color: "#46A0FC"
            theme.groupName: "primary"
        }

        QExtQuickButton{
            content.text: "Success"
            content.font.bold: true;
            content.color: "#FFF"
            background.color: "#6AC044"
            theme.groupName: "success"
        }

        QExtQuickButton{
            content.text: "Warning"
            content.font.bold: true;
            content.color: "#FFF"
            background.color: "#E4A147"
            theme.groupName: "warning"
        }

        QExtQuickButton{
            content.text: "Danger"
            content.font.bold: true;
            content.color: "#FFF"
            background.color: "#F36D6F"
            theme.groupName: "danger"
        }
    }

    Row{
        height: 40;
        spacing: 10
        QExtQuickButton{
            content.text: "Default"
        }

        QExtQuickButton{
            content.text: "Primary"
            content.color: "#46A0FC"
            content.font.bold: true;
            background.color: "#ECF5FF"
            border.color: "#46A0FC"
            theme.enabled: false
        }

        QExtQuickButton{
            content.text: "Success"
            content.font.bold: true;
            content.color: "#6AC044"
            background.color: "#F0F9EB"
            border.color: "#6AC044"
            theme.enabled: false
        }

        QExtQuickButton{
            content.text: "Warning"
            content.font.bold: true;
            content.color: "#E4A147"
            background.color: "#FDF6ED"
            border.color: "#E4A147"
            theme.enabled: false
        }

        QExtQuickButton{
            content.text: "Danger"
            content.font.bold: true;
            content.color: "#F36D6F"
            background.color: "#FEF0F0"
            border.color: "#F36D6F"
            theme.enabled: false
        }
    }

}

