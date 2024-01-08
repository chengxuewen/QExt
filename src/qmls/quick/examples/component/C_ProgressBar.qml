import QtQuick 2.12
import QtQuick.Controls 2.12
import QExtQuick 1.0

Column {
    spacing: 20

    Column {
        width: p1.width
        anchors.horizontalCenter: parent.horizontalCenter
        Label {
            text: p1.formatText
            anchors.horizontalCenter: parent.horizontalCenter
        }
        QExtQuickProgressBar {
            id:p1
            maxValue: 125
            format: "$v - $max"
        }
    }


    Item {
        width: p2.width
        height: p2.height
        anchors.horizontalCenter: parent.horizontalCenter
        QExtQuickProgressBar {
            id: p2
            foreground.color: "#F36D6F"
            format: "$p%"
        }

        Label {
            text: p2.formatText
            anchors.left: p2.right
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
        }
    }


    QExtQuickProgressBar {
        id: p3
        height: 25
        maxValue: 66
        anchors.horizontalCenter: parent.horizontalCenter
        background.radius: p3.height / 2
        foreground.color: "#6AC044"
        format: "$p%"
        Label {
            text: parent.formatText
            anchors.centerIn: parent
            font.pixelSize: 16
            font.bold: true
            color: "#FFF"
        }
    }

    Timer {
        interval: 100
        running: true
        repeat: true
        onTriggered:{
            p1.value += 1
            p2.value += 1
            p3.value += 1

            if(p1.percentage === 1){
                p1.value = 0
            }
            if(p2.percentage === 1){
                p2.value = 0
            }
            if(p3.percentage === 1){
                p3.value = 0
            }
        }
    }


    //custom image progress, for reference
    QExtQuickProgressBar {
        id: imgprogress
        width: 336
        height: 46
        anchors.horizontalCenter: parent.horizontalCenter
        Timer {
            interval: 300
            running: true
            repeat: true
            onTriggered: {
                imgprogress.value += 5
                if(imgprogress.value > imgprogress.maxValue){
                    imgprogress.value = 0
                }
            }
        }

        backgroundItem: Image {
            source: "qrc:/images/progressbg.png"
        }

        foregroundItem: Item {
            Item {
                id: fg
                width: img.width
                height: img.height
                anchors.centerIn: parent
                Image {
                    id:img
                    source: "qrc:/images/progressbar.png"
                    x:width * (1 - imgprogress.percentage) * -1
                    Behavior on x {
                        id:behavior
                        NumberAnimation {
                            duration: 300
                        }
                    }
                }
            }

            Rectangle {
                id: mask
                width: 336 - 26
                height: 46 - 22
                anchors.centerIn: parent
                radius: height / 2
            }

            QExtQuickMask {
                sourceItem: fg
                maskItem: mask
                width: mask.width
                height: mask.height
                anchors.centerIn: parent
            }
        }
    }

}
