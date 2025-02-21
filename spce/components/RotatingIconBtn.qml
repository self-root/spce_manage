import QtQuick
import QtQuick.Controls

Item {
    id: rotatingIconBtn
    property alias text: btnTxt.text
    property alias buttonColor: aRect.color
    property alias icon: btnIcon.source
    property alias textColor: btnTxt.color
    property alias buttonW: rotatingIconBtn.width
    property alias buttonH: rotatingIconBtn.height
    property bool hovered: false
    signal clicked()
    Rectangle{
        id: aRect
        anchors.fill: rotatingIconBtn
        radius: 4
        Image {
            id: btnIcon
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 4
            height: 30
            fillMode: Image.PreserveAspectFit
            Behavior on rotation {
                PropertyAnimation{
                    duration: 500
                }
            }
        }
        Text {
            id: btnTxt
            anchors.left: btnIcon.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 6

            font.pointSize: 11
            font.bold: true
        }

        MouseArea{
            id: rectBtnArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor

            onEntered: {
                hovered = true
            }

            onExited: {
                hovered = false
            }

            onClicked: rotatingIconBtn.clicked()

            states:[
                State {
                    name: "btnhovered"
                    when: hovered
                    PropertyChanges {
                        target: btnIcon
                        rotation: 180
                    }
                }
            ]
        }
    }
}
