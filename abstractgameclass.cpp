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
        QString currentUrl = siteAddress.arg(QString::number(dateSeconds),(QString::number(gameId)),(QString::number(currentPage)));
        manager->get(QNetworkRequest(QUrl(currentUrl)));
    } else {
        documentJsonList.append(documentJson);       
        if (currentPage > pageCount) {
            pageCount = 0;
            currentPage = 1;
            emit startGettingData();
            return;
        }
        QString currentUrl = siteAddress.arg(QString::number(dateSeconds),(QString::number(gameId)),(QString::number(currentPage)));
        qDebug() << currentUrl;
        manager->get(QNetworkRequest(QUrl(currentUrl)));
        currentPage++;
    }
}

