import QtQuick 2.6

import QExtQml 1.4

QExtQmlObject {
    id: mControl

    property Item parent;
    readonly property alias currentIndex: mPrivate.currentIndex
    readonly property Item currentItem: {
        if(currentIndex  !== -1){
            return children[currentIndex];
        }
        return null;
    }

    readonly property QExtQmlObject _: QExtQmlObject {
        id: mPrivate;
        property int currentIndex: -1;
    }

    default property alias children: mControl.childs
    property list<QExtQuickRadioBox> childs

    onChildrenChanged: {
        var i = children.length - 1;
        var trb = children[i];
        trb.parent = parent;
        trb.groupIndex = i;

        if(mPrivate.currentIndex !== -1) {
            trb.checked = false;
        } else if(trb.checked) {
            mPrivate.currentIndex = i;
        }

        trb.checkedChanged.connect(function() {
            if(trb.checked) {
                mPrivate.currentIndex = trb.groupIndex;
            }
        });
    }

    onCurrentIndexChanged: {
        for(var child in children) {
            var cobj = children[child];
            if(cobj.groupIndex !== mPrivate.currentIndex) {
                cobj.checked = false;
            }
        }
    }

    Component.onCompleted: {
        if(mPrivate.currentIndex == -1) {
            var cobj = children[0];
            if(cobj) {
                cobj.checked = true;
            }
        }
    }
}
