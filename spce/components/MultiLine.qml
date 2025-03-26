import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import QtQuick.Layouts
import ".."

Item {
    id: root
    property alias h: bg.implicitHeight
    property alias w: bg.implicitWidth
    property alias text: textField.text
    property alias label: textFieldLabel.text
    property alias icon: textIcon.icon
    width: w
    height: h
    signal textUpdated(var text)
    signal inputAccepted(var text)
    ColumnLayout{
        spacing: 6
        width: parent.width
        Text {
            id: textFieldLabel
            color: Style.textColor
        }

        TextArea{
            id: textField
            Layout.preferredHeight: 60
            Layout.preferredWidth: 250
            color: Style.titleTextColor
            leftPadding: textIcon.icon !== ""? 25 : 4
            verticalAlignment: TextInput.AlignVCenter
            wrapMode: TextArea.Wrap
            onTextChanged: {
                root.textUpdated(textField.text)
            }

            background: Rectangle{
                id: bg
                implicitHeight: 60
                implicitWidth: 250
                width: 250
                height: 60

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
                        color: "white"
                        radius: 4

                        TextIconBtn{
                            id: textIcon
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            itemWidth: 25
                            itemHeight: 40
                            iconColor: "#757575"
                            iconSize: 10
                        }
                    }
                }
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


}
