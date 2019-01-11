#include "weelbet.h"

weelbet::weelbet() : abstractGameClass (2, 180)
{
    siteAddress += "&game_type=" + QString::number(gameId) + "&my=0";
    manager->get(QNetworkRequest(QUrl(siteAddress)));
    connect(this, SIGNAL(startGettingData()), this, SLOT(getDataFromSite()));
}

void weelbet::parserJsonDocPage(QJsonDocument document)
{
    QJsonObject jsonObject = document.object().value("results").toObject();
    QJsonArray jsonArray = jsonObject["games"].toArray();
    foreach (const QJsonValue & value, jsonArray) {
        QPair<QString, QString> draw;
        QJsonObject obj = value.toObject();
        draw.first = obj["result"].toObject()["number"].toString();
        draw.second = obj["result"].toObject()["color"].toString();
        drawList.append(draw);
    }
}

void weelbet::getDataFromSite()
{
    foreach (QJsonDocument doc, documentJsonList) {
        parserJsonDocPage(doc);
    }
    for (int i = 0; i < drawList.size(); i++) {

    }
}