import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import ".."
import "../components"

Page {
    id: page
    Rectangle{
        anchors.fill: parent
        /*gradient: Gradient{
            GradientStop {
                position: 0.0
                color: "#040d1c"
            }

            GradientStop {
                position: 1.0
                color: "#124da8"
            }
        }*/

        Rectangle{
            id: shade
            anchors.fill: parent
            opacity: 0.5
            visible: searchBar.focus
            enabled: visible
            z:7
            MouseArea{
                anchors.fill: parent
                onPressed: searchBar.focus = false
            }

            states: [
                State {
                    name: "visible"
                    when: shade.visible
                    PropertyChanges {
                        target: shade
                        color: Style.primary
                    }
                },
                State {
                    name: "hidden"
                    when: !shade.visible
                    PropertyChanges {
                        target: shade
                        color: "white"
                    }
                }
            ]

            transitions: [
                Transition {
                    from: "hidden"
                    to: "visible"

                    ColorAnimation {
                        target: shade
                        duration: 200
                    }
                },
                Transition {
                    from: "visible"
                    to: "hidden"

                    ColorAnimation {
                        target: shade
                        duration: 200
                    }
                }
            ]
        }

        Item {
            id: searchResultWrapper
            width: 300
            height: 400
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 4

            z: 8
            DropShadow{
                source: resultRect
                anchors.fill: resultRect
                horizontalOffset: 0
                verticalOffset: 0
                radius: 6
                color: Style.primary
            }

            Rectangle{
                id: resultRect
                //anchors.fill: parent
                width: searchResultWrapper.width
                visible: searchBar.activeFocus
                radius: 6
                color: "white"
                states: [
                    State {
                        when: resultRect.visible
                        name: "visible"
                        PropertyChanges {
                            target: resultRect
                            height: searchResultWrapper.height
                        }
                    },
                    State {
                        when: !resultRect.visible
                        name: "hidden"
                        PropertyChanges {
                            target: resultRect
                            height: 0
                        }
                    }
                ]

                transitions: [
                    Transition {
                        from: "hidden"
                        to: "visible"

                        NumberAnimation {
                            target: resultRect
                            property: "height"
                            duration: 200
                            easing.type: Easing.InOutQuad
                        }
                    },
                    Transition {
                        from: "visible"
                        to: "hidden"

                        NumberAnimation {
                            target: resultRect
                            property: "width"
                            duration: 200
                            easing.type: Easing.InOutQuad
                        }

                        NumberAnimation {
                            target: resultRect
                            property: "height"
                            duration: 200
                            easing.type: Easing.InOutQuad
                        }
                    }
                ]
                Image {
                    id: steeringImgSearching
                    anchors.centerIn: parent
                    width: 60
                    visible: controller.shipListModel.searching
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/images/images/ship-steering.png"

                    RotationAnimator{
                        target: steeringImgSearching
                        from: 0
                        to: 360
                        duration: 1200
                        loops: Animation.Infinite
                        running: steeringImgSearching.visible
                    }
                }
                Text {
                    text: qsTr("Searching...")
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: steeringImgSearching.bottom
                    anchors.topMargin: 4
                    color: "grey"
                    font.pointSize: 8
                    visible: steeringImgSearching.visible
                }
                ListView{
                    id: searchResultList
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.topMargin: 50
                    anchors.bottomMargin: 8
                    model: controller.shipListModel
                    clip: true
                    ScrollBar.vertical: ScrollBar{}
                    delegate: Item{
                        width: searchResultList.width
                        height: 60
                        DropShadow{
                            source: contentRect
                            anchors.fill: contentRect
                            horizontalOffset: 0
                            verticalOffset: 0
                            radius: 3
                        }

                        Rectangle{
                            id: contentRect
                            anchors.fill: parent
                            anchors.margins: 3
                            radius: 4
                            DropShadow{
                                source: flagResult
                                anchors.fill: flagResult
                                horizontalOffset: 0
                                verticalOffset: 0
                                radius: 3
                            }
                            Image {
                                id: flagResult
                                height: parent.height - 16
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.leftMargin: 8
                                source: flagUrl
                                fillMode: Image.PreserveAspectFit
                                onStatusChanged: {
                                    if (status == Image.Error)
                                    {
                                        source = "file:///" + controller.flagDir + "/" + flagUrl
                                    }
                                }
                            }

                            Text {
                                id: shipNameResult
                                anchors.top: parent.top
                                anchors.left: flagResult.right
                                anchors.topMargin: 8
                                anchors.leftMargin: 8
                                text: name
                                color: Style.primary
                                font.bold: true
                                font.pointSize: 9
                            }

                            Text {
                                id: shipTypeResult
                                anchors.top: shipNameResult.bottom
                                anchors.left: flagResult.right
                                anchors.topMargin: 8
                                anchors.leftMargin: 8
                                text: type
                                color: "grey"
                                font.pointSize: 8
                            }

                            MouseArea{
                                anchors.fill: parent
                                onReleased: {
                                    console.log("Ship: " + name)
                                    searchBar.focus = false
                                    controller.documentFormModel.getShip(imo)
                                }
                            }
                        }
                    }
                }
            }
        }

        TextField{
            id: searchBar
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 6
            placeholderText: "Ship Name"
            verticalAlignment: TextInput.AlignVCenter
            z: 9
            background: Rectangle{
                implicitHeight: 40
                implicitWidth: 200
                radius: 16
                border.color: searchBar.activeFocus? Style.primary : "white"
            }
            onAccepted: controller.shipListModel.searchShip(searchBar.text)
            onTextEdited: controller.shipListModel.shipsLike(searchBar.text)
        }




        color: "#f6f4fc"
        Text {
            id: wText
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 12
            anchors.leftMargin: 16
            text: "Schedule"
            font.bold: true
            font.pointSize: 22
            color: Style.titleTextColor
        }

        DropShadow{
            source: reload
            anchors.fill: reload
            horizontalOffset: 0
            verticalOffset: 0
            radius: 6
            color: "grey"
        }

        Image {
            id: reload
            width: 30
            anchors.left: wText.right
            anchors.verticalCenter: wText.verticalCenter
            anchors.leftMargin: 10
            anchors.bottomMargin: 6
            antialiasing: true
            smooth: true
            fillMode: Image.PreserveAspectFit
            source: "qrc:/images/images/reload.png"
            states: [
                State {
                    name: "hovered"
                    when: reloadArea.hovered
                    PropertyChanges {
                        target: reload
                        rotation: 180
                    }
                }
            ]
            transitions: [
                Transition {
                    from: ""
                    to: "hovered"

                    NumberAnimation {
                        target: reload
                        property: "rotation"
                        duration: 800
                        easing.type: Easing.InOutQuad
                    }
                },

                Transition {
                    from: "hovered"
                    to: ""

                    NumberAnimation {
                        target: reload
                        property: "rotation"
                        duration: 400
                        easing.type: Easing.InOutQuad
                    }
                }
            ]
        }

        MouseArea{
            id: reloadArea
            property bool hovered
            anchors.fill: reload
            hoverEnabled: true

            onEntered: hovered = true
            onExited: hovered = false
            onPressed: controller.scheduleListModel.loadSchedules()
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
                Layout.preferredWidth: 350
                clip: true
                spacing: 16
                ScrollBar.vertical: ScrollBar{

                }

                model: controller.scheduleListModel

                delegate: Item{
                    width: scheduleList.width
                    height: 100
                    DropShadow{
                        source: rectDelegate
                        anchors.fill: rectDelegate
                        horizontalOffset: 0
                        verticalOffset: 0
                        radius: 8
                        samples: 25
                        color: index === scheduleList.currentIndex ? "#070433": "grey"
                    }
                    Rectangle{
                        id: rectDelegate
                        color: "#ffffff"
                        radius: 4
                        anchors.fill: parent
                        anchors.margins: 4

                        DropShadow{
                            source: flag
                            anchors.fill: flag
                            verticalOffset: 0
                            horizontalOffset: 0
                            radius: 4
                            color: "grey"
                        }

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
                            color: "#070433"
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
                            color: "#a19fbb"
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
                            color: "#a19fbb"
                        }
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
                            //controller.shipDetailModel.getShipDetail(imo)
                            //schedDateTxt.text = schedule_type + ": " + datetime
                            controller.documentFormModel.getShip(imo)
                        }
                    }
                }
            }

            DropShadow{
                source: shipDetailRect
                anchors.fill: shipDetailRect
                verticalOffset: 0
                horizontalOffset: 0
                radius: 4
                color: "grey"
            }

            Rectangle{
                id: shipDetailRect
                Layout.alignment: Qt.AlignTop
                Layout.fillHeight: true
                //Layout.preferredWidth: 840
                //Layout.minimumWidth: 500
                Layout.fillWidth: true
                radius: 4
                color: "#ffffff"

                RoundButton{
                    id: saveButton
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    anchors.bottomMargin: 20
                    text: "\uf0c7"
                    font.family: Style.webFont
                    z: 6

                    onClicked: {
                        controller.documentFormModel.createDocuments(
                            {
                                "terminal": terminalCombo.displayText,
                                "start_date": start_date.selected_date,
                                "end_date": end_date.selected_date,
                                "document_date": document_date.selected_date,
                                "commissionnaire": commissionnaireCombo.displayText,
                                "collecteur": collecteurCombo.displayText,
                                "driver": driverCombo.displayText,
                                "vehicle": vehicleNumberCombo.displayText,
                                "eliminateur": eliminateurCombo.displayText,
                                "invoice_quantity": invoiceQuantity.text,
                                "invoice_amount": invoiceAmount.text
                            }
                        )
                    }

                }

                ScrollView{
                    width: parent.width
                    height: parent.height
                    GridLayout{
                        columnSpacing: 20
                        rowSpacing: 20
                        columns: page.width > 950? 2 : 1
                        Item {
                            width: 350
                            height: 500
                            Layout.alignment: Qt.AlignHCenter

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

                                Image {
                                    id: steeringImg
                                    anchors.top: parent.top
                                    anchors.right: parent.right
                                    anchors.topMargin: 6
                                    anchors.rightMargin: 6
                                    width: 30
                                    visible: controller.fetchingShip
                                    fillMode: Image.PreserveAspectFit
                                    source: "qrc:/images/images/ship-steering.png"

                                    RotationAnimator{
                                        target: steeringImg
                                        from: 0
                                        to: 360
                                        duration: 1200
                                        loops: Animation.Infinite
                                        running: steeringImg.visible
                                    }
                                }

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
                                        id: imoNumberEdit
                                        Layout.margins: 10
                                        enabled: controller.fetchingShip? false : true
                                        label: "IMO Number"
                                        text: controller.documentFormModel.imo
                                        icon: "\uf002"
                                        onTextUpdated: controller.documentFormModel.imo = imoNumberEdit.text
                                        onInputAccepted: (content) => {
                                            controller.documentFormModel.getShip(content)
                                        }
                                    }

                                    LineEdit{
                                        id: shipNameEdit
                                        Layout.margins: 10
                                        label: "Name of ship"
                                        enabled: controller.fetchingShip? false : true
                                        icon: "\uf21a"
                                        text: controller.documentFormModel.shipName
                                        onTextChanged: controller.documentFormModel.shipName = shipNameEdit.text
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
                                        id: flagStateEdit
                                        Layout.margins: 10
                                        label: "Flag State"
                                        text: controller.documentFormModel.flagState
                                        onTextChanged: controller.documentFormModel.flagState = flagStateEdit.text
                                        Item {
                                            id: imgWrapper
                                            anchors.right: parent.right
                                            anchors.bottom: parent.bottom
                                            anchors.bottomMargin: -18
                                            anchors.rightMargin: 4
                                            width: flagImg.width
                                            height: flagImg.height
                                            DropShadow{
                                                source: flagImg
                                                anchors.fill: flagImg
                                                verticalOffset: 0
                                                horizontalOffset: 0
                                                radius: 4
                                                color: "grey"
                                            }
                                            Image {
                                                id: flagImg
                                                height: 30

                                                fillMode: Image.PreserveAspectFit
                                                source: "file:///" + controller.documentFormModel.flagUrl
                                            }
                                        }

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
                            width: 350
                            height: 500
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
                                        text: "RECEPTION FACILITY AND\n PORT PARTICULARS"
                                    }

                                    MComboBox{
                                        id: terminalCombo
                                        Layout.margins: 10
                                        icon: "\ue4aa"
                                        itemEditable: true
                                        label: "Port terminal"
                                        itemModel: controller.documentFormModel.terminalListModel
                                    }

                                    LineEdit{
                                        Layout.margins: 10
                                        label: "Reception facility provider"
                                        text: "S.P.C.E Toamasina port"
                                    }

                                    Column{
                                        Layout.margins: 10
                                        spacing: 4
                                        Text {
                                            text: qsTr("Waste Discharge Date")
                                        }

                                        Row{
                                            spacing: 12
                                            DatePicker{
                                                id: start_date
                                                Layout.margins: 10
                                                label: "From"
                                            }

                                            DatePicker{
                                                id: end_date
                                                Layout.margins: 10
                                                label: "to"
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        Item {
                            width: 350
                            height: 440
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
                                        id: invoiceQuantity
                                        Layout.margins: 10
                                        label: "Quantity"
                                    }

                                    LineEdit{
                                        id: invoiceAmount
                                        Layout.margins: 10
                                        label: "Amount"
                                        icon: "$"
                                    }

                                    DatePicker{
                                        id: document_date
                                        Layout.margins: 10
                                        label: "Date"
                                    }
                                }
                            }
                        }
                        Item {
                            width: 350
                            height: 440
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

                                    MComboBox{
                                        id: commissionnaireCombo
                                        Layout.margins: 10
                                        itemEditable: true
                                        label: "Dénomination"
                                        itemModel: controller.documentFormModel.commListModel
                                        itemTextRole: "name"
                                        onCurrentIndexChanged: (newIndex) => {
                                            console.log("Index: " + newIndex)
                                            controller.documentFormModel.commissionnaireAt(newIndex)
                                        }
                                    }

                                    LineEdit{
                                        Layout.margins: 10
                                        label: "Adresse"
                                        icon: "\uf3c5"
                                        text: controller.documentFormModel.commAddress
                                        onTextChanged: controller.documentFormModel.commAddress = text
                                    }

                                    LineEdit{
                                        Layout.margins: 10
                                        label: "Tél"
                                        icon: "\uf095"
                                        text: controller.documentFormModel.commTel
                                        onTextChanged: controller.documentFormModel.commTel = text
                                    }

                                    LineEdit{
                                        Layout.margins: 10
                                        label: "Mail"
                                        text: controller.documentFormModel.commMail
                                        onTextChanged: controller.documentFormModel.commMail = text
                                    }

                                    LineEdit{
                                        Layout.margins: 10
                                        label: "Responsable"
                                        text: controller.documentFormModel.commResponsable
                                        onTextChanged: controller.documentFormModel.commResponsable = text
                                    }
                                }
                            }
                        }

                        Item {
                            width: 350
                            height: 700
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

                                    MComboBox{
                                        id: collecteurCombo
                                        Layout.margins: 10
                                        itemEditable: true
                                        label: "Nom"
                                        itemModel: controller.documentFormModel.collListModel
                                        onCurrentIndexChanged: (newIndex) => {
                                            controller.documentFormModel.collecteurAt(newIndex)
                                        }
                                    }

                                    LineEdit{
                                        Layout.margins: 10
                                        label: "Adresse"
                                        icon: "\uf3c5"
                                        text: controller.documentFormModel.collAddress
                                        onTextChanged: controller.documentFormModel.collAddress = text
                                    }

                                    LineEdit{
                                        Layout.margins: 10
                                        label: "Tél"
                                        icon: "\uf095"
                                        text: controller.documentFormModel.collTel
                                        onTextChanged: controller.documentFormModel.collTel = text
                                    }

                                    LineEdit{
                                        Layout.margins: 10
                                        label: "Mail"
                                        text: controller.documentFormModel.collMail
                                        onTextChanged: controller.documentFormModel.collMai = text
                                    }

                                    LineEdit{
                                        Layout.margins: 10
                                        label: "Responsable"
                                        text: controller.documentFormModel.collResponsable
                                        onTextChanged: controller.documentFormModel.collResponsable = text
                                    }



                                    MComboBox{
                                        id: driverCombo
                                        Layout.margins: 10
                                        label: "Nom to chauffeur"
                                        itemEditable: true
                                        itemModel: controller.documentFormModel.driverListModel
                                    }

                                    MComboBox{
                                        id: vehicleNumberCombo
                                        Layout.margins: 10
                                        label: "Numéro du véhicule"
                                        itemEditable: true
                                        itemModel: controller.documentFormModel.vehicleListModel
                                        onCurrentIndexChanged: (newIndex) => {
                                            controller.documentFormModel.vehicleAt(newIndex)
                                        }
                                    }

                                    LineEdit{
                                        Layout.margins: 10
                                        label: "Type du véhicule"
                                        text: controller.documentFormModel.vehicleType
                                        onTextChanged: controller.documentFormModel.vehicleType = text
                                    }
                                }
                            }
                        }

                        Item {
                            width: 350
                            height: 700
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

                                    MComboBox{
                                        id: eliminateurCombo
                                        Layout.margins: 10
                                        itemEditable: true
                                        label: "Nom"
                                        itemModel: controller.documentFormModel.eliminateurListModel
                                        onCurrentIndexChanged: (newIndex) => {
                                            controller.documentFormModel.eliminateurAt(newIndex)
                                        }
                                    }

                                    LineEdit{
                                        Layout.margins: 10
                                        label: "Adresse"
                                        icon: "\uf3c5"
                                        text: controller.documentFormModel.elimAddress
                                        onTextChanged: controller.documentFormModel.elimAddress = text
                                    }

                                    LineEdit{
                                        Layout.margins: 10
                                        label: "Tél"
                                        icon: "\uf095"
                                        text: controller.documentFormModel.elimTel
                                        onTextChanged: controller.documentFormModel.elimTel = text
                                    }

                                    LineEdit{
                                        Layout.margins: 10
                                        label: "Mail"
                                        text: controller.documentFormModel.elimMail
                                        onTextChanged: controller.documentFormModel.elimMail = text
                                    }

                                    LineEdit{
                                        Layout.margins: 10
                                        label: "Responsable"
                                        text: controller.documentFormModel.elimResponsable
                                        onTextChanged: controller.documentFormModel.elimResponsable = text
                                    }

                                    LineEdit{
                                        Layout.margins: 10
                                        label: "Site de réception"
                                        text: controller.documentFormModel.elimReceptionSite
                                        onTextChanged: controller.documentFormModel.elimReceptionSite = text
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}
