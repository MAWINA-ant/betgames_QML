#include "sevenbet.h"

sevenbet::sevenbet() : abstractGameClass(7, 180)
{
    manager->get(QNetworkRequest(QUrl(siteAddress)));
    connect(this, SIGNAL(startGettingData()), this, SLOT(getDataFromSite()));
}

void sevenbet::parserJsonDocPage(QJsonDocument document)
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

void sevenbet::getDataFromSite()
{
    foreach (QJsonDocument doc, documentJsonList) {
        parserJsonDocPage(doc);
    }
    for (int i = 0; i < drawList.size(); i++) {
        int sum = 0;
        QString draw = "";
        foreach (QString str, drawList.at(i)) {
            sum += str.toInt();
            draw.append(str + " ");
        }
        emit sendDrawData(draw, sum);
    }
}


