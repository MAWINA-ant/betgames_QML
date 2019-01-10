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
    qint64 seconds = dateTime.toSecsSinceEpoch();
    siteAddress = "https://tvbetframe6.com/tvbet/getdata?action=filterResults&date=" + QString::number(seconds);
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    //********************************************************************************
}

abstractGameClass::~abstractGameClass()
{

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
        QJsonObject objectJson = documentJson.object().value(QString("results")).toObject();
        QJsonValue value = objectJson.value(QString("pageCount"));
        pageCount = quint8(value.toInt()); // узнаем кол-во страниц всего
        QString currentUrl = siteAddress + "&page=" + QString::number(currentPage) + "&clientId=1&lng=ru";
        manager->get(QNetworkRequest(QUrl(currentUrl)));
    } else {
        documentJsonList.append(documentJson);       
        if (currentPage > pageCount) {
            pageCount = 0;
            currentPage = 1;
            emit startGettingData();
            return;
        }
        QString currentUrl = siteAddress + "&page=" + QString::number(currentPage) + "&clientId=1&lng=ru";
        manager->get(QNetworkRequest(QUrl(currentUrl)));
        currentPage++;
    }
}

