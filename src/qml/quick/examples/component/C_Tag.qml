import QtQuick 2.12
import QEXTQuick 1.0

Column {
    spacing: 15

    Row {
        id:layout
        spacing: 10
        anchors.horizontalCenter: parent.horizontalCenter
        QEXTTag {
            label.text: "Tag One"
        }

        QEXTTag {
            label.text: "Tag Two"
            label.color: "#6AC044"
            background.color: "#F0F9EB"
            background.border.color: "#6AC044"
        }

        QEXTTag {
            label.text: "Tag Three"
            label.color: "#E4A147"
            background.color: "#FDF6ED"
            background.border.color: "#E4A147"
        }

        QEXTTag {
            label.text: "Tag Four"
            label.color: "#F36D6F"
            background.color: "#FEF0F0"
            background.border.color: "#F36D6F"
        }
    }


    Row {
        spacing: 10
        anchors.horizontalCenter: parent.horizontalCenter
        QEXTTag {
            label.text: "Tag One"
            closable: true
            background.radius: 10
            onClosed: visible = false
        }

        QEXTTag {
            closable: true
            background.radius: 10
            label.text: "Tag Two"
            label.color: "#6AC044"
            background.color: "#F0F9EB"
            background.border.color: "#6AC044"
            onClosed: visible = false
        }

        QEXTTag {
            closable: true
            background.radius: 10
            label.text: "Tag Three"
            label.color: "#E4A147"
            background.color: "#FDF6ED"
            background.border.color: "#E4A147"
            onClosed: visible = false
        }

        QEXTTag {
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
