import QtQuick 2.0

import QExtQuick.Controls 1.4

Column {
    spacing: 15

    Row {
        spacing: 10

        QExtQuickRoundedShap {
            width: 100
            height: 60
            color: "red"
            topLeftRadius: 30
        }
        QExtQuickRoundedShap {
            width: 100
            height: 60
            color: "red"
            topLeftRadius: 60
        }
        QExtQuickRoundedShap {
            width: 100
            height: 80
            color: "#409EFF"
            bottomLeftRadius: 50
        }
        QExtQuickRoundedShap {
            width: 100
            height: 80
            color: "#409EFF"
            bottomRightRadius: 50
        }
    }

    Row {
        spacing: 10

        QExtQuickRoundedShap {
            width: 100
            height: 80
            color: "#409EFF"
            topLeftRadius: 30
        }
        QExtQuickRoundedShap {
            width: 100
            height: 80
            color: "#409EFF"
            topRightRadius: 50
        }
        QExtQuickRoundedShap {
            width: 100
            height: 80
            color: "#409EFF"
            bottomLeftRadius: 50
        }
        QExtQuickRoundedShap {
            width: 100
            height: 80
            color: "#409EFF"
            bottomRightRadius: 50
        }
    }

    Row {
        spacing: 10

        QExtQuickRoundedShap {
            width: 100
            height: 80
            color: "#409EFF"
            topLeftRadius: 80
        }
        QExtQuickRoundedShap {
            width: 100
            height: 80
            color: "#409EFF"
            topRightRadius: 80
        }
        QExtQuickRoundedShap {
            width: 100
            height: 80
            color: "#409EFF"
            bottomLeftRadius: 80
        }
        QExtQuickRoundedShap {
            width: 100
            height: 80
            color: "#409EFF"
            bottomRightRadius: 80
        }
    }

    Row {
        spacing: 10

        QExtQuickRoundedShap {
            width: 100
            height: 80
            color: "#409EFF"
            topLeftRadius: 40
            topRightRadius: 40
            border.width: 5
            border.color: "yellow"
        }
        QExtQuickRoundedShap {
            width: 100
            height: 80
            color: "#409EFF"
            topLeftRadius: 40
            bottomRightRadius: 40

        }
        QExtQuickRoundedShap {
            width: 100
            height: 80
            color: "#409EFF"
            topRightRadius: 60
            bottomLeftRadius: 25
            border.width: 5
            border.color: "black"
        }
        QExtQuickRoundedShap {
            width: 100
            height: 80
            color: "#409EFF"
            bottomLeftRadius: 5
            bottomRightRadius: 50
            border.width: 5
            border.color: "red"
        }
    }

}
