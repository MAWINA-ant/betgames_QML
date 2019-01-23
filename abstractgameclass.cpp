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
    qDebug() << dateTime;
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
    if (timeMinute % 3 == 1 && gameId == 6)
        manager->get(QNetworkRequest(QUrl(siteAddress.arg(QString::number(dateSeconds),(QString::number(gameId)),(QString::number(currentPage))))));
    else if (timeMinute % 3 == 2 && gameId == 7)
        manager->get(QNetworkRequest(QUrl(siteAddress.arg(QString::number(dateSeconds),(QString::number(gameId)),(QString::number(currentPage))))));
    else if (timeMinute % 3 == 0 && gameId == 2)
        manager->get(QNetworkRequest(QUrl(siteAddress.arg(QString::number(dateSeconds),(QString::number(gameId)),(QString::number(currentPage))))));
}

void abstractGameClass::replyFinished(QNetworkReply *reply)
{
    // если нет соединени или нет данных или ошибка
    if (!reply->bytesAvailable() || reply->error()) {
        QMessageBox errorMessage;
        errorMessage.setText("Problem with connection to internet");
        errorMessage.exec();
        return;
    }
    //************************************************
    gameData = reply->readAll();
    QJsonDocument documentJson = QJsonDocument::fromJson(gameData);
    if (pageCount == 0){
        documentJsonList.clear();
        QJsonObject objectJson = documentJson.object().value(QString("results")).toObject();
        QJsonValue value = objectJson.value(QString("pageCount"));
        pageCount = quint8(value.toInt()); // узнаем кол-во страниц на сегодня
        if (pageCount < 4) {
            for (int i = 1; i < pageCount; i++) {
                listURL.enqueue(siteAddress.arg(QString::number(dateSeconds),(QString::number(gameId)),(QString::number(i))));
            }
            for (int i = 1; i < (5 - pageCount); i++) {
                listURL.enqueue(siteAddress.arg(QString::number(dateSeconds - 86400),(QString::number(gameId)),(QString::number(i))));
            }
        } else {
            for (int i = 1; i < (gameId == 2 ? pageCount : 6); i++) {
                listURL.enqueue(siteAddress.arg(QString::number(dateSeconds),(QString::number(gameId)),(QString::number(i))));
            }
        }
        if (!listURL.empty()) {
            manager->get(QNetworkRequest(QUrl(listURL.dequeue())));
            currentPage++;
        }
    } else {
        if (!documentJsonList.contains(documentJson)) {
            documentJsonList.append(documentJson);
            emit sendProgressStatus(currentPage * 1.0 / 5, (gameId == 6 ? "5 из 36" : gameId == 2 ? "Колесо" : "7 из 42"));
        }
        if (listURL.isEmpty()) {
            pageCount = 0;
            currentPage = 1;
            emit startGettingData();
            return;
        } else {
            manager->get(QNetworkRequest(QUrl(listURL.dequeue())));
            currentPage++;
        }
    }
}

