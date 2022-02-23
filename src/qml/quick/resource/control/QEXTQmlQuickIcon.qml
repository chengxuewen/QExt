import QtQuick 2.9
import QtQml 2.9

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
        QEXTQmlQuickAwesomeIcon {
            enabled: false
            scale: qextIcon.scale
            source: qextIcon.source
            color: qextIcon.color
        }
    }

    Component {
        id: mSvgComponent
        QEXTQmlQuickSVGIcon {
            enabled: false
            scale: qextIcon.scale
            source: qextIcon.source
            color: qextIcon.color
        }
    }
}
