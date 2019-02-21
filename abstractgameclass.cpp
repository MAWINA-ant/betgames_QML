#include "abstractgameclass.h"

abstractGameClass::abstractGameClass(quint8 id, quint16 intervalSec, QObject *parent) : QObject(parent),
                                                                                            gameIntervalSec(intervalSec),
                                                                                            gameId(id)
{
    //********************************************************************************
    // время почему-то смещено на 1 час
    // создаю менеджер работы с веб
    //********************************************************************************

    QDateTime dateTime = QDateTime::currentDateTime();
    dateTime.setTime(QTime(0,0,0));
    dateSeconds = dateTime.toSecsSinceEpoch();
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(siteAddress.arg(QString::number(dateSeconds),(QString::number(gameId)),(QString::number(currentPage))))));
    minuteTimer = new QTimer(this);
    connect(minuteTimer, SIGNAL(timeout()), this, SLOT(loadData()));
    minuteTimer->start(60000);
    //********************************************************************************
}

abstractGameClass::~abstractGameClass()
{

}

void abstractGameClass::loadData()
{
    int timeMinute = QTime::currentTime().minute();
    QDateTime dateTime = QDateTime::currentDateTime();
    dateTime.setTime(QTime(0,0,0));
    dateSeconds = dateTime.toSecsSinceEpoch();
    if (timeMinute % 3 == 2 && gameId == 6)
        manager->get(QNetworkRequest(QUrl(siteAddress.arg(QString::number(dateSeconds),(QString::number(gameId)),(QString::number(currentPage))))));
    else if (timeMinute % 3 == 0 && gameId == 7)
        manager->get(QNetworkRequest(QUrl(siteAddress.arg(QString::number(dateSeconds),(QString::number(gameId)),(QString::number(currentPage))))));
    else if (timeMinute % 3 == 1 && gameId == 2)
        manager->get(QNetworkRequest(QUrl(siteAddress.arg(QString::number(dateSeconds),(QString::number(gameId)),(QString::number(currentPage))))));
    if (timeMinute % 5 == 0 && gameId == 9)
        manager->get(QNetworkRequest(QUrl(siteAddress.arg(QString::number(dateSeconds),(QString::number(gameId)),(QString::number(currentPage))))));
}

void abstractGameClass::replyFinished(QNetworkReply *reply)
{
    // если нет соединени или нет данных или ошибка
    if (!reply->bytesAvailable() || reply->error()) {
        QMessageBox errorMessage;
        errorMessage.setText("Problem with connection to internet ");
        errorMessage.exec();
        return;
    }
    //************************************************
    gameData = reply->readAll();
    QJsonDocument documentJson = QJsonDocument::fromJson(gameData);
    if (pageCount == -1) {
        documentJsonList.clear();
        QJsonObject objectJson = documentJson.object().value(QString("results")).toObject();
        QJsonValue value = objectJson.value(QString("pageCount"));
        pageCount = qint8(value.toInt()); // узнаем кол-во страниц на сегодня
        if (pageCount < 10) {
            for (int i = 1; i <= pageCount; i++) {
                listURL.enqueue(siteAddress.arg(QString::number(dateSeconds),(QString::number(gameId)),(QString::number(i))));
            }
            for (int i = 1; i <= (10 - pageCount); i++) {
                listURL.enqueue(siteAddress.arg(QString::number(dateSeconds - 86400),(QString::number(gameId)),(QString::number(i))));
            }
        } else {
            for (int i = 1; i <= 10; i++) {
                listURL.enqueue(siteAddress.arg(QString::number(dateSeconds),(QString::number(gameId)),(QString::number(i))));
            }
        }
        if (!listURL.empty()) {
            manager->get(QNetworkRequest(QUrl(listURL.dequeue())));
            emit sendProgressStatus(currentPage * 1.0 / 10, "Загрузка данных " + QString(gameId == 2 ? "WEELBET" : gameId == 6 ? "5BET" : gameId == 9 ? "KENO" : "7BET"));
            currentPage++;
        }
    } else {
        if (!documentJsonList.contains(documentJson)) {
            documentJsonList.append(documentJson);
        }
        if (listURL.isEmpty()) {
            pageCount = -1;
            currentPage = 1;
            emit startGettingData();
            return;
        } else {
            manager->get(QNetworkRequest(QUrl(listURL.dequeue())));
            emit sendProgressStatus(currentPage * 1.0 / 10, "Загрузка данных " + QString(gameId == 2 ? "WEELBET" : gameId == 6 ? "5BET" : gameId == 9 ? "KENO" : "7BET"));
            currentPage++;
        }
    }
}

