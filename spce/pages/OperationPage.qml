import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import QtQuick.Controls.Material
import ".."
import "../components"

Page{
    id: operationPage
    //Material.theme: Material.Dark
    Material.accent: Style.primary
    Material.primary: Style.primary
    Rectangle{
        anchors.fill: parent
        color: "#f6f4fc"

        Text {
            id: wText
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 12
            anchors.leftMargin: 8
            text: "Ship Document"
            font.bold: true
            font.pointSize: 26
            color: Style.titleTextColor
        }

        RowLayout{
            anchors.top: wText.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 20
            ColumnLayout{
                Rectangle{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color: "transparent"
                    ScrollView{
                        width: parent.width
                        height: parent.height
                        Grid{
                            spacing: 40
                            columns: 2
                            Item {
                                width: 400
                                height: 500
                                DropShadow{
                                    source: a_rect
                                    anchors.fill: a_rect
                                    horizontalOffset: 0
                                    verticalOffset: 0
                                    radius: 6
                                    //samples: 9
                                    color: Style.boxShadow
                                }

                                Rectangle{
                                    id: a_rect
                                    anchors.fill: parent
                                    anchors.margins: 6
                                    color: "white"
                                    radius: 4

                                    ColumnLayout{
                                        id: l
                                        spacing: 10
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        anchors.top: parent.top
                                        anchors.bottom: parent.bottom
                                        anchors.topMargin: 10
                                        anchors.bottomMargin: 40
                                        FormSectionTitle{
                                            Layout.alignment: Qt.AlignHCenter
                                            text: "SHIP PARTICULARS"
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "IMO Number"
                                            text: controller.documentFormModel.imo
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Name of ship"
                                            text: controller.documentFormModel.shipName
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Gross tonnage"
                                            text: controller.documentFormModel.tonnage
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Distinctive number or letters"
                                            text: controller.documentFormModel.callSign
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Flag State"
                                            text: controller.documentFormModel.flagState
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Type of ship"
                                            text: controller.documentFormModel.shipType
                                        }
                                    }


                             }
                            }
                            Item {
                                width: 400
                                height: 500
                                DropShadow{
                                    source: a_rect2
                                    anchors.fill: a_rect2
                                    horizontalOffset: 0
                                    verticalOffset: 0
                                    radius: 6
                                    //samples: 9
                                    color: Style.boxShadow
                                }

                                Rectangle{
                                    id: a_rect2
                                    anchors.fill: parent
                                    anchors.margins: 6
                                    color: "white"
                                    radius: 4

                                    ColumnLayout{
                                        spacing: 10
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        anchors.top: parent.top
                                        anchors.bottom: parent.bottom
                                        anchors.topMargin: 10
                                        anchors.bottomMargin: 40
                                        FormSectionTitle{
                                            Layout.alignment: Qt.AlignHCenter
                                            text: "INSTALLATION D’ORIGINE"
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Dénomination"
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Adresse"
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Tél"
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Mail"
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Responsable"
                                        }

                                        TextButton{
                                            Layout.alignment: Qt.AlignHCenter
                                            Layout.margins: 10
                                            width: 100
                                            height: 40
                                            text: "Add"
                                        }
                                    }
                                }
                            }

                            Item {
                                width: 400
                                height: 580
                                DropShadow{
                                    source: a_rect3
                                    anchors.fill: a_rect3
                                    horizontalOffset: 0
                                    verticalOffset: 0
                                    radius: 6
                                    //samples: 9
                                    color: Style.boxShadow
                                }

                                Rectangle{
                                    id: a_rect3
                                    anchors.fill: parent
                                    anchors.margins: 6
                                    color: "white"
                                    radius: 4

                                    ColumnLayout{
                                        spacing: 10
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        anchors.top: parent.top
                                        anchors.bottom: parent.bottom
                                        anchors.topMargin: 10
                                        anchors.bottomMargin: 40
                                        FormSectionTitle{
                                            Layout.alignment: Qt.AlignHCenter
                                            text: "COLLECTEUR - TRANSPORTEUR"
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Nom"
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Adresse"
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Tél"
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Mail"
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Responsable"
                                        }



                                        TextButton{
                                            Layout.alignment: Qt.AlignHCenter
                                            Layout.margins: 10
                                            width: 100
                                            height: 40
                                            text: "Add"
                                        }
                                    }
                             }
                            }

                            Item {
                                width: 400
                                height: 580
                                DropShadow{
                                    source: a_rect4
                                    anchors.fill: a_rect4
                                    horizontalOffset: 0
                                    verticalOffset: 0
                                    radius: 6
                                    //samples: 9
                                    color: Style.boxShadow
                                }

                                Rectangle{
                                    id: a_rect4
                                    anchors.fill: parent
                                    anchors.margins: 6
                                    color: "white"
                                    radius: 4

                                    ColumnLayout{
                                        spacing: 10
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        anchors.top: parent.top
                                        anchors.bottom: parent.bottom
                                        anchors.topMargin: 10
                                        anchors.bottomMargin: 40
                                        FormSectionTitle{
                                            Layout.alignment: Qt.AlignHCenter
                                            text: "VALORISATEUR / ELIMINATEUR "
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Nom"
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Adresse"
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Tél"
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Mail"
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Responsable"
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Site de réception"
                                        }

                                        TextButton{
                                            Layout.alignment: Qt.AlignHCenter
                                            Layout.margins: 10
                                            width: 100
                                            height: 40
                                            text: "Add"
                                        }
                                    }
                                }
                            }

                            Item {
                                width: 400
                                height: 400
                                DropShadow{
                                    source: a_rect5
                                    anchors.fill: a_rect5
                                    horizontalOffset: 0
                                    verticalOffset: 0
                                    radius: 6
                                    //samples: 9
                                    color: Style.boxShadow
                                }

                                Rectangle{
                                    id: a_rect5
                                    anchors.fill: parent
                                    anchors.margins: 6
                                    color: "white"
                                    radius: 4

                                    ColumnLayout{
                                        spacing: 10
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        anchors.top: parent.top
                                        anchors.bottom: parent.bottom
                                        anchors.topMargin: 10
                                        anchors.bottomMargin: 40
                                        FormSectionTitle{
                                            Layout.alignment: Qt.AlignHCenter
                                            text: "RECEPTION FACILITY AND PORT PARTICULARS"
                                        }

                                        ComboBox{
                                            Layout.margins: 10
                                            width: 250
                                            editable: true

                                            model: ListModel{
                                                id: model
                                                ListElement {
                                                    text: "Mole B"
                                                }

                                                ListElement {
                                                    text: "Mole C"
                                                }
                                            }
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Reception facility provider"
                                        }

                                        Column{
                                            Layout.margins: 10
                                            spacing: 4
                                            Text {
                                                text: qsTr("Waste Discharge Date")
                                            }

                                            Row{
                                                spacing: 8
                                                LineEdit{
                                                    label: "From"
                                                    w: 80
                                                }

                                                LineEdit{
                                                    w: 80
                                                    label: "to"
                                                }
                                            }

                                        }

                                    }
                                }
                            }

                            Item {
                                width: 400
                                height: 400
                                DropShadow{
                                    source: a_rect6
                                    anchors.fill: a_rect6
                                    horizontalOffset: 0
                                    verticalOffset: 0
                                    radius: 6
                                    //samples: 9
                                    color: Style.boxShadow
                                }

                                Rectangle{
                                    id: a_rect6
                                    anchors.fill: parent
                                    anchors.margins: 6
                                    color: "white"
                                    radius: 4

                                    ColumnLayout{
                                        spacing: 10
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        anchors.top: parent.top
                                        anchors.bottom: parent.bottom
                                        anchors.topMargin: 10
                                        anchors.bottomMargin: 40
                                        FormSectionTitle{
                                            Layout.alignment: Qt.AlignHCenter
                                            text: "Invoice"
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Quantity"
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Amount"
                                        }

                                        LineEdit{
                                            Layout.margins: 10
                                            label: "Date"
                                        }

                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    Layout.fillWidth: true
                    Layout.preferredHeight: 40
                    color: "white"
                    radius: 4
                }
            }

            Rectangle{
                Layout.preferredWidth: 400
                Layout.fillHeight: true
                color: "white"
                radius: 4
            }
        }
    }


}
