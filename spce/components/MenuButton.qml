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
    Rectangle{
        id: btnRect
        radius: 3
        anchors.fill: parent
        color: "transparent"
        Behavior on color {
            PropertyAnimation{
                duration: 200
            }
        }

        Image {
            id: icon
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 2
            width: 30
            height: 30
            fillMode: Image.PreserveAspectFit
            source: iconNormal
        }

        Text {
            id: txt
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: icon.right
            anchors.leftMargin: 3
            color: "white"
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
                        color: Qt.lighter("#0c203c")
                    }

                    PropertyChanges {
                        target: txt
                        color: "#bdfe50"
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
                        color: Qt.lighter("#0c203c")
                    }
                    PropertyChanges {
                        target: txt
                        color: "#bdfe50"
                    }

                    PropertyChanges {
                        target: icon
                        source: iconHover

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
