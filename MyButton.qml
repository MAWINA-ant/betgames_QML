import QtQuick 2.0
import QtQuick.Controls 2.1

Button {
    id: myButton
    width: parent.width / 2
    height: 50

    contentItem: Text {
         text: myButton.text
         font.pointSize: 20
         opacity: enabled ? 1.0 : 0.3
         color: myButton.down ? "#17a81a" : "red"
         horizontalAlignment: Text.AlignHCenter
         verticalAlignment: Text.AlignVCenter
         elide: Text.ElideRight
        }
    background: Rectangle {
         implicitWidth: 100
         implicitHeight: 50
         opacity: enabled ? 1 : 0.3
         border.color: myButton.down ? "#red" : "#17a81a"
         border.width: 1
         radius: 10
        }
}
