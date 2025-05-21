import QtQuick 2.12
import QExtQuick.Controls 1.3

Column{
    spacing: 15

    QExtQuickDividerLine{
        width: 350
        height: 1
    }

    Row{
        spacing: 10
        Repeater{
            model: 30

            delegate: QExtQuickDividerLine{
                width: Math.random() * 2 + 1
                height: 40
                color: Qt.rgba(Math.random(),Math.random(),Math.random(),1)
            }
        }
    }


    QExtQuickDividerLine{
        width: 350
        height: 1
    }

}
