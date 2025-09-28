import QtQuick 2.6

import QExtQuick.Controls 1.4

MouseArea {
    id: mControl
    state: {
        return QExtQuickControls.buttonStateToString(checkable && checked ? QExtQuickControls.ButtonStateChecked :
                                                                            QExtQuickControls.ButtonStateNormal);
    }

    property bool hovered: false
    property bool pressed: false
    property bool checked: false
    property bool checkable: false
    property bool toggled: pressed || checked
    property int stateValue: QExtQuickControls.ButtonStateNormal

    onClicked: {
        if (checkable) {
            checked = !checked;
        }
        updateState();
    }
    onEntered: {
        if(hoverEnabled) {
            hovered = true;
        }
        updateState();
    }
    onExited: {
        hovered = false;
        updateState();
    }
    onPressed: {
        pressed = true;
        updateState();
    }
    onReleased: {
        pressed = false;
        updateState();
    }

    function updateState() {
        if (checkable && checked) {
            stateValue = QExtQuickControls.ButtonStateChecked;
        } else if (pressed) {
            stateValue = QExtQuickControls.ButtonStatePressed;
        } else if (hovered) {
            stateValue = QExtQuickControls.ButtonStateHovered;
        } else {
            stateValue = QExtQuickControls.ButtonStateNormal;
        }
        state = QExtQuickControls.buttonStateToString(stateValue);
    }
}
