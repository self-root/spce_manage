import QtQuick
import QtQuick.Controls

Page {
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
            id: wText
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 12
            anchors.leftMargin: 8
            text: qsTr("Schedule")
            font.bold: true
            font.pointSize: 26
            color: "white"
        }

        ListView{
            id: scheduleList
            anchors.top: wText.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.topMargin: 10
            anchors.leftMargin: 16
            anchors.rightMargin: 16
            anchors.bottomMargin: 16
            clip: true
            spacing: 16
            ScrollBar.vertical: ScrollBar{}

            model: controller.scheduleListModel

            delegate: Rectangle{
                width: scheduleList.width
                height: 200
                //color: Qt.lighter("#0c203c")
                color: "#0c203c"
                radius: 4

                Image {
                    id: flag
                    width: 80
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.topMargin: 8
                    anchors.leftMargin: 8
                    fillMode: Image.PreserveAspectFit
                    source: flag_url
                    cache: true
                }

                Text {
                    id: shipName
                    text: name
                    anchors.top: parent.top
                    anchors.left: flag.right
                    anchors.topMargin: 8
                    anchors.leftMargin: 8
                    font.pointSize: 12
                    font.bold: true
                    color: "#bdfe50"
                }

                Text {
                    id: imoTxt
                    text: "IMO: " + imo
                    anchors.top: shipName.bottom
                    anchors.left: flag.right
                    anchors.topMargin: 8
                    anchors.leftMargin: 8
                    font.pointSize: 10
                    font.bold: true
                    color: "white"
                }

                Text {
                    id: dateTxt
                    text: schedule_type + ": " + datetime
                    anchors.top: imoTxt.bottom
                    anchors.left: flag.right
                    anchors.topMargin: 8
                    anchors.leftMargin: 8
                    font.pointSize: 10
                    font.bold: true
                    color: "white"
                }
            }
        }
    }
}
