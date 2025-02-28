import QtQuick
import QtQuick.Controls
import ".."

Item {
    id: textBtn
    property alias w: textBtn.width
    property alias h: textBtn.height
    property alias text: txt.text
    property bool hovered: false
    property bool pressed: false
    signal clicked()

    width: 150
    height: 30

    Rectangle {
        id: btnRect
        anchors.fill: parent
        anchors.margins: 3
        color: Style.buttonDefault
        radius: 6
        border.color: btnRect.color
        Text {
            id: txt
            color: "white"
            anchors.centerIn: parent
            font.pointSize: 11
            font.family: Style.robotFont

        }

        MouseArea{
            id: mArea
            anchors.fill: parent
            hoverEnabled: true

            onEntered: {
                textBtn.hovered = true
            }

            onExited: {
                textBtn.hovered = false
            }

            onPressed: {
                textBtn.pressed = true
            }

            onReleased: {
                textBtn.pressed = false
                textBtn.clicked()
            }
        }

        states: [
            State {
                name: "hovered"
                when: hovered
                PropertyChanges {
                    target: btnRect
                    color: Style.buttonHovered
                }
            },
            State {
                name: "pressed"
                when: textBtn.pressed
                PropertyChanges {
                    target: btnRect
                    color: Style.buttonActive
                }
            }
        ]
    }
}
