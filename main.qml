import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 480
    height: 480
    title: qsTr("BetGames statistics")

    // номер розыгрыша
    property int number: 1

    // задаём размещение кнопок получения результатов и вычислений
    Row {
        id: buttonsMenu
        height: 30
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5

        Button {
            id: buttonGetStat
            width: parent.width / 2
            height: 30
            text: qsTr("Get statistics")

            onClicked: {
                myModel.append({num: number++, result: "1,2,3,4,5,6,7", summ: "213"})
            }
        }

        Button {
            id: buttonCompute
            width: parent.width / 2
            height: 30
            text: qsTr("Compute")

            onClicked: {

            }
        }

    }

    TableView {
        id: tableResults
        anchors.top: buttonsMenu.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5

        rowDelegate: Component {
            Rectangle {
                height: 21

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
            role: "num"
            title: "№"
            width: 40
        }

        TableViewColumn {
            role: "result"
            title: "Result"
            width: 180

            delegate: Item {
                anchors.fill: parent

                MyBall {
                    id: ball_1
                    anchors.margins: 5
                    anchors.left: parent.left
                    ballText: styleData.value.split(",")[0]
                }
                MyBall {
                    id: ball_2
                    anchors.margins: 5
                    anchors.left: ball_1.right
                    ballText: styleData.value.split(",")[1]
                }
                MyBall {
                    id: ball_3
                    anchors.margins: 5
                    anchors.left: ball_2.right
                    ballText: styleData.value.split(",")[2]
                }
                MyBall {
                    id: ball_4
                    anchors.margins: 5
                    anchors.left: ball_3.right
                    ballText: styleData.value.split(",")[3]
                }
                MyBall {
                    id: ball_5
                    anchors.margins: 5
                    anchors.left: ball_4.right
                    ballText: styleData.value.split(",")[4]
                }
                MyBall {
                    id: ball_6
                    anchors.margins: 5
                    anchors.left: ball_5.right
                    ballText: styleData.value.split(",")[5]
                }
                MyBall {
                    id: ball_7
                    anchors.margins: 5
                    anchors.left: ball_6.right
                    ballText: styleData.value.split(",")[6]
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
}
