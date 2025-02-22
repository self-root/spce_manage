import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import "components"


ApplicationWindow {
    width: 1200
    height: 880
    visible: true
    title: qsTr("SPCE Manage")

    Connections{
        target: uicontroller
        function onGoSchedulePage(){
            console.log("Scheduling...")
            stackView.replace("qrc:/pages/SchedulePage.qml")
            operationBtn.current = false
        }

        function onGoOperationPage(){
            console.log("Operation...")
            stackView.replace("qrc:/pages/OperationPage.qml")
            scheduleBtn.current = false
        }
    }

    RowLayout{
        anchors.fill: parent
        spacing: 0
        Rectangle{
            id: sideMenu
            Layout.fillHeight: true
            Layout.preferredWidth: 250
            color: "#0c203c"

            ColumnLayout{
                anchors.fill: parent
                Rectangle{
                    Layout.fillWidth: true
                    Layout.preferredHeight: 250
                    Image {
                        id: spce_logo
                        anchors.centerIn: parent
                        width: 200
                        height: 200
                        fillMode: Image.PreserveAspectFit
                        source: "qrc:/images/images/spce.png"
                    }
                }

                Rectangle{
                    Layout.fillHeight: true
                    Layout.fillWidth:  true
                    color: "#0c203c"
                    MenuButton{
                        id: scheduleBtn
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.topMargin: 4
                        anchors.leftMargin: 3
                        height: 40
                        width: parent.width - 10
                        iconNormal: "qrc:/images/images/icons8-schedule-100-normal.png"
                        iconHover: "qrc:/images/images/icons8-schedule-100-hover.png"
                        text: "Schedule"
                        current: true
                        onClicked: uicontroller.scheduleMenuBtnClic()
                    }

                    MenuButton{
                        id: operationBtn
                        anchors.top: scheduleBtn.bottom
                        anchors.left: parent.left
                        anchors.topMargin: 4
                        anchors.leftMargin: 3
                        height: 40
                        width: parent.width - 10
                        iconNormal: "qrc:/images/images/business-model-normal.png"
                        iconHover: "qrc:/images/images/business-model-hover.png"
                        text: "Operation page"
                        onClicked: uicontroller.operationMenuBtnClic()
                    }
                }
            }
        }

        StackView{
            id: stackView
            Layout.fillHeight: true
            Layout.fillWidth: true
            initialItem: "qrc:/pages/SchedulePage.qml"
        }

        DropShadow{
            anchors.fill: sideMenu
            horizontalOffset: 3
            radius: 6
            color: "#0c203c"
            source: sideMenu
        }
    }
}
