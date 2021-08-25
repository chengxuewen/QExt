import QtQuick 2.12
import QtQuick.Controls 2.12
import QEXTQuick 1.2

Column {
    spacing: 20
    QEXTCarousel{
        width: 400
        height: 180
        itemWidth: 350
        itemHeight:160

        QEXTCarouselElement {
            otherData: "#409EFF"
        }

        QEXTCarouselElement {
            otherData: "#67C23A"
        }

        QEXTCarouselElement {
            otherData: "#E6A23C"
        }

        QEXTCarouselElement {
            otherData: "#F56C6C"
        }

        contentItem : Rectangle{
            color: modelData.otherData
            Column{
                anchors.centerIn: parent
                spacing: 10
                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 50
                    color: "#FFF"
                    font.bold: true
                    text: modelData.index
                }
                Label{
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 22
                    color: "#FFF"
                    font.bold: true
                    text: modelData.otherData
                }
            }
        }
    }

    QEXTCarousel {
        width: 400
        height: 180
        itemWidth: width
        itemHeight:height
        pathItemCount: 3

        QEXTCarouselElement {
            otherData: "#409EFF"
        }

        QEXTCarouselElement {
            otherData: "#67C23A"
        }

        QEXTCarouselElement {
            otherData: "#E6A23C"
        }

        QEXTCarouselElement {
            otherData: "#F56C6C"
        }

        contentItem : Rectangle{
            color: modelData.otherData
            Column {
                anchors.centerIn: parent
                spacing: 10
                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 50
                    color: "#FFF"
                    font.bold: true
                    text: modelData.index
                }
                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 22
                    color: "#FFF"
                    font.bold: true
                    text: modelData.otherData
                }
            }
        }
    }
}
