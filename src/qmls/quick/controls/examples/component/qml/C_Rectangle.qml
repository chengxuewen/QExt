import QtQuick 2.0

import QExtQuick.Controls 1.4

Column {
    spacing: 15

    Row {
        id:layout
        spacing: 10


        QExtQuickRectangle {
            width: 100
            height: 80
            color: "#409EFF"
            radius: 2
            theme.enabled: false
            Text{
                x: 10
                y: 10
                color: "#FFF"
                text: (parent.color + "").toUpperCase()
            }

            Row {
                anchors.bottom: parent.bottom
                Rectangle {
                    width: 50
                    height: 30
                    color: "#DAECFE"
                }

                Rectangle {
                    width: 50
                    height: 30
                    color: "#ECF5FF"
                }
            }
        }


        QExtQuickRectangle {
            width: 100
            height: 80
            color: "#6AC044"
            radius: 2
            theme.enabled: false
            Text {
                x: 10
                y: 10
                color: "#FFF"
                text: (parent.color + "").toUpperCase()
            }

            Row {
                anchors.bottom: parent.bottom
                Rectangle {
                    width: 50
                    height: 30
                    color: "#E1F2D9"
                }

                Rectangle {
                    width: 50
                    height: 30
                    color: "#F0F9EB"
                }
            }
        }


        QExtQuickRectangle {
            width: 100
            height: 80
            color: "#E4A147"
            radius: 2
            theme.enabled: false
            Text {
                x: 10
                y: 10
                color: "#FFF"
                text: (parent.color + "").toUpperCase()
            }

            Row {
                anchors.bottom: parent.bottom
                Rectangle {
                    width: 50
                    height: 30
                    color: "#FAECD9"
                }

                Rectangle {
                    width: 50
                    height: 30
                    color: "#FDF6ED"
                }
            }
        }


        QExtQuickRectangle {
            width: 100
            height: 80
            color: "#F36D6F"
            radius: 2
            theme.enabled: false
            Text {
                x: 10
                y: 10
                color: "#FFF"
                text: (parent.color + "").toUpperCase()
            }

            Row {
                anchors.bottom: parent.bottom
                Rectangle {
                    width: 50
                    height: 30
                    color: "#FCE2E2"
                }

                Rectangle {
                    width: 50
                    height: 30
                    color: "#FEF0F0"
                }
            }
        }

    }

}
