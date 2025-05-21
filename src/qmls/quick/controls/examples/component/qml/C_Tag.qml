import QtQuick 2.12
import QExtQuick.Controls 1.3

Column {
    spacing: 15

    Row {
        id:layout
        spacing: 10
        anchors.horizontalCenter: parent.horizontalCenter
        QExtQuickTag {
            label.text: "Tag One"
        }

        QExtQuickTag {
            label.text: "Tag Two"
            label.color: "#6AC044"
            background.color: "#F0F9EB"
            background.border.color: "#6AC044"
        }

        QExtQuickTag {
            label.text: "Tag Three"
            label.color: "#E4A147"
            background.color: "#FDF6ED"
            background.border.color: "#E4A147"
        }

        QExtQuickTag {
            label.text: "Tag Four"
            label.color: "#F36D6F"
            background.color: "#FEF0F0"
            background.border.color: "#F36D6F"
        }
    }


    Row {
        spacing: 10
        anchors.horizontalCenter: parent.horizontalCenter
        QExtQuickTag {
            label.text: "Tag One"
            closable: true
            background.radius: 10
            onClosed: visible = false
        }

        QExtQuickTag {
            closable: true
            background.radius: 10
            label.text: "Tag Two"
            label.color: "#6AC044"
            background.color: "#F0F9EB"
            background.border.color: "#6AC044"
            onClosed: visible = false
        }

        QExtQuickTag {
            closable: true
            background.radius: 10
            label.text: "Tag Three"
            label.color: "#E4A147"
            background.color: "#FDF6ED"
            background.border.color: "#E4A147"
            onClosed: visible = false
        }

        QExtQuickTag {
            closable: true
            background.radius: 10
            label.text: "Tag Four"
            label.color: "#F36D6F"
            background.color: "#FEF0F0"
            background.border.color: "#F36D6F"
            onClosed: visible = false
        }
    }

}
