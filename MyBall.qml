import QtQuick 2.9

Rectangle {
    property string ballText
    property string ballColor
    property int idGame

    width: 30
    height: 30
    radius: idGame == 2 ? 0 : 15
    color: ballColor
    border.color: "black"
    border.width: 1
    Text {
        id: number
        text: ballText
        anchors.centerIn: parent
        onTextChanged: {
            if (idGame != 2)
                setColor()
            color = (ballColor == "yellow" || ballColor == "white") ? "black" : "white"
        }
    }

    function setColor() {
        if (idGame == 7) {
            if (ballText % 2 == 0)
                ballColor = "blue"
            else
                ballColor = "black"
        } else if (idGame == 6) {
            if (ballText >= 1 && ballText <= 9)
                ballColor = "yellow"
            else if (ballText >= 10 && ballText <= 18)
                ballColor = "green"
            else if (ballText >= 19 && ballText <= 27)
                ballColor = "red"
            else if (ballText >= 28 && ballText <= 36)
                ballColor = "blue"
        } else if (idGame == 9) {
            ballColor = "red"
        } else if (idGame == 21) {

        } else if (idGame == 22) {
            if (ballText % 4 == 1)
                ballColor = "blue"
            else if (ballText % 4 == 2)
                ballColor = "black"
            else if (ballText % 4 == 3)
                ballColor = "red"
            else if (ballText % 4 == 0)
                ballColor = "pink"
        } else if (idGame == 23) {

        } else if (idGame == 24) {

        }
    }
}
