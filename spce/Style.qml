pragma Singleton
import QtQuick

Item {
    readonly property string primary: "#253c7f"
    readonly property string buttonDefault: "#4984e8"
    readonly property string buttonHovered: "#3367dd"
    readonly property string buttonActive: "#2b54ca"
    readonly property string pageBackGround: "#f6f4fc"
    readonly property string titleTextColor: "#2a395a"
    readonly property string textColor: "#525d6e"
    readonly property string boxShadow: "#525d6e"
    readonly property string boxShadowActive: "#253c7f"
    readonly property var robotFont: robotoF.name

    FontLoader{
        id: robotoF
        source: "qrc:/fonts/fonts/Roboto-Regular.ttf"
    }
}
