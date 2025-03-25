import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import Qt.labs.qmlmodels
import QtQuick.Controls.Material
import QtCharts 2.7
import ".."
import "../components"

Page {
    id: root
    property string currentInvoice
    Connections{
        target: controller.invoiceTableModel
        function onInvoiceUpdated() {
            loadRevenueBarSeries()
        }
    }

    background: Rectangle{
        anchors.fill: parent
        color: "white"
    }

    function formatNumber(number) {
        var loc = Qt.locale()
        return loc.toString(number)
    }

    function toString(value, index){
        if (index === 1 || index === 2)
            return formatNumber(value)
        return value
    }

    function loadRevenueBarSeries(){
        controller.revenueChartModel.loadData()
        var i = controller.revenueChartModel.rowCount()
        revenueBarSerie.clear()
        garbageBarSerie.clear()
        monthAxis.categories = []
        monthGAxis.categories = []
        revenueBarSerie.append("Revenue", [])
        garbageBarSerie.append("Garbage Removed", [])
        revenueBarSerie.at(0).color = Style.buttonDefault
        garbageBarSerie.at(0).color = "#8cc63f"
        for (var index = 0; index < i; index++)
        {
            var month = controller.revenueChartModel.dataAt(index, 257)
            var amounts = controller.revenueChartModel.dataAt(index, 258)
            var garbage = controller.revenueChartModel.dataAt(index, 259)
            monthAxis.categories.push(month)
            monthGAxis.categories.push(month)
            revenueBarSerie.at(0).values.push(amounts[0])
            garbageBarSerie.at(0).values.push(garbage[0])
            revenueYaxis.max = Math.max(revenueYaxis.max, amounts[0])
            garbageYaxis.max = Math.max(garbageYaxis.max, garbage[0])
        }
    }

    function loadShipTypeSeriesData() {
        controller.chartModel.loadData()
        var dataCount = controller.chartModel.shipTypeDistroCount()
        shipTypeSeries.clear()
        for (var i = 0; i < dataCount; i++)
        {
            var label = controller.chartModel.dataAt(i, 257)
            var value = controller.chartModel.dataAt(i, 258)
            shipTypeSeries.append(label, value)
        }
    }

    Component.onCompleted: {
        loadRevenueBarSeries()
        loadShipTypeSeriesData()
    }

    Text {
        id: wText
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 12
        anchors.leftMargin: 16
        text: "Invoices"
        font.bold: true
        font.pointSize: 22
        color: Style.titleTextColor
    }

    ColumnLayout{
        anchors.top: wText.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 6
        spacing: 6

        Item {
            id: chartRectWrapper
            Layout.fillWidth: true
            Layout.preferredHeight: root.height * 0.45

            DropShadow{
                source: chartRect
                anchors.fill:  chartRect
                horizontalOffset: 0
                verticalOffset: 0
                radius: 6
            }

            Rectangle{
                id: chartRect
                anchors.fill: parent
                anchors.margins: 4
                color: "white"
                radius: 6
                GridLayout{
                    anchors.fill: parent
                    anchors.topMargin: 6
                    columnSpacing: 16
                    rowSpacing: 8
                    columns: 4
                    Rectangle{
                        Layout.preferredHeight: 100
                        Layout.preferredWidth: 200
                        Layout.leftMargin: 6
                        radius: 6
                        color: Style.primary
                        Text {
                            id: t_1
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.margins: {
                                top: 6
                                left: 6
                            }
                            text: "Generated invoices"
                            font.bold: true
                            font.pointSize: 14
                            color: "white"
                        }

                        Text {
                            id: t_2
                            anchors.top: t_1.bottom
                            anchors.left: parent.left
                            anchors.margins: {
                                top: 20
                                left: 6
                            }
                            text: controller.invoiceTableModel.invoiceCount
                            font.bold: true
                            font.pointSize: 20
                            color: "white"
                        }

                        Image {
                            id: in_image
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            anchors.rightMargin: 6
                            anchors.bottomMargin: 8
                            width: 50
                            fillMode: Image.PreserveAspectFit
                            source: "qrc:/images/images/invoice_incon1.png"
                        }
                    }
                    Rectangle{
                        Layout.preferredHeight: 100
                        Layout.preferredWidth: 200
                        radius: 6
                        color: Style.buttonDefault
                        Text {
                            id: t_3
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.margins: {
                                top: 6
                                left: 6
                            }
                            text: "Total Amounts"
                            font.bold: true
                            font.pointSize: 14
                            color: "white"
                        }

                        Text {
                            id: t_4
                            anchors.top: t_3.bottom
                            anchors.left: parent.left
                            anchors.margins: {
                                top: 20
                                left: 6
                            }
                            text: "$" + formatNumber(controller.invoiceTableModel.totalAmount)
                            font.bold: true
                            font.pointSize: 20
                            color: "white"
                        }

                        Image {
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            anchors.rightMargin: 6
                            anchors.bottomMargin: 8
                            width: 50
                            fillMode: Image.PreserveAspectFit
                            source: "qrc:/images/images/money.png"
                        }
                    }

                    Rectangle{
                        Layout.preferredHeight: 100
                        Layout.preferredWidth: 240
                        radius: 6
                        color: "#8cc63f"
                        Text {
                            id: t_5
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.margins: {
                                top: 6
                                left: 6
                            }
                            text: "Garbage collected"
                            font.bold: true
                            font.pointSize: 14
                            color: "white"
                        }

                        Text {
                            id: t_6
                            anchors.top: t_5.bottom
                            anchors.left: parent.left
                            anchors.margins: {
                                top: 20
                                left: 6
                            }
                            text: formatNumber(controller.invoiceTableModel.totalGarbage) + " CBM"
                            font.bold: true
                            font.pointSize: 20
                            color: "white"
                        }

                        Image {
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            anchors.rightMargin: 6
                            anchors.bottomMargin: 8
                            width: 50
                            fillMode: Image.PreserveAspectFit
                            source: "qrc:/images/images/recycling-truck.png"
                        }
                    }

                    Rectangle{
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.rightMargin: 4
                        Layout.rowSpan: 2

                        ChartView{
                            id: revenueChartView
                            title: "Monthly generated revenue & garbage removed"
                            anchors.fill: parent
                            legend.alignment: Qt.AlignBottom
                            antialiasing: true
                            animationOptions: ChartView.SeriesAnimations
                            locale: Qt.locale("en_US")
                            localizeNumbers: true

                            ToolTip{
                                id: revenueTooltip
                                visible: false
                                background: Rectangle {
                                    color: Style.buttonDefault
                                    radius: 5
                                }
                            }

                            ToolTip{
                                id: garbageTooltip
                                visible: false
                                background: Rectangle {
                                    color: "#8cc63f"
                                    radius: 5
                                }
                            }

                            BarSeries{
                                id: revenueBarSerie
                                axisX: BarCategoryAxis {
                                    id: monthAxis
                                     categories: ["Revenues"]
                                }
                                axisY: ValuesAxis{
                                    id: revenueYaxis
                                    min: 0
                                    max: 100

                                    labelFormat: "%.0f"
                                    titleText: "Revenue ($)"
                                }
                                onHovered: (status, index, barset) => {
                                    if (status) {
                                        var mouseP = revenueChartView.mapToPosition(Qt.point(index, barset.at(index)), revenueBarSerie)
                                        revenueTooltip.x = mouseP.x
                                        revenueTooltip.y = mouseP.y
                                        revenueTooltip.text = "$" + formatNumber(revenueBarSerie.at(0).values[index])
                                        revenueTooltip.visible = true
                                    }
                                    else{
                                        revenueTooltip.visible = false
                                    }
                                }
                            }

                            BarSeries{
                                id: garbageBarSerie
                                axisX: BarCategoryAxis {
                                    id: monthGAxis
                                    visible: false
                                    categories: ["Garbage"]
                                }
                                axisYRight: ValuesAxis{
                                    id: garbageYaxis
                                    min: 0
                                    max: 40

                                    labelFormat: "%.0f"
                                    titleText: "Quantity (CBM)"
                                }
                                onHovered: (status, index, barset) => {
                                    if (status) {
                                        var mouseP = revenueChartView.mapToPosition(Qt.point(index, barset.at(index)), garbageBarSerie)
                                        garbageTooltip.x = mouseP.x
                                        garbageTooltip.y = mouseP.y
                                        garbageTooltip.text = formatNumber(garbageBarSerie.at(0).values[index]) + " CBM"
                                        garbageTooltip.visible = true
                                    }
                                    else{
                                        garbageTooltip.visible = false
                                    }
                                }
                            }
                        }
                    }

                    Rectangle{
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.columnSpan: 3
                        Layout.leftMargin: 4
                        ChartView{
                            id: shipTypeChartView
                            property real mX
                            property real mY
                            title: "Ship Types distribution"
                            anchors.fill: parent
                            legend.alignment: Qt.AlignRight
                            antialiasing: true
                            animationOptions: ChartView.SeriesAnimations
                            locale: Qt.locale("en_US")
                            localizeNumbers: true

                            ToolTip{
                                id: shipTypeValue
                                visible: false
                                timeout: 1000
                            }

                            MouseArea {
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onPositionChanged: (mouse) => {
                                        shipTypeChartView.mX = mouseX
                                        shipTypeChartView.mY = mouseX
                                    }
                                }

                            PieSeries{
                                id: shipTypeSeries
                                onHovered: (slice, state) => {
                                    if (state)
                                    {
                                        shipTypeValue.x = shipTypeChartView.mX
                                        shipTypeValue.y = shipTypeChartView.mY
                                        shipTypeValue.text = slice.value
                                        shipTypeValue.visible = true
                                        slice.exploded = true
                                    }
                                    else
                                        slice.exploded = false
                                        shipTypeValue.visible = false
                                }
                            }
                        }
                    }
                }
            }
        }

        Item {
            id: tableWrapper
            Layout.fillHeight: true
            Layout.fillWidth: true

            DropShadow{
                source: tableRect
                anchors.fill:  tableRect
                horizontalOffset: 0
                verticalOffset: 0
                radius: 6
            }

            Rectangle{
                id: tableRect
                anchors.fill: parent
                anchors.margins: 4
                color: "white"
                radius: 6
                Rectangle{
                    width: parent.width
                    height: 30
                    anchors.top: parent.top
                    radius: parent.radius
                    color: Style.primary

                    Rectangle{
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 6
                        color: parent.color
                    }
                }


                HorizontalHeaderView{
                    id: horizontalHeader
                    anchors.left: invoiceTable.left
                    anchors.top: parent.top
                    //anchors.topMargin: 3
                    syncView: invoiceTable
                    clip: invoiceTable
                    delegate: Rectangle {
                        implicitWidth: 120
                        implicitHeight: 30
                        color: Style.primary
                        Label {
                            anchors.centerIn: parent
                            text: display
                            color: "white"
                            font.bold: true
                        }
                    }
                }

                TableView{
                    id: invoiceTable
                    property int hoveredRow: -1
                    property int activeRow
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: horizontalHeader.bottom
                    anchors.bottom: parent.bottom
                    anchors.margins: 4
                    columnSpacing: 1
                    rowSpacing: 1
                    clip: true
                    selectionBehavior: TableView.SelectRows
                    selectionMode: TableView.SingleSelection

                    model: controller.invoiceTableModel
                    ScrollBar.vertical: ScrollBar{}
                    ScrollBar.horizontal: ScrollBar{}

                    delegate: Rectangle {
                        implicitWidth: 120
                        implicitHeight: 26
                        color: invoiceTable.hoveredRow === row? "#6c82c1" : row % 2 === 0? "white" : "#a7b5dc"
                        RowLayout{
                            id: row_l
                            visible: column === 6
                            width: parent.width
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 4
                            spacing: 4
                            Label{
                                text: row_l.visible? display.text : ""
                            }
                            Rectangle{
                                Layout.preferredHeight: 20
                                Layout.preferredWidth: flg.width
                                Layout.alignment: Qt.AlignRight
                                DropShadow{
                                    source: flg
                                    anchors.fill:  flg
                                    horizontalOffset: 0
                                    verticalOffset: 0
                                    radius: 2
                                }
                                Image {
                                    id: flg
                                    height: parent.height
                                    fillMode: Image.PreserveAspectFit
                                    source: row_l.visible ? "file:///" + controller.flagDir + "/" + display.url : ""
                                }
                            }


                        }

                        Label {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 4
                            visible: column !== 6
                            text: column !== 6? display : ""
                        }

                        MouseArea{
                            id: m_area
                            anchors.fill: parent
                            hoverEnabled: !contextMenu.visible
                            acceptedButtons: Qt.RightButton
                            onEntered: {
                                invoiceTable.hoveredRow = row
                            }
                            onClicked: (mouse) => {
                                contextMenu.popup()
                                console.log(invoiceTable.model.data(invoiceTable.index(row, 0)))
                                invoiceTable.activeRow = row
                            }
                        }
                    }
                }
            }
        }
    }
    Menu{
        id: contextMenu
        MenuItem{
            text: "Export PDF"
            icon.source: "qrc:/images/images/file-pdf.png"
            //icon.color: "red"
        }

        MenuItem{
            text: "Edit invoice"
            icon.source: "qrc:/images/images/ui-edit.png"
            onClicked:
            {
                var invoice = controller.invoiceTableModel.invoiceAt(invoiceTable.activeRow)
                invoiceEditFields.visible = true
                invoiceAmount.text = invoice["amount"]
                invoiceQuantity.text = invoice["quantity"]
                invoiceNumberTxt.text = invoice["invoice_number"] + " for " + invoice["ship_name"]
                root.currentInvoice = invoice["invoice_number"]
            }
        }

        MenuSeparator{}

        MenuItem{
            text: "Delete"
            icon.source: "qrc:/images/images/ui-delete.png"
            icon.color: "red"
        }
    }
    DropShadow{
        source: invoiceEditFields
        anchors.fill: invoiceEditFields
        horizontalOffset: -2
        verticalOffset: 2
        radius: 6
        color: "grey"
    }

    Rectangle{
        id: invoiceEditFields
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        visible: false
        width: 400
        height: 300

        ColumnLayout{
            anchors.fill: parent
            anchors.margins: 4
            spacing: 6
            Text {
                id: invoiceNumberTxt
                font.bold: true
                font.pointSize: 10
                Layout.alignment: Qt.AlignCenter
            }

            LineEdit{
                id: invoiceQuantity
                Layout.margins: 10
                Layout.alignment: Qt.AlignCenter
                label: "Quantity"
            }

            LineEdit{
                id: invoiceAmount
                Layout.margins: 10
                Layout.alignment: Qt.AlignCenter
                label: "Amount"
                icon: "$"
            }

            RowLayout{
                Layout.alignment: Qt.AlignRight
                spacing: 6
                Button{
                    text: "Save"
                    Layout.alignment: Qt.AlignRight
                    onClicked: {
                        controller.invoiceTableModel.updateInvoice(
                            {
                                "invoice_number": root.currentInvoice,
                                "amount": invoiceAmount.text,
                                "quantity": invoiceQuantity.text
                            },
                            invoiceTable.activeRow
                        )
                        invoiceEditFields.visible = false
                    }
                }

                Button{
                    text: "Cancel"
                    onClicked: invoiceEditFields.visible = false
                    Layout.alignment: Qt.AlignRight
                }
            }
        }

        states: [
            State {
                name: "editing"
                when: invoiceEditFields.visible
                PropertyChanges {
                    target: invoiceEditFields
                    width: 450
                }
            },
            State {
                name: "hidden"
                when: !invoiceEditFields.visible
                PropertyChanges {
                    target: invoiceEditFields
                    width: 0
                }
            }
        ]
        transitions: [
            Transition {
                from: "hidden"
                to: "editing"

                NumberAnimation {
                    target: invoiceEditFields
                    property: "width"
                    duration: 200
                    easing.type: Easing.InOutQuad
                }
            },
            Transition {
                from: "editing"
                to: "hidden"

                NumberAnimation {
                    target: invoiceEditFields
                    property: "width"
                    duration: 300
                    easing.type: Easing.InOutQuad
                }
            }
        ]
    }
}
