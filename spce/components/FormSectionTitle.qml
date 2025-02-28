import QtQuick
import QtQuick.Controls
import ".."

Item {
    property alias text: title.text
    width: title.implicitWidth
    height: title.implicitHeight
    Text {
        id: title
        font.pointSize: 13
        font.family: Style.robotFont
        color: Style.titleTextColor
        horizontalAlignment: Text.AlignHCenter
    }
}
