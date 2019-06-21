#include "bettingbot.h"

bettingBot::bettingBot(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

void bettingBot::replyFinished(QNetworkReply *reply)
{
    QByteArray gameData = reply->readAll();
    QJsonDocument documentJson = QJsonDocument::fromJson(gameData);
    qDebug() << "Chto-to" << documentJson;
}

void bettingBot::makeBet(const int &number, const int &gameId, const QString &betId, const int &sum)
{
    QUrl url("");
    QNetworkRequest request(url);
    QString params = "";
    QByteArray postData;

    if (gameId == 6)
        postData.append(params.arg(sum).arg(62).arg(6.8).arg(number).arg(betId).arg(gameId));
    else if (gameId == 7)
        postData.append(params.arg(sum).arg(108).arg(5.7).arg(number).arg(betId).arg(gameId));
    request.setRawHeader("Content-Type", "application/json");
    manager->post(request, postData);

}
