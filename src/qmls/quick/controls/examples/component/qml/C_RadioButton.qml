import QtQuick 2.0

import QExtQuick.Controls 1.4

Column{
    spacing: 15;

    Row{
        id:layout
        spacing: 3
        QExtQuickRadioBoxGroup{
            parent: layout

            QExtQuickRadioBox{
                text: ""
                checked: true
            }

            QExtQuickRadioBox{
                text: "Guangzhou"
                checked: true
            }

            QExtQuickRadioBox{
                text: "Shanghai"
            }

            QExtQuickRadioBox{
                enabled: false;
                text: "Hong Kong"
            }

            // onCurrentItemChanged: result.text =  currentItem.text;
        }

        // Item{width: 18; height: 10;}

        // Text{
        //     id:result
        //     width: 40;
        //     anchors.verticalCenter: parent.verticalCenter;
        // }
    }

    Row{
        id:layoutborder
        spacing: 25
        anchors.horizontalCenter: parent.horizontalCenter
        QExtQuickRadioBoxGroup{
            parent: layoutborder

            QExtQuickRadioBox{
                id:tb
                text: "Primary"
                // iconPosition: TPosition.Reght
                background.visible: true
                border.width: 1;
                theme.groupName: "rboxa"

                states: [
                    State {
                        name: "checked"
                        PropertyChanges {
                            target: tb.border
                            color:"#409EFF"
                        }
                    }
                ]
            }

            QExtQuickRadioBox{
                id:tb2
                text: "Success"
                // iconPosition: TPosition.Reght
                background.visible: true
                border.width: 1;
                background.color: "#F0F9EB"
                theme.groupName: "rboxb"
                states: [
                    State {
                        name: "checked"
                        PropertyChanges {
                            target: tb2.border
                            color:"#67C23A"
                        }
                    }
                ]
            }

            QExtQuickRadioBox{
                id:tb3
                text: "Warning"
                // iconPosition: TPosition.Reght
                background.visible: true
                border.width: 1;
                background.color: "#FDF6ED"
                theme.groupName: "rboxc"
                states: [
                    State {
                        name: "checked"
                        PropertyChanges {
                            target: tb3.border
                            color:"#E6A23C"
                        }
                    }
                ]
            }

            QExtQuickRadioBox{
                id:tb4
                text: "Danger"
                // iconPosition: TPosition.Reght
                background.visible: true
                border.width: 1;
                background.color: "#FEF0F0"
                theme.groupName: "rboxd"
                states: [
                    State {
                        name: "checked"
                        PropertyChanges {
                            target: tb4.border
                            color:"#F56C6C"
                        }
                    }
                ]
            }

            QExtQuickRadioBox{
                id:tb5
                text: "DangerseFGAERWSGRADSBGHAERG|"
                // iconPosition: TPosition.Reght
                background.visible: true
                border.width: 1;
                background.color: "#FEF0F0"
                theme.groupName: "rboxd"
                states: [
                    State {
                        name: "checked"
                        PropertyChanges {
                            target: tb5.border
                            color:"#F56C6C"
                        }
                    }
                ]
            }

            QExtQuickRadioBox{
                id:tb6
                width: implicitWidth
                text: "DangerseFGAERDSBGHAERG|"
                // iconPosition: TPosition.Reght
                background.visible: true
                border.width: 1;
                background.color: "#FEF0F0"
                theme.groupName: "rboxd"
                states: [
                    State {
                        name: "checked"
                        PropertyChanges {
                            target: tb6.border
                            color:"#F56C6C"
                        }
                    }
                ]
            }
        }
    }

}
