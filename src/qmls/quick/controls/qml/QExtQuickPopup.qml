import QtQuick 2.6
import QtQuick.Controls 2.0

import QExtQml 1.4
import QExtQml.Theme 1.4
import QExtQuick.Controls 1.4

QtObject {
    id: mControl

    signal opened()
    signal closeed()
    signal hided(var autoclose)
    signal triggeredBackground()

    property Component backgroundComponent
    property alias internal: mPrivate

    // default property alias children: mPrivate.children

    function open() {
        mPrivate.create();
        opened();
    }

    function hide(autoclose) {
        mPrivate.hide(autoclose);
        hided(autoclose);
    }

    function close() {
        mPrivate.close();
        closeed();
    }

    backgroundComponent: Rectangle {
        color: "BLACK"
        opacity: 0
        z:-1
        Behavior on opacity {
            NumberAnimation {
                duration: 200
            }
        }
    }

    QExtQmlObject {
        id: mPrivate
        property var layout;
        property list<QtObject> childs
        function create(){
            if (!layout){
                layout = mLayoutComponent.createObject(QExtQml.rootWindow);
                layout.z = 99999;
                layout.show();
            }

            for (var i in children) {
                if ((typeof children[i].parent) !== "undefined" && (typeof children[i].className) === "undefined"){
                    children[i].parent = layout;
                }
            }
        }

        function hide(autoclose) {
            layout.hide(autoclose);
        }

        function close() {
            if (layout) {
                layout.destroy();
            }
        }
    }

    Component {
        id: mLayoutComponent

        Item {
            id: mItem
            anchors.fill: parent

            function show() {
                if (mBackgroundLoader.item) {
                    mBackgroundLoader.item.opacity = 0.5
                }
            }

            function hide(autoclose) {
                if (autoclose) {
                    mItem.destroy(300);
                }
                if (mBackgroundLoader.item) {
                    mBackgroundLoader.item.opacity = 0;
                }
            }

            Loader {
                id: mBackgroundLoader
                anchors.fill: parent
                sourceComponent: backgroundComponent
            }

            MouseArea {
                anchors.fill: parent
                onClicked: triggeredBackground()
                onWheel: {}
            }
        }
    }
}
