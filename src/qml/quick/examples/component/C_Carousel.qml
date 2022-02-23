import QtQuick 2.9
import QtQuick.Controls 2.9
import QEXTQmlQuick 1.0

Column {
    spacing: 20
    QEXTQmlQuickCarousel{
        width: 400
        height: 180
        itemWidth: 350
        itemHeight:160

        QEXTQmlQuickCarouselElement {
            otherData: "#409EFF"
        }

        QEXTQmlQuickCarouselElement {
            otherData: "#67C23A"
        }

        QEXTQmlQuickCarouselElement {
            otherData: "#E6A23C"
        }

        QEXTQmlQuickCarouselElement {
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

    QEXTQmlQuickCarousel {
        width: 400
        height: 180
        itemWidth: width
        itemHeight:height
        pathItemCount: 3

        QEXTQmlQuickCarouselElement {
            otherData: "#409EFF"
        }

        QEXTQmlQuickCarouselElement {
            otherData: "#67C23A"
        }

        QEXTQmlQuickCarouselElement {
            otherData: "#E6A23C"
        }

        QEXTQmlQuickCarouselElement {
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
