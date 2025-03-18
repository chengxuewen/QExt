import QtQuick 2.12
import QtQml 2.12

Rectangle {
    id: qextRoundRectangle
    layer.enabled: true
    property int radiusCorners: Qt.AlignLeft | Qt.AlignRight | Qt.AlignTop | Qt.AlignBottom /* Default: */
    /*
                            Qt.AlignLeft |      Qt.AlignLeft |      Qt.AlignRight |     Qt.AlignLeft |      Qt.AlignLeft |
                            Qt.AlignRight |     Qt.AlignTop |       Qt.AlignTop |       Qt.AlignRight |     Qt.AlignRight |
              None:0        Qt.AlignTop |       Qt.AlignBottom      Qt.AlignBottom      Qt.AlignTop         Qt.AlignBottom
                            Qt.AlignBottom
        *****************     *************       ***************   ***************       *************     *****************
        *               *    *             *     *              *   *              *     *             *    *               *
        *               *   *               *   *               *   *               *   *               *   *               *
        *               *   *               *   *               *   *               *   *               *   *               *
        *               *   *               *   *               *   *               *   *               *   *               *
        *               *   *               *   *               *   *               *   *               *   *               *
        *               *   *               *   *               *   *               *   *               *   *               *
        *               *    *             *     *              *   *              *    *               *    *             *
        *****************     *************       ***************   ***************     *****************     *************
    */

    Repeater {
        model: [ {
                x: 0,
                y: 0,
                visible: internal.aligns(Qt.AlignLeft | Qt.AlignTop),
                radius: qextRoundRectangle.radius
            },
            {
                x: qextRoundRectangle.width - qextRoundRectangle.radius,
                y: 0,
                visible: internal.aligns(Qt.AlignRight | Qt.AlignTop),
                radius: qextRoundRectangle.radius
            },
            {
                x: 0,
                y: qextRoundRectangle.height - qextRoundRectangle.radius,
                visible: internal.aligns(Qt.AlignLeft | Qt.AlignBottom),
                radius: qextRoundRectangle.radius
            },
            {
                x: qextRoundRectangle.width - qextRoundRectangle.radius,
                y: qextRoundRectangle.height - qextRoundRectangle.radius,
                visible: internal.aligns(Qt.AlignRight | Qt.AlignBottom),
                radius: qextRoundRectangle.radius
            } ]

        Rectangle {
            x: modelData.x; y: modelData.y
            width: modelData.radius; height: width
            visible: !modelData.visible
            color: parent.color
        }
    }

    QtObject {
        id: internal

        function aligns(direction) {
            return (qextRoundRectangle.radiusCorners & direction) === direction
        }
    }
}
