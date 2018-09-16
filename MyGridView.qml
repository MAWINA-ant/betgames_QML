import QtQuick 2.9

GridView {

    anchors.fill: parent
    cellHeight: 70
    cellWidth: 80

    opacity: Math.max(0.5, 1.0 - Math.abs(verticalOvershoot) / height)

    highlight: Rectangle {
        color: "lightcyan"
        radius: 5
        border.color: "black"
        border.width: 2
    }
}
