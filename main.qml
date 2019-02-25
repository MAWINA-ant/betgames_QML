import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtMultimedia 5.9


ApplicationWindow {
    id: mainWindow
    visible: true
    width: 6 * oneBallsView.cellWidth
    height: 1000
    color: "lightgoldenrodyellow"
    title: qsTr("BetGames statistics")


    // номер розыгрыша
    property int number: 1
    property int gameId     // тип игры

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
            oneBallsModel.append({ball: numberBall, freqInRow: freqRow})
        }

        // прогресс получения статистики
        onSendProgressStatus: {
            progressText.text = progressGameType
            progressGetResult.value = progressStatus          
        }

        onSignalToStartBettingQML: {
            if (gameType == 2 && !button_weel.checked) {
                button_weel.myAnimation.start()
            } else if (gameType == 6 && !button_5_of_36.checked) {
                button_5_of_36.myAnimation.start()
            } else if (gameType == 7 && !button_7_of_42.checked) {
                button_7_of_42.myAnimation.start()
            } else if (gameType == 21 && !button_lotto3.checked) {
                button_lotto1.myAnimation.start()
            } else if (gameType == 22 && !button_lotto3.checked) {
                button_lotto2.myAnimation.start()
            } else if (gameType == 23 && !button_lotto3.checked) {
                button_lotto3.myAnimation.start()
            } else if (gameType == 24 && !button_lotto3.checked) {
                button_lotto4.myAnimation.start()
            }
            if (soundSwitch.checked)
                sirena.play()
        }
    }

    SwipeView {
        id: mainView

        currentIndex: 1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height - mainMenu.height

        Item {
            id: firstPage

            // компонент=делегат для отображения в GridView с вычислениями
            //*************************************************************
            Component {
                id: oneBallsDelegate

                Rectangle {
                    id: myFrame

                    property bool isChecked: false

                    color: mainWindow.color
                    width: oneBallsView.cellWidth
                    height: oneBallsView.cellHeight

                    radius: 5
                    border.width: 2
                    border.color: mainWindow.color

                    Component.onCompleted:
                        if ((freqInRow > 41 && gameId == 7) ||
                            (freqInRow > 43 && gameId == 6) ||
                            (freqInRow > 10 && gameId == 9) ||
                            (freqInRow > 119 && gameId == 2)||
                            (freqInRow > 119 && gameId == 23)) {
                            myAnimation.start()
                            if (soundSwitch.checked)
                                sirena.play()
                            myFrame.border.color = "black"
                        }

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
                        font.pointSize: 10
                        text: '<b>In a row:</b> ' + freqInRow
                        color: (freqInRow > 41 && gameId == 7) ? "red" :
                               (freqInRow > 43 && gameId == 6) ? "red" :
                               (freqInRow > 10 && gameId == 9) ? "red" :
                               (freqInRow > 119 && gameId == 2) ? "red" :
                               (freqInRow > 119 && gameId == 23) ? "red" : "black"
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if (!isChecked) {
                                color = "lightcyan"
                                border.color = "black"
                                isChecked = true
                            } else {
                                color = mainWindow.color
                                border.color = mainWindow.color
                                isChecked = false
                            }

                        }
                        onDoubleClicked: {
                            myAnimation.stop()
                            sirena.stop()
                            parent.border.color = mainWindow.color
                            color = mainWindow.color
                        }
                    }

                    PropertyAnimation {
                        id: myAnimation
                        loops: Animation.Infinite
                        target: myFrame

                        alwaysRunToEnd: true
                        property: "color"
                        from: "lightcyan"
                        to: mainWindow.color
                        duration: 1000
                    }

                }
            }
            //*************************************************************

            MyGridView {
                id: oneBallsView

                header: MyHeader {
                    headerText: "One ball"
                }
                delegate: oneBallsDelegate
                model: oneBallsModel
            }

            ListModel {
                id : oneBallsModel
            }
        }

        Item {
            id: secondPage

            Component {
                id: listResultsDelegate

                Item {
                    width: parent.width; height: myRow.height + 10

                    property var myArray : result.split(" ")

                    Text {
                        id: numberResults
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.margins: 5
                        width: 40
                        font.pointSize: 12
                        text: " " + num + " "
                    }
                    Row {
                        id: myRow
                        anchors.left: numberResults.right
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 5
                        Repeater {
                            model: gameId == 7 ? 7 : gameId == 6 ? 5 : gameId == 9 ? 20 : gameId == 21 ? 7 : gameId == 22 ? 5 : gameId == 24 ? 5 : 1
                            MyBall {
                                ballColor: gameId == 2 ? myArray[1] : ""
                                ballText: gameId == 2 ? myArray[0] : myArray[index] !== undefined ? myArray[index] : ""
                                idGame: gameId
                            }
                        }
                    }
                    Text {
                        id: summResult
                        anchors.left: myRow.right
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.margins: 5
                        font.pointSize: 12

                        color: (gameId == 7 && (summ > 200 || summ < 101)) ? "red" : (gameId == 7 && (summ > 175 || summ < 126)) ? "blue" : "black"

                        text: " " + (gameId == 2 ? "" : gameId == 23 ? "" : summ)
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
                    color: "lightcyan"
                    radius: 5
                    border.color: "black"
                    border.width: 2
                }
                highlightFollowsCurrentItem: true

                model: ListModel {
                    id : modelResults
                }

                delegate: listResultsDelegate
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
        height: 200

        //anchors.top: indicator.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        gradient: Gradient {
            GradientStop {position: 0; color: "paleturquoise"}
            GradientStop {position: 0.7; color: "lightskyblue"}
        }

        // строка с выбором игры и кол-вом дней выборки
        //**********************************************
        Grid {
            id: statisticsSettings
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5
            enabled: false

            MyRadioButton {
                id: button_weel
                text: qsTr("WEELBET")
                onCheckedChanged: {
                    if (checked) {
                        modelResults.clear()
                        oneBallsModel.clear()
                        number = 1
                        gameId = 2
                        appCore.gameChanged(gameId)
                        myAnimation.stop()
                    }
                }
            }

            MyRadioButton {
                id: button_5_of_36
                text: qsTr("5BET")
                onCheckedChanged: {
                    if (checked) {
                        modelResults.clear()
                        oneBallsModel.clear()
                        number = 1
                        gameId = 6
                        appCore.gameChanged(gameId)
                        myAnimation.stop()
                    }
                }
            }

            MyRadioButton {
                id: button_7_of_42
                text: qsTr("7BET")
                onCheckedChanged: {
                    if (checked) {
                        modelResults.clear()
                        oneBallsModel.clear()
                        number = 1
                        gameId = 7
                        appCore.gameChanged(gameId)
                        myAnimation.stop()
                    }
                }
            }

            MyRadioButton {
                id: button_keno
                text: qsTr("KENO")
                onCheckedChanged: {
                    if (checked) {
                        modelResults.clear()
                        oneBallsModel.clear()
                        number = 1
                        gameId = 9
                        appCore.gameChanged(gameId)
                        myAnimation.stop()
                    }
                }
            }

            MyRadioButton {
                id: button_lotto1
                text: qsTr("LOTTO_1")
                onCheckedChanged: {
                    if (checked) {
                        modelResults.clear()
                        oneBallsModel.clear()
                        number = 1
                        gameId = 21
                        appCore.gameChanged(gameId)
                        myAnimation.stop()
                    }
                }
            }

            MyRadioButton {
                id: button_lotto2
                text: qsTr("LOTTO_2")
                onCheckedChanged: {
                    if (checked) {
                        modelResults.clear()
                        oneBallsModel.clear()
                        number = 1
                        gameId = 22
                        appCore.gameChanged(gameId)
                        myAnimation.stop()
                    }
                }
            }

            MyRadioButton {
                id: button_lotto3
                text: qsTr("LOTTO_3")
                onCheckedChanged: {
                    if (checked) {
                        modelResults.clear()
                        oneBallsModel.clear()
                        number = 1
                        gameId = 23
                        appCore.gameChanged(gameId)
                        myAnimation.stop()
                    }
                }
            }

            MyRadioButton {
                id: button_lotto4
                text: qsTr("LOTTO_4")
                onCheckedChanged: {
                    if (checked) {
                        modelResults.clear()
                        oneBallsModel.clear()
                        number = 1
                        gameId = 24
                        appCore.gameChanged(gameId)
                        myAnimation.stop()
                    }
                }
            }

            CheckBox {
                id: soundSwitch
                text: qsTr("Звук")
            }
        }


        //**********************************************

        // показывает процесс загрузки страниц с сайта
        //*********************************************
        ProgressBar {
            id: progressGetResult
            height: 15
            value: 0.0

            anchors.top: statisticsSettings.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5

            background: Rectangle {
                color: "#e6e6e6"
                radius: 5
            }
            Text {
                id: progressText
                anchors.horizontalCenter: parent.horizontalCenter
            }
            contentItem: Rectangle {
                anchors.left: progressGetResult.left
                anchors.verticalCenter: progressGetResult.verticalCenter
                width: progressGetResult.visualPosition * progressGetResult.width
                height: progressGetResult.height
                radius: 5
                color: "#17a81a"

            }
            onValueChanged: {
                if (value == 0) {
                    statisticsSettings.enabled = false
                    progressText.text = ""
                }
                if (value == 1) {
                    progressText.text = "Загрузка статистики игры завершена"
                    statisticsSettings.enabled = true
                }
            }
        }
        //*********************************************

        // Строка с кнопками для получения результатов и подсчетов
        //*********************************************************
        Row {
            id: buttonsMenu
            anchors.top: progressGetResult.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5

            MyButton {
                id: buttonGetStat
                text: qsTr("Get statistics")
                onClicked: {
                    sirena.stop()
                    number = 1
                    progressGetResult.value = 0.0
                    appCore.receiveFromQMLGetData(countDaysOfStats.value)
                }
            }

            MyButton {
                id: buttonCompute
                text: qsTr("Quit")
                onClicked: {
                    mainWindow.close()
                }
            }
        }
        //*********************************************************
    }

    Audio {
        id: sirena
        source: "qrc:///sounds/00182.mp3"
    }

    // обновить отображение
    Timer {
            interval: 30000; running: true; repeat: true
            onTriggered: {
                modelResults.clear()
                oneBallsModel.clear()
                number = 1
                appCore.gameChanged(gameId)
            }
        }
}
