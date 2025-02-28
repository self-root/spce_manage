import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

Item {

    id: root
        width: 400
        implicitHeight: contentBox.implicitHeight + 20 + titleText.implicitHeight

        property alias title: titleText.text

        DropShadow {
            source: contentBox
            anchors.fill: contentBox
            horizontalOffset: 0
            verticalOffset: 0
            radius: 6
            color: "black"
        }

        Rectangle {
            id: contentBox
            color: "#40040d1c"
            width: parent.width
            implicitHeight: formLayout.implicitHeight + 20 + titleText.implicitHeight
            radius: 8

            Text {
                id: titleText
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 8
                font.pointSize: 12
                font.bold: true
                color: "white"
            }

            Row {
                id: formLayout
                anchors.top: titleText.bottom
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 10
                spacing: 40

                Grid {
                    id: leftGrid
                    columns: 2
                    spacing: 10
                    verticalItemAlignment: Grid.AlignVCenter
                }

                Grid {
                    id: rightGrid
                    columns: 2
                    spacing: 10
                    verticalItemAlignment: Grid.AlignVCenter
                }
            }
        }

        function addFormField(labelText, inputField, leftSide = true) {
            let grid = leftSide ? leftGrid : rightGrid;
            grid.addItem(Qt.createQmlObject(`
                    Text {
                        text: "` + labelText + `";
                        color: "white";
                    }
                    ${inputField}
            `, grid, "dynamicInput"));
        }
    }

