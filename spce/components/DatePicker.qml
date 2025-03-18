import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import ".."
import QtQuick.Dialogs

Item {
    id: control
    property alias h: bg.implicitHeight
    property alias w: bg.implicitWidth
    property alias text: textField.text
    property alias label: textFieldLabel.text
    property var selected_date : new Date()
    width: w
    height: h
    Connections{
        target: calendar
        function onDateSelected(date)
        {
            console.log(date)
            textField.text = date.toLocaleString(Qt.locale("fr_FR"), "dd/MM/yyyy")
            calendarPopup.close()
            selected_date = date
        }
    }

    Column{
        spacing: 6
        width: parent.width
        Text {
            id: textFieldLabel
            color: Style.textColor
        }

        TextField{
            id: textField
            color: Style.titleTextColor
            readOnly: true
            text: new Date().toLocaleString(Qt.locale("fr_FR"), "dd/MM/yyyy")
            leftPadding: 25
            background: Rectangle{
                id: bg
                implicitHeight: 40
                implicitWidth: 100

                Item {
                    id: rectWraper
                    anchors.fill: parent
                    DropShadow{
                        anchors.fill: bgBox
                        source: bgBox
                        horizontalOffset: 0
                        verticalOffset: 0
                        radius: 3
                        color: textField.focus ? Style.boxShadowActive : Style.boxShadow
                    }

                    Rectangle{
                        id: bgBox
                        width: parent.width
                        height: parent.height
                        anchors.bottom: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        border.color: textField.focus ? Style.primary : "#d6d8d9"
                        color: "transparent"
                        radius: 4

                        TextIconBtn{
                            anchors.left: parent.left
                            itemWidth: 25
                            itemHeight: 40
                            iconColor: "#757575"
                            iconSize: 10
                            icon: "\uf073"
                        }


                    }
                }
            }



            onPressed: {
                calendarPopup.open()
            }

            states: [State {
                    name: "focused"
                    when: textField.focus
                    PropertyChanges {
                        target: bgBox
                        height: bg.implicitHeight
                    }
                }
            ]

            transitions: [
                Transition {
                    from: ""
                    to: "focused"
                    NumberAnimation {
                        target: bgBox
                        property: "height"
                        duration: 300
                        easing.type: Easing.InOutQuad
                    }
                },

                Transition {
                    from: "focused"
                    to: ""

                    NumberAnimation {
                        target: bgBox
                        property: "height"
                        duration: 300
                        easing.type: Easing.InOutQuad
                    }
                }
            ]
        }
    }

    Popup{
        id: calendarPopup
        width: calendar.width
        height: calendar.height
        x: -100
        y: 70

        background: Item {
            Rectangle {
                id: popupBackground
                anchors.fill: parent
                color: "white"
                radius: 2  // Rounded corners
            }

            DropShadow {
                anchors.fill: popupBackground
                source: popupBackground
                color: "#80000000"  // Shadow color with transparency
                radius: 12  // Shadow blur radius
                samples: 24  // Higher samples = smoother shadow
                spread: 0.2  // Adjust for softer edges
                horizontalOffset: 0
                verticalOffset: 0
            }
        }

        MCalendar{
            id: calendar
            anchors.centerIn: parent
        }
    }



}
