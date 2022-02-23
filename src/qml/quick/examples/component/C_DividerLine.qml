import QtQuick 2.12
import QEXTQmlQuick 1.0

Column{
    spacing: 15

    QEXTQmlQuickDividerLine{
        width: 350
        height: 1
    }

    Row{
        spacing: 10
        Repeater{
            model: 30

            delegate: QEXTQmlQuickDividerLine{
                width: Math.random() * 2 + 1
                height: 40
                color: Qt.rgba(Math.random(),Math.random(),Math.random(),1)
            }
        }
    }


    QEXTQmlQuickDividerLine{
        width: 350
        height: 1
    }

}
