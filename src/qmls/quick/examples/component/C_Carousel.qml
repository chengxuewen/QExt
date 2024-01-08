import QtQuick 2.12
import QtQuick.Controls 2.12
import QExtQuick 1.0

Column {
    spacing: 20
    QExtQuickCarousel{
        width: 400
        height: 180
        itemWidth: 350
        itemHeight:160

        QExtQuickCarouselElement {
            otherData: "#409EFF"
        }

        QExtQuickCarouselElement {
            otherData: "#67C23A"
        }

        QExtQuickCarouselElement {
            otherData: "#E6A23C"
        }

        QExtQuickCarouselElement {
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

    QExtQuickCarousel {
        width: 400
        height: 180
        itemWidth: width
        itemHeight:height
        pathItemCount: 3

        QExtQuickCarouselElement {
            otherData: "#409EFF"
        }

        QExtQuickCarouselElement {
            otherData: "#67C23A"
        }

        QExtQuickCarouselElement {
            otherData: "#E6A23C"
        }

        QExtQuickCarouselElement {
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
