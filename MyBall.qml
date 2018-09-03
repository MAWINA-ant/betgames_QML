import QtQuick 2.3

Rectangle {
    id: myBall
    property string ballText
    property string ballColor
    property int idGame

    width: 20
    height: 20
    radius: 10
    color: ballColor
    anchors.verticalCenter: parent.verticalCenter
    border.color: "black"
    border.width: 1
    Text {
        id: number
        text: ballText
        anchors.centerIn: parent
        onTextChanged: {
            setColor()
            color = (ballColor == "yellow" || ballColor == "white") ? "black" : "white"
        }
    }

    function setColor() {
        if (ballText == "") {
            ballColor = "grey"
        }
        if (idGame == 1) {
            if (ballText == "1" || ballText == "3" || ballText == "5" || ballText == "8" || ballText == "10" || ballText == "12" || ballText == "13" || ballText == "15"
                    || ballText == "17" || ballText == "20" || ballText == "22" || ballText == "24" || ballText == "26" || ballText == "27" || ballText == "29"
                    || ballText == "32" || ballText == "34" || ballText == "36" || ballText == "37" || ballText == "39" || ballText == "41") {
                ballColor = "yellow"
            } else if (ballText == "2" || ballText == "4" || ballText == "6" || ballText == "7" || ballText == "9" || ballText == "11" || ballText == "14" || ballText == "16"
                       || ballText == "18" || ballText == "19" || ballText == "21" || ballText == "23" || ballText == "25" || ballText == "28" || ballText == "30"
                       || ballText == "31" || ballText == "33" || ballText == "35" || ballText == "38" || ballText == "40" || ballText == "42") {
                ballColor = "black"
            }
        }
        else if (idGame == 3) {
            if (ballText == "1" || ballText == "2" || ballText == "3" || ballText == "4" || ballText == "5"
                    || ballText == "6" || ballText == "7" || ballText == "8" || ballText == "9" ) {
                ballColor = "white"
            } else if (ballText == "10" || ballText == "11" || ballText == "12" || ballText == "13" || ballText == "14"
                    || ballText == "15" || ballText == "16" || ballText == "17" || ballText == "18" ) {
                ballColor = "green"
            } else if (ballText == "19" || ballText == "20" || ballText == "21" || ballText == "22" || ballText == "23"
                    || ballText == "24" || ballText == "25" || ballText == "26" || ballText == "27" ) {
                ballColor = "red"
            } else if (ballText == "28" || ballText == "29" || ballText == "30" || ballText == "31" || ballText == "32"
                    || ballText == "33" || ballText == "34" || ballText == "35" || ballText == "36" ) {
                ballColor = "blue"
            }
        }
    }
}
