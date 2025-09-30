import QtQuick 2.6

import QExtQml 1.4
import QExtQuick.Controls 1.4

MouseArea {
    id: mControl
    state: QExtQml.stateToString(QExtQml.StateNormal)

    property bool hovered: false
    property bool pressed: false
    property bool checked: false
    property bool checkable: false
    property bool toggled: pressed || checked
    property int stateValue: QExtQml.StateNormal

    onEntered: {
        if(hoverEnabled) {
            hovered = true;
        }
    }
    onExited: {
        hovered = false;
    }
    onPressed: {
        pressed = true;
        if (checkable) {
            checked = !checked;
        }
    }
    onReleased: {
        pressed = false;
    }

    onHoveredChanged: {
        updateState();
    }
    onPressedChanged: {
        updateState();
    }
    onCheckedChanged: {
        updateState();
    }
    onCheckableChanged: {
        updateState();
    }

    function updateState() {
        if (checkable && checked) {
            stateValue = QExtQml.StateChecked;
        } else if (pressed) {
            stateValue = QExtQml.StatePressed;
        } else if (hovered) {
            stateValue = QExtQml.StateHovered;
        } else {
            stateValue = QExtQml.StateNormal;
        }
        state = QExtQml.stateToString(stateValue);
    }
}
