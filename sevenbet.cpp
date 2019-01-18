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

void sevenbet::sendDataToQML()
{
    for (int i = 0; i < drawListQML.size(); i ++) {
        emit sendDrawData(drawListQML.at(i).first, drawListQML.at(i).second);
    }
    QMapIterator<int, int> it(notFallOut);
    while (it.hasNext()) {
        it.next();
        emit sendResultToQML(it.key(), it.value());
    }
}

void sevenbet::getDataFromSite()
{
    qDebug() << documentJsonList.size();
    foreach (QJsonDocument doc, documentJsonList) {
        parserJsonDocPage(doc);
    }
    for (int i = 0; i < drawList.size(); i++) {
        int sum = 0;
        QString draw = "";
        foreach (QString strNumber, drawList.at(i)) {
            int number = strNumber.toInt();
            sum += number;
            if (!notFallOut.contains(number))
                notFallOut.insert(number, i);
            draw.append(strNumber + " ");
        }
        QPair<QString, int> pair;
        pair.first = draw;
        pair.second = sum;
        drawListQML.append(pair);
    }
}


