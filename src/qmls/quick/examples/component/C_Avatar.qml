import QtQuick 2.12
import QEXTQmlQuick 1.0

Column{
    spacing: 15

    Row{
        id:layout
        spacing: 20

        QEXTQmlQuickAvatar{
            width: 60
            height: 60
            source: "qrc:/images/0.jpg"
            radius: 5
        }

        QEXTQmlQuickAvatar{
            width: 60
            height: 60
            source: "qrc:/images/1.jpg"
            radius: 20
        }

        QEXTQmlQuickAvatar{
            width: 60
            height: 60
            source: "qrc:/images/2.jpg"
            radius: height / 2
            borderWidth: 1
            borderColor: "#F56C6C"
        }

        QEXTQmlQuickAvatar{
            width: 60
            height: 60
            source: "qrc:/images/3.jpg"
            radius: 20
        }

        QEXTQmlQuickAvatar{
            width: 60
            height: 60
            source: "qrc:/images/4.jpg"
            radius: 5
        }

    }

}
