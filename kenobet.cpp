#include "kenobet.h"

kenobet::kenobet() : abstractGameClass(9, 300)
{
    connect(this, SIGNAL(startGettingData()), this, SLOT(getDataFromSite()));
}

void kenobet::sendDataToQML()
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

void kenobet::parserJsonDocPage(QJsonDocument document)
{
    QJsonObject jsonObject = document.object().value("results").toObject();
    QJsonArray jsonArray = jsonObject["games"].toArray();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        if (obj["status"] == 5)
            continue;
        QJsonArray arrayResult = obj["result"].toArray();
        QList<QString> draw;
        foreach (const QJsonValue & val, arrayResult) {
            draw.append(val.toString());
        }
        drawList.append(draw);
    }
}

void kenobet::getDataFromSite()
{
    drawList.clear();
    drawListQML.clear();
    notFallOut.clear();
    foreach (QJsonDocument doc, documentJsonList) {
        parserJsonDocPage(doc);
    }
    for (int i = 0; i < drawList.size(); i++) {
        int sum = 0;
        QString draw = "";
        foreach (QString strNumber, drawList.at(i)) {
            int number = strNumber.toInt();
            sum += number;
            if (!notFallOut.contains(number)) {
                notFallOut.insert(number, i);
                if (i > 41)
                    emit signalToStartBetting(gameId);
            }
            draw.append(strNumber + " ");
        }
        QPair<QString, int> pair;
        pair.first = draw;
        pair.second = sum;
        drawListQML.append(pair);
    }
}
