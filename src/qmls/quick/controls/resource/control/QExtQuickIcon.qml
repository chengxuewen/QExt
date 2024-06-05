import QtQuick 2.12
import QtQml 2.12

Item {
    id: qextIcon

    property string source
    property color color

    Loader {
        anchors.fill: parent
        sourceComponent: {
            if (qextIcon.source.toLowerCase().indexOf(".svg") !== -1) {
                return mSvgComponent
            }
            return mAwesomeIconComponent
        }
    }

    Component {
        id: mAwesomeIconComponent
        QExtQuickAwesomeIcon {
            enabled: false
            scale: qextIcon.scale
            source: qextIcon.source
            color: qextIcon.color
        }
    }

    Component {
        id: mSvgComponent
        QExtQuickSVGIcon {
            enabled: false
            scale: qextIcon.scale
            source: qextIcon.source
            color: qextIcon.color
        }
    }
}
