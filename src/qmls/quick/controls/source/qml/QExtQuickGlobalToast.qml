pragma Singleton
import QtQml 2.9
import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQml 1.2
import QExtQuick.Controls 1.2

QExtQuickToast {
    id: root

    function setTopLevelWindow(object) {
        while (null !== object.parent) {
            object = object.parent;
        }
        root.rootWindow = object;
    }
    // property alias rootWindow: qextRootWindow
}
