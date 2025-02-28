import QtQuick
import QtQuick.Controls

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

    Rectangle{
        id: btnRect
        radius: 6
        anchors.fill: parent
        color: "transparent"

        Image {
            id: icon
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 8
            width: 30
            height: 30
            fillMode: Image.PreserveAspectFit
            source: iconNormal
        }

        Text {
            id: txt
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: icon.right
            anchors.leftMargin: 8
            color: "#96a1bb"
            font.family: robotoF.name
            font.weight: Font.Medium
            font.pointSize: 12
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
