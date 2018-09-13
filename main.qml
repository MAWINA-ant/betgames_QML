import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1


ApplicationWindow {
    visible: true
    width: 485
    height: 750
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
            modelResults.append({num: number++, result: drawing, summ: summOfBalls})
        }

        onSendResultToQML: {
            modelCalculate.append({ball: numberBall, freqInRow: freqRow, freqAll: freqAll})
        }

        // прогресс получения статистики
        onSendProgressStatus: {
            progressGetResult.value = progressStatus
        }
    }

    SwipeView {
        id: mainView

        currentIndex: 1
        //anchors.fill: parent
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height - 120

        Item {
            id: firstPage

            // компонент=делегат для отображения в GridView с вычислениями
            //*************************************************************
            Component {
                id: ballDelegate
                Item {
                    width: listCalculate.cellWidth
                    height: listCalculate.cellHeight

                    MyBall {
                        id: theBall
                        anchors.top: parent.top
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.margins: 5
                        ballText: ball
                        idGame: gameId
                    }

                    Text {
                        id: inRow
                        anchors.top: theBall.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.margins: 5
                        text: '<b>In a row:</b> ' + freqInRow
                        color: freqInRow > 15 ? "red" : "black"
                    }

                    Text {
                        id: allFreq
                        anchors.top: inRow.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.margins: 5
                        text: '<b>All times:</b> ' + freqAll
                        color: freqAll < (number / (statisticsSettings > 1 ? 7 : 6)) ? "green" : "black"
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            parent.GridView.view.currentIndex = index
                        }
                    }
                }
            }
            //*************************************************************
            GridView {
                id: listCalculate
                anchors.fill: parent
                cellHeight: 70
                cellWidth: 80

                opacity: Math.max(0.5, 1.0 - Math.abs(verticalOvershoot) / height)

                delegate: ballDelegate

                model: modelCalculate

                header: MyHeader {
                    headerText: "One ball"
                }

                highlight: Rectangle {
                    color: "skyblue"; radius: 5
                }
            }

            ListModel {
                id : modelCalculate
            }
        }

        Item {
            id: secondPage

            Component {
                id: listResultsDelegate

                Item {
                    width: parent.width; height: 30

                    Text {
                        id: numberResults
                        anchors.left: parent.Left
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.margins: 5
                        text: "№ " + num + "  "
                    }

                    MyBall {
                        id: ball_1
                        anchors.margins: 5
                        anchors.left: numberResults.right
                        anchors.verticalCenter: parent.verticalCenter
                        ballText: result.split(" ")[0] !== undefined ? result.split(" ")[0] : ""
                        idGame: gameId
                    }
                    MyBall {
                        id: ball_2
                        anchors.margins: 5
                        anchors.left: ball_1.right
                        anchors.verticalCenter: parent.verticalCenter
                        ballText: result.split(" ")[1] !== undefined ? result.split(" ")[1] : ""
                        idGame: gameId
                    }
                    MyBall {
                        id: ball_3
                        anchors.margins: 5
                        anchors.left: ball_2.right
                        anchors.verticalCenter: parent.verticalCenter
                        ballText: result.split(" ")[2] !== undefined ? result.split(" ")[2] : ""
                        idGame: gameId

                    }
                    MyBall {
                        id: ball_4
                        anchors.margins: 5
                        anchors.left: ball_3.right
                        anchors.verticalCenter: parent.verticalCenter
                        ballText: result.split(" ")[3] !== undefined ? result.split(" ")[3] : ""
                        idGame: gameId
                    }
                    MyBall {
                        id: ball_5
                        anchors.margins: 5
                        anchors.left: ball_4.right
                        anchors.verticalCenter: parent.verticalCenter
                        ballText: result.split(" ")[4] !== undefined ? result.split(" ")[4] : ""
                        idGame: gameId
                    }
                    MyBall {
                        id: ball_6
                        anchors.margins: 5
                        anchors.left: ball_5.right
                        anchors.verticalCenter: parent.verticalCenter
                        ballText: result.split(" ")[5] !== undefined ? result.split(" ")[5] : ""
                        idGame: gameId
                        visible: (idGame == 1) ? true : false

                    }
                    MyBall {
                        id: ball_7
                        anchors.margins: 5
                        anchors.left: ball_6.right
                        anchors.verticalCenter: parent.verticalCenter
                        ballText: result.split(" ")[6] !== undefined ? result.split(" ")[6] : ""
                        idGame: gameId
                        visible: (idGame == 1) ? true : false
                    }

                    Text {
                        id: summResult
                        anchors.left: ball_7.right
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.margins: 5
                        text: "Summ " + summ + "  "
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            parent.ListView.view.currentIndex = index
                        }
                    }

                }
            }

            ListView {
                id: listResults
                anchors.fill: parent

                header: MyHeader {
                    headerText: "All statistics"
                }
                highlight: Rectangle {
                    color: "skyblue"
                }
                highlightFollowsCurrentItem: true

                model: ListModel {
                    id : modelResults
                }

                delegate: listResultsDelegate
            }
        }

        Item {
            id: thirdPage
            Rectangle {
                anchors.fill: parent
                color: "blue"
            }
        }
    }

    PageIndicator {
        id: indicator

        count: mainView.count
        currentIndex: mainView.currentIndex

        anchors.bottom: mainView.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle {
        id: mainMenu

        anchors.top: indicator.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        gradient: Gradient {
            GradientStop {position: 0; color: "gray"}
            GradientStop {position: 0.7; color: "black"}
        }

        // строка с выбором игры и кол-вом дней выборки
        //**********************************************
        Row {
            id: statisticsSettings
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5

            RadioButton {
                id: button_7_of_42
                width: parent.width / 4
                text: qsTr("7 out of 42")
                checked: true
                onCheckedChanged: {
                    if (button_7_of_42.checked == true) {
                        gameId = 1
                        button_6_of_36.checked = false
                    }
                    appCore.gameChanged(gameId)
                    modelResults.clear()
                    modelCalculate.clear()
                    progressGetResult.value = 0.0
                }
            }

            RadioButton {
                id: button_6_of_36
                width: parent.width / 4
                text: qsTr("5 out of 36")
                onCheckedChanged: {
                    if (button_6_of_36.checked == true) {
                        gameId = 3
                        button_7_of_42.checked = false
                    }
                    appCore.gameChanged(gameId)
                    modelResults.clear()
                    modelCalculate.clear()
                    progressGetResult.value = 0.0
                }
            }

            Text {
                id: countDaysLabel
                width: parent.width / 4
                text: qsTr("Days of statistics: ")
                anchors.verticalCenter: parent.verticalCenter
            }

            SpinBox {
                id: countDaysOfStats
                width: parent.width / 4
                value: 1
                from: 1
                to: 365
            }
        }
        //**********************************************

        // показывает процесс загрузки страниц с сайта
        //*********************************************
        ProgressBar {
            id: progressGetResult
            height: 25
            anchors.top: statisticsSettings.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5
        }
        //*********************************************

        // Строка с кнопками для получения результатов и подсчетов
        //*********************************************************
        Row {
            id: buttonsMenu
            height: 30
            anchors.top: progressGetResult.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5

            Button {
                id: buttonGetStat
                width: parent.width / 2
                height: 30
                text: qsTr("Get statistics")

                onClicked: {
                    modelResults.clear()
                    modelCalculate.clear()
                    number = 1
                    progressGetResult.value = 0.0
                    appCore.receiveFromQMLGetData(countDaysOfStats.value)
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
        //*********************************************************
    }
}
