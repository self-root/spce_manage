import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../components"

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
            text: "Schedule"
            font.bold: true
            font.pointSize: 26
            color: "white"
        }

        RowLayout{
            id: rowLayout
            spacing: 16
            anchors.top: wText.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.topMargin: 10
            anchors.leftMargin: 16
            anchors.rightMargin: 16
            anchors.bottomMargin: 16
            ListView{
                id: scheduleList
                Layout.fillHeight: true
                Layout.fillWidth: true
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
                        source: "file:///" + flag_url
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

                    Rectangle{
                        id: rectIndicator
                        anchors.right: parent.right
                        anchors.rightMargin: 6
                        anchors.verticalCenter: parent.verticalCenter
                        width: 10
                        height: 180
                        radius: 4
                        color: "#bdfe50"
                        visible: index === scheduleList.currentIndex ? true : false
                    }


                    MouseArea{
                        id: mouseArea
                        anchors.fill: parent
                        onClicked: {
                            console.log("mousex: " + mouseX)
                            var i = scheduleList.indexAt(mouseX + parent.x, mouseY + parent.y)
                            console.log("Index: " + i)
                            scheduleList.currentIndex = i
                            console.log("Current index: " + scheduleList.currentIndex)
                            console.log("imo: " + imo)
                            controller.shipDetailModel.getShipDetail(imo)
                            schedDateTxt.text = schedule_type + ": " + datetime
                        }
                    }
                }
            }

            Rectangle{
                id: shipDetailRect
                Layout.alignment: Qt.AlignTop
                Layout.preferredHeight:300
                Layout.preferredWidth: 400
                radius: 4
                gradient: Gradient{
                    GradientStop {
                        position: 0.0
                        color: "#124da8"
                    }

                    GradientStop {
                        position: 1.0

                        color: "#040d1c"
                    }
                }

                Text {
                    id: shipNameTxt
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.topMargin: 10
                    text: controller.shipDetailModel.name
                    font.bold: true
                    font.pointSize: 14
                    color: "#bdfe50"
                    //horizontalAlignment: Text.AlignHCenter
                }

                Text {
                    id: shipimoTxt
                    anchors.top: shipNameTxt.bottom
                    anchors.left: parent.left
                    anchors.leftMargin: 6
                    anchors.topMargin: 10
                    text: "IMO: " + controller.shipDetailModel.imo
                    color: "white"
                    font.pointSize: 11

                }

                Text {
                    id: shipclallignTxt
                    anchors.top: shipimoTxt.bottom
                    anchors.left: parent.left
                    anchors.leftMargin: 6
                    anchors.topMargin: 10
                    text: "Distinctive number or letters:  " + controller.shipDetailModel.callsign
                    color: "white"
                    font.pointSize: 11

                }

                Text {
                    id: shipFlagTxt
                    anchors.top: shipclallignTxt.bottom
                    anchors.left: parent.left
                    anchors.leftMargin: 6
                    anchors.topMargin: 10
                    text: "Flag State: " + controller.shipDetailModel.flag
                    color: "white"
                    font.pointSize: 11

                }

                Text {
                    id: shipgtTxt
                    anchors.top: shipFlagTxt.bottom
                    anchors.left: parent.left
                    anchors.leftMargin: 6
                    anchors.topMargin: 10
                    text: "Gross tonnage: " + controller.shipDetailModel.grossTonnage
                    color: "white"
                    font.pointSize: 11

                }

                Text {
                    id: shitypetTxt
                    anchors.top: shipgtTxt.bottom
                    anchors.left: parent.left
                    anchors.leftMargin: 6
                    anchors.topMargin: 10
                    text: "Type of ship: " + controller.shipDetailModel.shipType
                    color: "white"
                    font.pointSize: 11

                }

                Text {
                    id: schedDateTxt
                    anchors.top: shitypetTxt.bottom
                    anchors.left: parent.left
                    anchors.leftMargin: 6
                    anchors.topMargin: 10
                    color: "white"
                    font.pointSize: 11

                }

                Image {
                    id: flagImg
                    anchors.top: shipNameTxt.bottom
                    anchors.right: parent.right
                    anchors.topMargin: 10
                    anchors.rightMargin: 6
                    width: 100
                    fillMode: Image.PreserveAspectFit
                    source: "file:///" + controller.shipDetailModel.flagUrl
                }

                RotatingIconBtn{
                    id: aButton
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 16
                    buttonW: 240
                    buttonH: 40
                    buttonColor: "#bdfe50"
                    textColor: "#040d1c"
                    text: "Prepare Ship Documents"
                    icon: "qrc:/images/images/ship-steering.png"
                    onClicked: {
                        console.log("aButton clicked")
                    }
                }

            }
        }




    }
}
