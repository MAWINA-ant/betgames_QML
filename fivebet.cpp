#include "fivebet.h"

fivebet::fivebet() : abstractGameClass(6, 180)
{
    siteAddress = siteAddress.arg(QString::number(dateSeconds)).arg(QString::number(gameId)).arg(QString::number(currentPage));
    manager->get(QNetworkRequest(QUrl(siteAddress)));
    connect(this, SIGNAL(startGettingData()), this, SLOT(getDataFromSite()));
}

void fivebet::parserJsonDocPage(QJsonDocument document)
{
    QJsonObject jsonObject = document.object().value("results").toObject();
    QJsonArray jsonArray = jsonObject["games"].toArray();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        QJsonArray arrayResult = obj["result"].toArray();
        QList<QString> draw;
        foreach (const QJsonValue & val, arrayResult) {
            QJsonObject object = val.toObject();
            draw.append(object["number"].toString());
        }
        drawList.append(draw);
    }
}

void fivebet::sendDataToQML()
{

}

void fivebet::getDataFromSite()
{
    foreach (QJsonDocument doc, documentJsonList) {
        parserJsonDocPage(doc);
    }
}



