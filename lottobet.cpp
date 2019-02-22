#include "lottobet.h"

lottobet::lottobet(QObject *parent) : QObject(parent)
{


    QUrl url(urlString.arg("GetResult"));

    QNetworkRequest request(url);
    request.setRawHeader("Content-Type", "application/json");

    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    QByteArray array;
    array.append("{\"t1\":\"2019-2-20\",\"t\":180,\"sID\":3,\"c\":\"ru\",\"token\":\"389E9109-0B4D-4988-A71A-F96CA16A9993\"}");

    //manager->post(request, array);
}


/*void appcore::replyFinished(QNetworkReply *reply)
{
    // если нет соединени или нет данных или ошибка
    if (!reply->bytesAvailable() || reply->error()) {
        qDebug() << "Error!";
        return;
    }
s
    QByteArray gameData = reply->readAll();
    QJsonDocument documentJson = QJsonDocument::fromJson(gameData);
    QJsonObject jsonObject = documentJson.object();
    QJsonArray jsonArray = jsonObject.value("GetMagicResultResult").toArray();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        qDebug() << obj.value("Res").toString();
    }

    QFile fileOut("fileout.txt");
    if (fileOut.open(QIODevice::WriteOnly)) {
        fileOut.write(gameData);
        fileOut.close();
    }

    //qDebug() << gameData.size();
}*/
