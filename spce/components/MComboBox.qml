import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import QtQuick.Controls.Material
import ".."

Item {
    id: control
    property alias h: bg.implicitHeight
    property alias w: bg.implicitWidth
    property alias text: a_combo.currentText
    property alias label: a_label.text
    property alias itemModel: a_combo.model
    property alias itemEditable: a_combo.editable
    property alias itemTextRole: a_combo.textRole
    property alias displayText: a_combo.displayText
    property alias icon: textIcon.icon
    property int index
    property bool completed: false
    signal currentIndexChanged(var index)

    width: w
    height: h
    Column{
        spacing: 6
        width: parent.width
        Text {
            id: a_label
            color: Style.textColor
        }

        ComboBox{
            id: a_combo
            leftPadding: textIcon.icon !== ""? 10 : 4
            background: Rectangle{
                id: bg
                implicitHeight: 40
                implicitWidth: 250

                Item {
                    id: rectWraper
                    anchors.fill: parent
                    DropShadow{
                        anchors.fill: bgBox
                        source: bgBox
                        horizontalOffset: 0
                        verticalOffset: 0
                        radius: 3
                        color: a_combo.focus ? Style.boxShadowActive : Style.boxShadow
                    }

                    Rectangle{
                        id: bgBox
                        width: parent.width
                        height: parent.height
                        anchors.bottom: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        border.color: a_combo.focus ? Style.primary : "#d6d8d9"
                        color: "white"
                        radius: 4

                        TextIconBtn{
                            id: textIcon
                            anchors.left: parent.left
                            itemWidth: 25
                            itemHeight: 40
                            iconColor: "#757575"
                            iconSize: 10
                        }
                    }
                }
            }

            onActivated: {
                control.index = a_combo.currentIndex
                control.currentIndexChanged(a_combo.currentIndex)
            }

            onEditTextChanged: {
                if (currentIndex !== -1 && currentText !== a_combo.editText) {
                    console.log("Edit text changed: " + a_combo.editText)
                    a_combo.currentIndex = -1
                    control.index = -1
                    control.currentIndexChanged(-1)
                }

                else{
                    a_combo.displayText = a_combo.editText
                }

            }

            states: [State {
                name: "focused"
                when: a_combo.focus
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

    Component.onCompleted: {
        control.completed = true
    }
}
