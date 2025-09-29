import QtQuick 2.6

import QExtQml 1.4
import QExtQml.Theme 1.4
import QExtQuick.Controls 1.4

QExtQuickButton {
    id: mControl
    theme.className: "QExtQuickIconButton"

    property int spacing: 5
    property alias icon: mIconInfo
    property Component iconComponent

    contentComponent: {
        if(mIconInfo.position === QExtQuickControls.PositionCenter) {
            return contentOnlyiconItem;
        } else if(mIconInfo.position === QExtQuickControls.PositionLeft ||
                  mIconLoader.position === QExtQuickControls.PositionRight) {
            return mContentRowLayoutComponent;
        } else if(mIconInfo.position === QExtQuickControls.PositionTop) {
            return mContentColumnLayoutComponent;
        }
        return null;
    }

    iconComponent: {
        if(!mIconInfo.source) {
            return null;
        } else if(mIconInfo.source.indexOf(".svg") != -1) {
            return mSvgIconComponent;
        }
        return mFontIconComponent;
    }

    QExtQmlIconInfo {
        id: mIconInfo
        width: 18
        height: 18
        color:"#2D2D2D"
        position: QExtQuickControls.PositionLeft
    }

    Component {
        id: contentOnlyiconItem;
        Loader {
            scale:  mControl.theme.scale;
            sourceComponent: iconComponent;
        }
    }

    Component{
        id: mContentRowLayoutComponent
        Row {
            id: row
            spacing: mControl.spacing
            scale: mControl.theme.scale
            layoutDirection: mControl.icon.position === QExtQuickControls.PositionLeft ? Qt.LeftToRight
                                                                                       : Qt.RightToLeft

            Loader {
                id: mIconLoader
                enabled: false
                visible: iconComponent
                sourceComponent: iconComponent
                anchors.verticalCenter: row.verticalCenter
            }

            QExtQuickText {
                id: mText
                enabled: false
                theme.parent: mControl.theme
                theme.childName: "text"

                text: mControl.content.text
                font: mControl.content.font
                color: mControl.content.color

                anchors.verticalCenter: row.verticalCenter
            }
        }
    }

    Component {
        id: mContentColumnLayoutComponent
        Column {
            spacing: mControl.spacing
            scale: mControl.theme.scale

            Loader {
                enabled: false;
                sourceComponent: iconComponent
                anchors.horizontalCenter: parent.horizontalCenter
            }

            QExtQuickText {
                id: mText
                enabled: false
                theme.parent: mControl.theme
                theme.childName: "text"

                text: mControl.content.text
                font: mControl.content.font
                color: mControl.content.color

                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    Component{
        id: mFontIconComponent
        QExtQuickFontIcon {
            enabled: false
            theme.childName: "icon"
            theme.parent: mControl.theme

            color: mIconInfo.color
            width: mIconInfo.width
            height: mIconInfo.height
            source: mIconInfo.source
        }
    }

    Component{
        id: mSvgIconComponent
        QExtQuickSvgIcon {
            enabled: false;
            theme.parent: mControl.theme
            theme.childName: "icon"

            color: mIconInfo.color
            width: mIconInfo.width
            height: mIconInfo.height
            source: mIconInfo.source
        }
    }
}
