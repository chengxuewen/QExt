pragma Singleton
import QtQml 2.9
import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQml 1.4

QExtQuickToast {
    id: mControl
    rootWindow: QExtQml.rootWindow

    function setTopLevelWindow(object) {
        while (undefined !== object.parent && null !== object.parent) {
            object = object.parent;
        }
        mControl.rootWindow = object;
    }
}
