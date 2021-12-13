import QtQuick 2.0
import QtTest 1.0

import QEXTQmlVLC 1.0

Rectangle {
    width: 640
    height: 480
    color: "black"

    QEXTQmlVLCPlayer {
        id: player
        logLevel: QEXTVLC.LogLevel_Debug
        url: "rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mov"
    }
    QEXTQmlVLCVideoOutput {
        id: video
        source: player
        anchors.fill: parent
    }

    TestCase {
        id: tc1
        name: "FillMode"
        when: windowShown

        function test_fillMode()
        {
            wait(3000)
            video.fillMode = QEXTVLC.Fill_PreserveAspectCrop
            wait(500)
            video.fillMode = QEXTVLC.Fill_Stretch
            wait(500)
            video.fillMode = QEXTVLC.Fill_PreserveAspectFit
            wait(2000)
        }
    }

    TestCase {
        id: tc2
        name: "AspectRatio"
        when: tc1.completed

        function test_aspectRatio() {
            video.aspectRatio = QEXTVLC.Ratio_1_1
            wait(500)
            video.aspectRatio = QEXTVLC.Ratio_5_4
            wait(500)
            video.aspectRatio = QEXTVLC.Ratio_4_3
            wait(500)
            video.aspectRatio = QEXTVLC.Ratio_16_10
            wait(500)
            video.aspectRatio = QEXTVLC.Ratio_5_3
            wait(500)
            video.aspectRatio = QEXTVLC.Ratio_16_9
            wait(500)
            video.aspectRatio = QEXTVLC.Ratio_185_100
            wait(500)
            video.aspectRatio = QEXTVLC.Ratio_221_100
            wait(500)
            video.aspectRatio = QEXTVLC.Ratio_235_100
            wait(500)
            video.aspectRatio = QEXTVLC.Ratio_239_100
            wait(500)
            video.aspectRatio = QEXTVLC.Ratio_Original
            wait(2000)
        }
    }

    TestCase {
        id: tc3
        name: "CropRatio"
        when: tc2.completed

        function test_cropRatio() {
            video.cropRatio = QEXTVLC.Ratio_1_1
            wait(500)
            video.cropRatio = QEXTVLC.Ratio_5_4
            wait(500)
            video.cropRatio = QEXTVLC.Ratio_4_3
            wait(500)
            video.cropRatio = QEXTVLC.Ratio_16_10
            wait(500)
            video.cropRatio = QEXTVLC.Ratio_5_3
            wait(500)
            video.cropRatio = QEXTVLC.Ratio_16_9
            wait(500)
            video.cropRatio = QEXTVLC.Ratio_185_100
            wait(500)
            video.cropRatio = QEXTVLC.Ratio_221_100
            wait(500)
            video.cropRatio = QEXTVLC.Ratio_235_100
            wait(500)
            video.cropRatio = QEXTVLC.Ratio_239_100
            wait(500)
            video.cropRatio = QEXTVLC.Ratio_Original
            wait(2000)
        }
    }
}
