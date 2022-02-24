import QtQuick 2.12
import QtQuick.Controls 1.2

import QEXTQmlQuick 1.0

ApplicationWindow {
    visible: true
    title: "widget proxy"
    width: 580
    height: 480

    QEXTCalendar
    {
        anchors.fill: parent
        visible: true
        MouseArea
        {
            anchors.fill: parent
//            hoverEnabled: true
            onPressed:
            {
                mouse.accepted = false;
            }
        }
    }

}
