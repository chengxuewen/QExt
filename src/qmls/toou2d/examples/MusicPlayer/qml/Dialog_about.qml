import QtQuick 2.0
import Toou2D 1.0

TDialog {

    bodyComponent: TRectangle{
        width:  layout.width  + 80;
        height: layout.height + 80;
        radius: 5;

        Column{
            id:layout;
            spacing: 5;
            anchors.centerIn: parent;

            TLabel{
                text: "Toou2D"
                font.pixelSize: 30;
                anchors.horizontalCenter: parent.horizontalCenter;
            }

            TLabel{
                text: T2D.version();
                anchors.horizontalCenter: parent.horizontalCenter;
            }

            Item{
                width: 10; height: 20;
            }

            TLabel{
                text: "基于Qt(Quick)跨平台技术打造的2D框架"
                anchors.horizontalCenter: parent.horizontalCenter;
            }
        }
    }

}
