import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
Page{
    id: operationPage
    Material.theme: Material.Dark
    Material.accent: "white"
    Material.primary: "white"

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
            text: "Ship Document"
            font.bold: true
            font.pointSize: 26
            color: "white"
        }

        RowLayout{
            anchors.top: wText.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 6
            ColumnLayout{
                Rectangle{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color: "transparent"
                    ScrollView{
                        width: parent.width
                        height: parent.height
                        Column{
                            spacing: 10
                            width: parent.width
                            Text {
                                text: "Ship particular"
                                color: "white"
                                font.bold: true
                                font.pointSize: 14
                            }

                            Rectangle{
                                width: 300
                                height: 3
                                color: "#bdfe50"
                            }

                            Row{
                                spacing: 20
                                TextField{
                                    id: imoInput
                                    width: 300
                                    placeholderText: "IMO number"
                                    color: "white"
                                }

                                TextField{
                                    id: shipNameInput
                                    width: 300
                                    placeholderText: "Ship name"
                                    color: "white"
                                }
                            }

                            Row{
                                spacing: 20
                                TextField{
                                    id: callSignInput
                                    width: 300
                                    placeholderText: "Callsign"
                                    color: "white"
                                }

                                TextField{
                                    id: countryInput
                                    width: 300
                                    placeholderText: "Flag State"
                                    color: "white"
                                }
                            }
                            TextField{
                                id: grossTonnageInput
                                width: 300
                                placeholderText: "Tonnage"
                                color: "white"
                            }
                        }
                    }
                }
                Rectangle{
                    Layout.fillWidth: true
                    Layout.preferredHeight: 40
                    color: "white"
                }
            }

            Rectangle{
                Layout.preferredWidth: 400
                Layout.fillHeight: true
                color: "yellow"
            }
        }
    }
}
