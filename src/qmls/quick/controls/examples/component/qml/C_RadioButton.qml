import QtQuick 2.0

import QExtQml 1.4
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
                color: "red"
            }

            QExtQuickRadioBox{
                text: "Shanghai"
            }

            QExtQuickRadioBox{
                enabled: false
                text: "Hong Kong"
            }
            onCurrentItemChanged: {
                console.warn("currentItem.text:" + currentItem.text)
            }
        }
    }

    Row{
        id:layoutborder
        spacing: 25
        QExtQuickRadioBoxGroup{
            parent: layoutborder

            QExtQuickRadioBox{
                id:tb
                text: "Primary"
                iconPosition: QExtQml.PositionRight
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
                iconPosition: QExtQml.PositionRight
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
                iconPosition: QExtQml.PositionRight
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
                iconPosition: QExtQml.PositionRight
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

        }
    }

    Row{
        id:layoutWidth
        spacing: 25
        QExtQuickRadioBoxGroup{
            parent: layoutWidth
            QExtQuickRadioBox{
                width: implicitWidth
                text: "Primary"
                background.visible: true
                border.width: 1;
            }

            QExtQuickRadioBox{
                width: implicitWidth
                text: "Primary123456789"
                background.visible: true
                border.width: 1;
            }

            QExtQuickRadioBox{
                width: 100
                text: "Primaryabsc"
                background.visible: true
                border.width: 1;
            }

            QExtQuickRadioBox{
                width: implicitWidth
                text: "Primary6789"
                background.visible: true
                border.width: 1;
            }
        }
    }

}
