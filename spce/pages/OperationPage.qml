import QtQuick
import QtQuick.Controls

Page{
    id: operationPage

    Rectangle{
        anchors.fill: parent
        gradient: Gradient{
            GradientStop {
                position: 0.0
                color: "#040d1c"
            }

            GradientStop {
                position: 1.0
                color: "#124da8"
            }
        }

        Text {
            id: txt
            anchors.centerIn: parent
            text: qsTr("Operation page")
        }
    }
}
