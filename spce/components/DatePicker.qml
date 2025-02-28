import QtQuick
import QtQuick.Controls
Item {
    id :root
    property alias w: root.width
    property alias h: root.height
    property color primary: "#00BCD4"
    property color primary_dark: "#0097A7"
    property color primary_light: "#B2EBF2"
    property color accent: "#FF5722"
    property color primary_text: "#212121"
    property color secondary_text: "#757575"
    property color icons: "#FFFFFF"
    property color divider: "#BDBDBD"

    readonly property double mm: Screen.pixelDensity

    Rectangle {
        id: mainForm
        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
        }
        height: cellSize * 12
        width: cellSize * 8
        property double cellSize: 40
        property int fontSizePx: cellSize * 0.32

        Rectangle {
            id: titleOfDate
            anchors {
                top: parent.top
                horizontalCenter: parent.horizontalCenter
            }
            height: 2.5 * mainForm.cellSize
            width: parent.width
            color: primary_dark
            z: 2
            Rectangle {
                id: selectedYear
                anchors {
                    top: parent.top
                    left: parent.left
                    right: parent.right
                }
                height: mainForm.cellSize * 1
                color: parent.color
                Text {
                    id: yearTitle
                    anchors.fill: parent
                    leftPadding: mainForm.cellSize * 0.5
                    topPadding: mainForm.cellSize * 0.5
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: mainForm.fontSizePx * 1.7
                    opacity: yearsList.visible ? 1 : 0.7
                    color: "white"
                    text: calendar.currentYear
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        yearsList.show();
                    }
                }
            }
            Text {
                id: selectedWeekDayMonth
                anchors {
                    left: parent.left
                    right: parent.right
                    top: selectedYear.bottom
                    bottom: parent.bottom
                }
                leftPadding: mainForm.cellSize * 0.5
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: height * 0.5
                text: calendar.weekNames[calendar.week].slice(0, 3) + ", " + calendar.currentDay + " " + calendar.months[calendar.currentMonth].slice(0, 3)
                color: "white"
                opacity: yearsList.visible ? 0.7 : 1
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        yearsList.hide();
                    }
                }
            }
        }

        ListView {
            id: calendar
            anchors {
                top: titleOfDate.bottom
                left: parent.left
                right: parent.right
                leftMargin: mainForm.cellSize * 0.5
                rightMargin: mainForm.cellSize * 0.5
            }
            height: mainForm.cellSize * 9
            visible: true
            z: 1
            clip: true

            snapMode: ListView.SnapToItem
            orientation: ListView.Horizontal
            spacing: mainForm.cellSize
            model: CalendarModel {
                id: calendarModel
                from: new Date(new Date().getFullYear(), 0, 1);
                to: new Date(new Date().getFullYear(), 11, 31);
                function  setYear(newYear) {
                    if (calendarModel.from.getFullYear() > newYear) {
                        calendarModel.from = new Date(newYear, 0, 1);
                        calendarModel.to = new Date(newYear, 11, 31);
                    } else {
                        calendarModel.to = new Date(newYear, 11, 31);
                        calendarModel.from = new Date(newYear, 0, 1);
                    }
                    calendar.currentYear = newYear;
                    calendar.goToLastPickedDate();
                }
            }

            property int currentDay: new Date().getDate()
            property int currentMonth: new Date().getMonth()
            property int currentYear: new Date().getFullYear()
            property int week: new Date().getDay()
            property var months: ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
            property var weekNames: ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"]

            delegate: Rectangle {
                height: mainForm.cellSize * 8.5 //6 - на строки, 1 на дни недели и 1.5 на подпись
                width: mainForm.cellSize * 7
                Rectangle {
                    id: monthYearTitle
                    anchors {
                        top: parent.top
                    }
                    height: mainForm.cellSize * 1.3
                    width: parent.width

                    Text {
                        anchors.centerIn: parent
                        font.pointSize: mainForm.fontSizePx * 1.2
                        text: calendar.months[model.month] + " " + model.year;
                    }
                }

                DayOfWeekRow {
                    id: weekTitles
                    locale: monthGrid.locale
                    anchors {
                        top: monthYearTitle.bottom
                    }
                    height: mainForm.cellSize
                    width: parent.width
                    delegate: Text {
                        text: model.shortName
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: mainForm.fontSizePx
                    }
                }

                MonthGrid {
                    id: monthGrid
                    month: model.month
                    year: model.year
                    spacing: 0
                    anchors {
                        top: weekTitles.bottom
                    }
                    width: mainForm.cellSize * 7
                    height: mainForm.cellSize * 6

                    locale: Qt.locale("en_US")
                    delegate: Rectangle {
                        height: mainForm.cellSize
                        width: mainForm.cellSize
                        radius: height * 0.5
                        property bool highlighted: enabled && model.day === calendar.currentDay && model.month === calendar.currentMonth && model.year === calendar.currentYear

                        enabled: model.month === monthGrid.month
                        color: enabled && highlighted ? primary_dark : "white"

                        Text {
                            anchors.centerIn: parent
                            text: model.day
                            font.pointSize: mainForm.fontSizePx
                            scale: highlighted ? 1.25 : 1
                            Behavior on scale { NumberAnimation { duration: 150 } }
                            visible: parent.enabled
                            color: parent.highlighted ? "white" : "black"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                calendar.currentDay = model.date.getDate();
                                calendar.currentMonth = model.date.getMonth();
                                calendar.week = model.date.getDay();
                                calendar.currentYear = model.date.getFullYear();
                            }
                        }
                    }
                }
            }


            Component.onCompleted: goToLastPickedDate()
            function goToLastPickedDate() {
                positionViewAtIndex(calendar.currentMonth, ListView.SnapToItem)
            }
        }

        ListView {
            id: yearsList
            anchors.fill: calendar
            orientation: ListView.Vertical
            visible: false
            z: calendar.z

            property int currentYear
            property int startYear: 1940
            property int endYear : new Date().getFullYear() + 50;
            model: ListModel {
                id: yearsModel
            }

            delegate: Rectangle {
                width: parent.width
                height: mainForm.cellSize * 1.5
                Text {
                    anchors.centerIn: parent
                    font.pixelSize: mainForm.fontSizePx * 1.5
                    text: name
                    scale: index == yearsList.currentYear - yearsList.startYear ? 1.5 : 1
                    color: primary_dark
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        calendarModel.setYear(yearsList.startYear + index);
                        yearsList.hide();
                    }
                }
            }

            Component.onCompleted: {
                for (var year = startYear; year <= endYear; year ++)
                    yearsModel.append({name: year});
            }
            function show() {
                visible = true;
                calendar.visible = false
                currentYear = calendar.currentYear
                yearsList.positionViewAtIndex(currentYear - startYear, ListView.SnapToItem);
            }
            function hide() {
                visible = false;
                calendar.visible = true;
            }
        }
    }

}
