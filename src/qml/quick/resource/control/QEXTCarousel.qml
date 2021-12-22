import QtQuick 2.12
import QtQml 2.0
import QtQuick.Controls 2.12

import QEXTQuick 1.0

Item {
    id: qextCarousel
    clip: true

    signal triggered(var modelData)

    property int itemWidth
    property int itemHeight
    property int margen: itemWidth / 3
    property int interval: 2000
    property int pathItemCount: 3

    property alias count: mPathView.count
    property alias currentIndex: mPathView.currentIndex
    property alias currentItem: mPathView.currentItem

    default property alias childs: qextCarousel.chillilst

    property list<QEXTCarouselElement> chillilst

    property Component contentItem

    function addElement(element) {
        mPathView.model.append(element)
    }

    function decrementCurrentIndex() {
        mPathView.decrementCurrentIndex()
    }

    function incrementCurrentIndex() {
        mPathView.incrementCurrentIndex()
    }

    contentItem: QEXTAvatar {
        source: modelData.imageSource
        radius: 10
    }

    PathView {
        id: mPathView
        anchors.fill: parent
        interactive: false
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        pathItemCount: qextCarousel.pathItemCount
        cacheItemCount: model.count
        highlightRangeMode: PathView.StrictlyEnforceRange
        model: ListModel{}

        delegate: Loader {
            property int itemIndex: index
            property var modelData: model
            property bool isCurrentItem: PathView.isCurrentItem

            width: itemWidth
            height: itemHeight
            z: PathView.zOrder
            scale: PathView.itemScale
            visible: PathView.onPath

            sourceComponent: contentItem
        }

        path: Path {
            startX: margen
            startY: qextCarousel.height / 2
            PathAttribute {
                name: "zOrder"
                value: 0
            }
            PathAttribute {
                name: "itemScale"
                value: 0.8
            }
            PathLine {
                x: qextCarousel.width / 2
                y: qextCarousel.height / 2
            }
            PathAttribute {
                name: "zOrder"
                value: 10
            }
            PathAttribute {
                name: "itemScale"
                value: 1
            }
            PathLine {
                x: qextCarousel.width - margen
                y: qextCarousel.height / 2
            }
            PathAttribute {
                name: "zOrder"
                value: 0
            }
            PathAttribute {
                name: "itemScale"
                value: 0.8
            }
        }

        Component.onCompleted: {
            if (chillilst.length >= 3 && pathItemCount < 3) {
                pathItemCount = 3
            }
            for (var i in chillilst) {
                mPathView.model.append(chillilst[i])
            }
        }

        onCurrentIndexChanged: mAutoNextTimer.restart()
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        property int px: 0
        property int dis: 10

        onPressed: px = mouseX
        onReleased: {
            if (Math.abs(px - mouseX) > dis) {
                if (px < mouseX) {
                    mPathView.decrementCurrentIndex()
                } else if (px > mouseX) {
                    mPathView.incrementCurrentIndex()
                }
            } else {
                var c = mPathView.currentItem
                if (mouseX < c.x) {
                    mPathView.decrementCurrentIndex()
                } else if (mouseX > c.x + c.width) {
                    mPathView.incrementCurrentIndex()
                } else {
                    triggered(c.modelData)
                }
            }
            mAutoNextTimer.restart()
        }
    }

    Timer {
        id: mAutoNextTimer
        interval: qextCarousel.interval
        running: qextCarousel.interval > 0
        repeat: true
        onTriggered: mPathView.incrementCurrentIndex()
    }
}
