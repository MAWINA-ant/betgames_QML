import QtQuick 2.0
import QtQuick.Controls 2.1

RadioButton {

    id: thisButton
    property PropertyAnimation myAnimation

    PropertyAnimation {
        id: myAnimation
        loops: Animation.Infinite
        target: thisButton

        alwaysRunToEnd: true
        property: "opacity"
        from: 0
        to: 1
        duration: 1000
    }
    myAnimation: myAnimation
}
