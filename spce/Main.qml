import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects


ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("SPCE Manage")

    RowLayout{
        anchors.fill: parent
        spacing: 0
        Rectangle{
            id: sideMenu
            Layout.fillHeight: true
            Layout.preferredWidth: 250


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

                }
            }
        }

        Rectangle{
            color: "white"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        DropShadow{
            anchors.fill: sideMenu
            horizontalOffset: 3
            radius: 6
            color: "grey"
            source: sideMenu
        }
    }
}
