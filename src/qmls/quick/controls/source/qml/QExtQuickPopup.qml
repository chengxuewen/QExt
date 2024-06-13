import QtQml 2.9
import QtQuick 2.9
import QtQuick.Controls 2.9

import QExtQml 1.2
import QExtQuick.Controls 1.2

//带有遮挡的图层
//    注意：他会覆盖整个屏幕

//    QExtQuickPopup{
//        id:popup

//        Rectangle{
//            width: 100;
//            height: 100;
//            anchors.centerIn: parent;
//        }

//        onTriggeredBackground:{
//            close();
//        }
//    }
/*! TODO */
QExtQmlObject {
    id: root

    onParentChanged: {
        console.debug("parent=", parent)
    }

    signal closeed();

    signal opened();

    signal hided(var autoclose);

    signal triggeredBackground();

    property Component backgroundComponent;
    property var rootWindow: function() {
        while (undefined !== root.parent && null !== root.parent) {
            object = object.parent;
        }
        return object;
    }

    property alias privatec: _private;

    default property alias childitem: _private.childs;

    function open(){
        _private.create();
        opened();
    }

    function hide(autoclose){
        _private.hide(autoclose);
        hided(autoclose);
    }

    function close(){
        _private.close();
        closeed();
    }

    backgroundComponent: Rectangle{
        color: "BLACK"; z:-1;
        opacity: 0
        Behavior on opacity {
            NumberAnimation {
                duration: 200;
            }
        }
    }

    QExtQmlObject {
        id:_private;

        property list<QtObject> childs;
        property var layout;
        function create() {
            if(!layout) {
                layout = layoutComponent.createObject(root.rootWindow);
                layout.z = 99999;
                layout.show();
            }

            for(var i in childs) {
                if((typeof childs[i].parent) !== "undefined" && (typeof childs[i].className) === "undefined") {
                    childs[i].parent = layout;
                }
            }
        }

        function hide(autoclose){
            layout.hide(autoclose);
        }

        function close(){
            if(layout) layout.destroy();
        }
    }

    Component{
        id:layoutComponent;

        Item{
            id:item
            anchors.fill: parent;

            function show(){
                if(bgloader.item)
                    bgloader.item.opacity = 0.5
            }

            function hide(autoclose){
                if(autoclose) item.destroy(300);
                if(bgloader.item)
                    bgloader.item.opacity = 0;
            }

            //black bg
            Loader{
                id:bgloader;
                anchors.fill: parent;
                sourceComponent: backgroundComponent;
            }

            MouseArea{
                anchors.fill: parent;
                onClicked: triggeredBackground();
                onWheel: {}
            }

            //push other item
        }
    }
}
