import QtQuick 2.12
import QtQml 2.12

import QEXTQuick 1.0

Item {
    id: qextAwesomeIcon
    width: 16
    height: 16

    property color color
    property string source

    Text {
        id: mContentText
        anchors.fill: parent
        enabled: false
        color: qextAwesomeIcon.color
        font.family: "fontawesome"
        font.pixelSize: Math.max(qextAwesomeIcon.width, qextAwesomeIcon.height)
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    QtObject {
        id: mWrapper
        property alias source: qextAwesomeIcon.source
        onSourceChanged: {
            if (source.indexOf("FA") === 0) {
                mContentText.text = QEXTQuickFontAwesome.awesomeFromKey(source)
            } else if (source.charAt(0) !== "\\") {
                mContentText.text = QEXTQuickFontAwesome.awesomeFromValue(source)
            } else {
                mContentText.text = source
            }
        }
    }
}
