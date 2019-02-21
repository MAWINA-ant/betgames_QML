#include "lottobet.h"

lottobet::lottobet(QObject *parent) : QObject(parent)
{
    QUrl url("https://amazon.betsfactory.net/RNGAPI/WidgetSupportService_v2/RNG_API.svc/GetResult");

    //QUrl url("https://tvbetframe6.com/tvbet/getdata/");
    //QUrl url("https://1xppbd.host/ru/user/auth/");
    QNetworkRequest request(url);

    request.setRawHeader("Content-Type", "application/json");

    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    QByteArray array;
    array.append("{\"t1\":\"2019-2-20\",\"t\":180,\"sID\":3,\"c\":\"ru\",\"token\":\"389E9109-0B4D-4988-A71A-F96CA16A9993\"}");
                 //"{\"t1\":\"2019-2-20\",\"t\":180,\"sID\":3,\"c\":\"ru\",\"token\":\"389E9109-0B4D-4988-A71A-F96CA16A9993\"}"
    //array.append("{\"amount\":\"10.00\",\"promocode\":\"\",\"events\":[{\"Type\":108,\"Coef\":5.7,\"Parameters\":[\"17\"],\"Game\":{\"Id\":70000243306,\"Type\":7}}],\"betType\":2,\"split\":0,\"acceptOdinar\":0,\"action\":\"placeBet\",\"tokenAuth\":\"5d7ad4058f10ab6e9cac11a94621aa0a\",\"clientId\":1,\"lng\":\"ru\"}");
    manager->post(request, array);
}


void appcore::replyFinished(QNetworkReply *reply)
{
    // если нет соединени или нет данных или ошибка
    if (!reply->bytesAvailable() || reply->error()) {
        qDebug() << "Error!";
        return;
    }
    //************************************************
    QByteArray gameData = reply->readAll();
    QJsonDocument documentJson = QJsonDocument::fromJson(gameData);
    QJsonObject jsonObject = documentJson.object();
    QJsonArray jsonArray = jsonObject.value("GetMagicResultResult").toArray();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        qDebug() << obj.value("Res").toString();
    }

    /*QFile fileOut("fileout.txt");
    if (fileOut.open(QIODevice::WriteOnly)) {
        fileOut.write(gameData);
        fileOut.close();
    }*/

    //qDebug() << gameData.size();
}
