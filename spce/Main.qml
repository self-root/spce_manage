import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import "components"


ApplicationWindow {
    width: 1560
    height: 880
    visible: true
    title: qsTr("SPCE Manage")

    Connections{
        target: uicontroller
        function onGoSchedulePage(){
            console.log("Scheduling...")
            stackView.replace("qrc:/pages/SchedulePage.qml")
            invoiceBtn.current = false
        }
        function onGoInvoicePage() {
            controller.invoiceTableModel.loadData()
            stackView.replace("qrc:/pages/Invoices.qml")
            scheduleBtn.current = false
        }
    }

    RowLayout{
        anchors.fill: parent
        spacing: 0
        Rectangle{
            id: sideMenu
            Layout.fillHeight: true
            Layout.preferredWidth: 200
            color: "white"

            ColumnLayout{
                anchors.fill: parent
                Rectangle{
                    Layout.fillWidth: true
                    Layout.preferredHeight: 200
                    Image {
                        id: spce_logo
                        anchors.centerIn: parent
                        width: 150
                        //height: 200
                        fillMode: Image.PreserveAspectFit
                        source: "qrc:/images/images/spce.png"
                    }
                }

                Rectangle{
                    Layout.fillHeight: true
                    Layout.fillWidth:  true
                    color: "white"
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
                        id: invoiceBtn
                        anchors.top: scheduleBtn.bottom
                        anchors.left: parent.left
                        anchors.topMargin: 4
                        anchors.leftMargin: 3
                        height: 40
                        width: parent.width - 10
                        iconNormal: "qrc:/images/images/business-model-normal.png"
                        iconHover: "qrc:/images/images/business-model-hover.png"
                        text: "Invoices"
                        onClicked: uicontroller.invoiceBtnClick()
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
            horizontalOffset: 0
            radius: 4
            samples: 9
            color: "#0c203c"
            source: sideMenu
        }
    }
}
