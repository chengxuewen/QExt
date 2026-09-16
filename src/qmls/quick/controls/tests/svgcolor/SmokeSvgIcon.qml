import QtQuick 2.15
import QtQuick.Window 2.15
import QExtQuick.Controls 1.4

Window {
    visible: true
    width: 100
    height: 100
    QExtQuickSvgIcon {
        id: icon
        anchors.centerIn: parent
        width: 24
        height: 24
        color: "red"
        source: "qrc:/QExtQuickControls/resources/image/info.svg"
        onStatusChanged: console.log("STATUS:" + status)
    }
    Timer {
        interval: 2500
        running: true
        onTriggered: {
            console.log("FINAL:" + icon.status)
            if (icon.status !== Image.Ready) {
                console.log("RESULT:FAIL")
                Qt.exit(2)
            }
            // 变色二次加载（验证换 URL 同步出图路径）
            icon.color = "blue"
            recolor.restart()
        }
    }
    Timer {
        id: recolor
        interval: 1500
        onTriggered: {
            console.log("RECOLORED:" + icon.status)
            console.log(icon.status === Image.Ready ? "RESULT:PASS" : "RESULT:FAIL")
            Qt.exit(icon.status === Image.Ready ? 0 : 3)
        }
    }
}
