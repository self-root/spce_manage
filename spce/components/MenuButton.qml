import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import ".."

Item {
    id: menuBtn
    property alias iconSource: icon.source
    property alias text: txt.text
    property string iconHover
    property string iconNormal
    property bool current: false
    property bool hovered: false
    signal clicked()

    FontLoader{
        id: robotoF
        source: "qrc:/fonts/fonts/Roboto-Regular.ttf"
    }

    DropShadow{
        source: btnRect
        anchors.fill: btnRect
        verticalOffset: 0
        horizontalOffset: 0
        radius: 4
        spread: 0.4
        color: Style.textColor
    }

    Rectangle{
        id: btnRect
        radius: 6
        anchors.fill: parent
        color: "white"

        Image {
            id: icon
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 8
            sourceSize: Qt.size(50, 50)
            //width: 25
            height: 25
            fillMode: Image.PreserveAspectFit
            source: iconNormal
            smooth: true
            antialiasing: true
        }

        Text {
            id: txt
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: icon.right
            anchors.leftMargin: 8
            color: Style.textColor
            font.family: robotoF.name
            font.weight: Font.Medium
            font.pointSize: 10
            //color: "#056839"
        }


        MouseArea{
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                menuBtn.hovered = true
            }

            onExited: {
                 menuBtn.hovered = false
            }

            states: [
                State {
                    name: "hovered"
                    when: menuBtn.hovered
                    PropertyChanges {
                        target: btnRect
                        color: "#253c7f"
                    }

                    PropertyChanges {
                        target: txt
                        color: "white"
                    }

                    PropertyChanges {
                        target: icon
                        source: iconHover
                    }
                },

                State {
                    name: "btnSelected"
                    when: menuBtn.current
                    PropertyChanges {
                        target: btnRect
                        color: "#253c7f"
                    }
                    PropertyChanges {
                        target: txt
                        color: "white"
                    }

                    PropertyChanges {
                        target: icon
                        source: iconHover

                    }


                }
            ]

            transitions: [
                Transition {
                    from: ""
                    to: "hovered"

                    PropertyAnimation{
                        target: btnRect
                        property: "color"
                        duration: 400
                    }
                },
                Transition {
                    from: "hovered"
                    to: ""

                    PropertyAnimation{
                        target: btnRect
                        property: "color"
                        duration: 400
                    }
                }
            ]

            onClicked: {
                menuBtn.current = true
                menuBtn.clicked()
            }
        }
    }
}
