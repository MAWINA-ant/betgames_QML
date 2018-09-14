import QtQuick 2.9

Rectangle {
    property string headerText

    width: parent.width
    height: 30
    gradient: Gradient {
        GradientStop {position: 0; color: "paleturquoise"}
        GradientStop {position: 0.7; color: "lightskyblue"}
    }
    Text {
        anchors.centerIn: parent
        color: "gray"
        text: headerText
        font.bold: true
        font.pointSize: 20
    }
}
