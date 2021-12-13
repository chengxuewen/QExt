import QtQuick.Window 2.0
import QtQuick 2.0

import QEXTQmlVLC 1.0

Window {
    id: window
    visible: true
    minimumWidth: 360
    height: 480
    width: 640
    color: "black"

    QEXTQmlVLCPlayer {
        id: player
        logLevel: QEXTVLC.LogLevel_Warning
//        url: "rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mov"
        url: "rtsp://admin:12345@192.168.5.50:8554/0"
    }
    QEXTQmlVLCVideoOutput {
        id: video
        source: player
        anchors.fill: parent
    }
}
