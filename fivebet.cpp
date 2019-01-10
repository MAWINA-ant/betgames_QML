#include "fivebet.h"

fivebet::fivebet() : abstractGameClass(6, 180)
{
    siteAddress += "&game_type=6&my=0";
    manager->get(QNetworkRequest(QUrl(siteAddress)));
    connect(this, SIGNAL(startGettingData()), this, SLOT(getDataFromSite()));
}

void fivebet::getDataFromSite()
{
    foreach (QJsonDocument doc, documentJsonList) {
        parserJsonDocPage(doc);
    }
}

void fivebet::parserJsonDocPage(QJsonDocument document)
{
    long long i = 1;
    QJsonObject jsonObject = document.object().value("results").toObject();
    QJsonArray jsonArray = jsonObject["games"].toArray();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        QJsonArray arrayResult = obj["result"].toArray();
        foreach (const QJsonValue & val, arrayResult) {
            QJsonObject object = val.toObject();
            qDebug() << "Nomer " << i++ << " " << object["number"].toString().toInt();
        }
    }
}

