#include "fivebet.h"

fivebet::fivebet() : abstractGameClass(6, 180)
{
    connect(this, SIGNAL(startGettingData()), this, SLOT(getDataFromSite()));
}

void fivebet::parserJsonDocPage(const QJsonDocument &document)
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
            QJsonObject object = val.toObject();
            draw.append(object["number"].toString());
        }
        drawList.append(draw);
    }
}

void fivebet::sendDataToQML()
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

int fivebet::getSum(const int &count)
{
    if (count >= 60 && count <= 62)
        return 10;
    else if (count >= 63 && count <= 65)
        return 10;
    else if (count >= 66 && count <= 68)
        return 20;
    else if (count >= 69 && count <= 71)
        return 40;
    else if (count >= 72 && count <= 74)
        return 80;
    else if (count >= 75 && count <= 77)
        return 160;
    else if (count >= 78 && count <= 81)
        return 320;
    else if (count >= 82 && count <= 84)
        return 640;
    else if (count >= 85 && count <= 87)
        return 1280;
    else if (count >= 88 && count <= 90)
        return 2560;
    else if (count >= 91 && count <= 93)
        return 5120;
    else
        return 0;
}

void fivebet::getDataFromSite()
{
    drawList.clear();
    drawListQML.clear();
    notFallOut.clear();

    //**************
    QJsonObject jsonObject = documentJsonList.at(0).object().value("results").toObject();
    QJsonArray jsonArray = jsonObject["games"].toArray();
    QJsonObject obj = jsonArray.at(0).toObject();
    QString idGameForBet = static_cast<QVariant>(obj["id"].toDouble() + 1).toString();
    //*************

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
                if (i > 59) {
                    emit signalToStartBetting(gameId);
                    emit betsData(number, 6, idGameForBet, getSum(i));
                }
            }
            draw.append(strNumber + " ");
        }
        QPair<QString, int> pair;
        pair.first = draw;
        pair.second = sum;
        drawListQML.append(pair);
    }
}



