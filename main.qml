import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 480
    height: 480
    title: qsTr("BetGames statistics")

    // номер розыгрыша
    property int number: 1
    property int gameId: 1     // тип игры

    /* С помощью объекта Connections
         * Устанавливаем соединение с классом ядра приложения
         * */
    Connections {
        target: appCore // Указываем целевое соединение
        /* Объявляем и реализуем функцию, как параметр
             * объекта и с имененем похожим на название сигнала
             * Разница в том, что добавляем в начале on и далее пишем
             * с заглавной буквы
             * */

        onSendDataToQML: {
            myModel.append({num: number++, result: drawing, summ: summOfBalls})
        }

        onSendResultToQML: {
            modelCalculate.append({ball: numberBall, freqInRow: freqRow, freqAll: freqAll})
        }

        // прогресс получения статистики
        onSendProgressStatus: {
            progressGetResult.value = progressStatus
        }
    }

    Column {
        id: menu
        height: 90
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        Row {
            id: gameChoice
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5

            RadioButton {
                id: button_7_of_42
                width: parent.width / 2
                text: qsTr("7 out of 42")
                checked: true
                onCheckedChanged: {
                    if (button_7_of_42.checked == true) {
                        gameId = 1
                        button_6_of_36.checked = false
                    }
                    appCore.gameChanged(gameId)
                    myModel.clear()
                    modelCalculate.clear()
                    progressGetResult.value = 0.0
                }
            }

            RadioButton {
                id: button_6_of_36
                width: parent.width / 2
                text: qsTr("5 out of 36")
                onCheckedChanged: {
                    if (button_6_of_36.checked == true) {
                        gameId = 3
                        button_7_of_42.checked = false
                    }
                    appCore.gameChanged(gameId)
                    myModel.clear()
                    modelCalculate.clear()
                    progressGetResult.value = 0.0
                }
            }
        }
        // задаём размещение кнопок получения результатов и вычислений
        Row {
            id: buttonsMenu
            height: 30
            anchors.top: gameChoice.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5

            Button {
                id: buttonGetStat
                width: parent.width / 2
                height: 30
                text: qsTr("Get statistics")

                onClicked: {
                    myModel.clear()
                    number = 1
                    appCore.receiveFromQMLGetData()
                }
            }

            Button {
                id: buttonCompute
                width: parent.width / 2
                height: 30
                text: qsTr("Compute")

                onClicked: {
                    modelCalculate.clear()
                    appCore.receiveFromQMLCalculate()
                }
            }
        }

        ProgressBar {
            id: progressGetResult
            height: 25
            anchors.top: buttonsMenu.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5
            //value: statusGetData
        }
    }

    TableView {
        id: tableResults
        anchors.top: menu.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5
        height: parent.height / 2

        rowDelegate: Component {
            Rectangle {
                height: 24

                Behavior on height{ NumberAnimation{} }

                color: styleData.selected ? "#448" : (styleData.alternate? "#eee" : "#fff")
                BorderImage{
                    id: selected
                    anchors.fill: parent
                    visible: styleData.selected
                    border{left:2; right:2; top:2; bottom:2}
                    SequentialAnimation {
                        running: true; loops: Animation.Infinite
                        NumberAnimation { target:selected; property: "opacity"; to: 1.0; duration: 900}
                        NumberAnimation { target:selected; property: "opacity"; to: 0.5; duration: 900}
                    }
                }
            }
        }
        TableViewColumn {
            role: "num"
            title: "№"
            width: 40
        }

        TableViewColumn {
            role: "result"
            title: "Result"
            width: (gameId == 1) ? 180 : 130

            delegate: Item {
                property var arrayOfNumber : styleData.value.split(" ")
                MyBall {
                    id: ball_1
                    anchors.margins: 5
                    anchors.left: parent.left
                    ballText: arrayOfNumber[0]
                    idGame: gameId
                }
                MyBall {
                    id: ball_2
                    anchors.margins: 5
                    anchors.left: ball_1.right
                    ballText: arrayOfNumber[1]
                    idGame: gameId
                    onBallTextChanged: {console.log("arrayOfNumber[1]" + arrayOfNumber[1]);}

                }
                MyBall {
                    id: ball_3
                    anchors.margins: 5
                    anchors.left: ball_2.right
                    ballText: arrayOfNumber[2]
                    idGame: gameId

                }
                MyBall {
                    id: ball_4
                    anchors.margins: 5
                    anchors.left: ball_3.right
                    ballText: arrayOfNumber[3]
                    idGame: gameId
                }
                MyBall {
                    id: ball_5
                    anchors.margins: 5
                    anchors.left: ball_4.right
                    ballText: arrayOfNumber[4]
                    idGame: gameId
                }
                MyBall {
                    id: ball_6
                    anchors.margins: 5
                    anchors.left: ball_5.right
                    ballText: arrayOfNumber[5]
                    idGame: gameId
                    visible: (idGame == 1) ? true : false

                }
                MyBall {
                    id: ball_7
                    anchors.margins: 5
                    anchors.left: ball_6.right
                    ballText: arrayOfNumber[6]
                    idGame: gameId
                    visible: (idGame == 1) ? true : false
                }
            }
        }

        TableViewColumn {
            role: "summ"
            title: "Summ"
        }

        model: ListModel {
            id : myModel
        }
    }

    Text {
        id: label
        anchors.top: tableResults.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        height: 20
        text: qsTr("Высчитаные ожидания:")
    }

    TableView {
        id: tableCalculate
        anchors.top: label.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 5

        rowDelegate: Component {
            Rectangle {
                height: 24

                Behavior on height{ NumberAnimation{} }

                color: styleData.selected ? "#448" : (styleData.alternate? "#eee" : "#fff")
                BorderImage{
                    id: selected
                    anchors.fill: parent
                    //source: "../images/selectedrow.png"
                    visible: styleData.selected
                    border{left:2; right:2; top:2; bottom:2}
                    SequentialAnimation {
                        running: true; loops: Animation.Infinite
                        NumberAnimation { target:selected; property: "opacity"; to: 1.0; duration: 900}
                        NumberAnimation { target:selected; property: "opacity"; to: 0.5; duration: 900}
                    }
                }
            }
        }
        TableViewColumn {
            role: "ball"
            title: "Ball"
            width: 30

            delegate: Item {
                MyBall {
                    id: ball_calculate
                    anchors.margins: 5
                    anchors.horizontalCenter: parent.horizontalCenter
                    ballText: styleData.value
                    idGame: gameId
                }
            }
        }

        TableViewColumn {
            role: "freqInRow"
            title: "Frequancy in a row"
            width: 100
            horizontalAlignment: Text.AlignHCenter
        }

        TableViewColumn {
            role: "freqAll"
            title: "Frequancy all"
            width: 80
            horizontalAlignment: Text.AlignHCenter
        }

        model: ListModel {
            id : modelCalculate
        }
    }
}
