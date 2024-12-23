import QtQuick 2.12
import QExtQuick.Controls 1.2

Column{
    spacing: 15

    Row{
        id:layout
        spacing: 20

        QExtQuickTriangle {
            width: 60
            height: 60
        }
        QExtQuickTriangle {
            width: 60
            height: 80
            color: "steelblue"
        }
        QExtQuickTriangle {
            width: 60
            height: 80
            color: "steelblue"
            borderColor: "red"
            borderWidth: 1
        }
        QExtQuickTriangle {
            width: 60
            height: 80
            color: "steelblue"
            borderColor: "black"
            borderWidth: 3
        }
    }

}
