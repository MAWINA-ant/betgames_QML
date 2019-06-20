#include "sevenbet.h"

sevenbet::sevenbet() : abstractGameClass(7, 180)
{
    connect(this, SIGNAL(startGettingData()), this, SLOT(getDataFromSite()));
}

void sevenbet::parserJsonDocPage(const QJsonDocument &document)
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

int sevenbet::getSum(const int &count, const betVariant &var)
{
    switch (var) {

    case SOLO:
        if (count >= 40 && count <= 41)
            return 10;
        else if (count >= 42 && count <= 43)
            return 10;
        else if (count >= 44 && count <= 45)
            return 20;
        else if (count >= 46 && count <= 47)
            return 30;
        else if (count >= 48 && count <= 49)
            return 50;
        else if (count >= 50 && count <= 51)
            return 80;
        else if (count >= 52 && count <= 53)
            return 130;
        else if (count >= 54 && count <= 55)
            return 210;
        else if (count >= 56 && count <= 57)
            return 340;
        else if (count >= 58 && count <= 59)
            return 550;
        else if (count >= 60 && count <= 61)
            return 890;
        else if (count >= 62 && count <= 63)
            return 1540;
        else if (count >= 64 && count <= 65)
            return 2430;
        else if (count >= 66 && count <= 67)
            return 3970;
        else
            return 0;

        break;

    case DUET:
        if (count == 31)
            return 10;
        else if (count == 32)
            return 10;
        else if (count == 33)
            return 20;
        else if (count == 34)
            return 30;
        else if (count == 35)
            return 50;
        else if (count == 36)
            return 80;
        else if (count == 37)
            return 130;
        else if (count == 38)
            return 210;
        else if (count == 39)
            return 340;
        else if (count == 40)
            return 550;
        else if (count == 41)
            return 890;
        else if (count == 42)
            return 1540;
        else if (count == 43)
            return 2430;

        break;

    case TRIO:
        if (count == 23)
            return 10;
        else if (count == 24)
            return 30;
        else if (count == 25)
            return 60;
        else if (count == 26)
            return 150;
        else if (count == 27)
            return 300;
        else if (count == 28)
            return 750;
        else if (count == 29)
            return 1500;
        else if (count == 30)
            return 3000;
        else if (count == 31)
            return 7500;

        break;
    }

}

void sevenbet::getDataFromSite()
{
    drawList.clear();
    drawListQML.clear();
    notFallOut.clear();
    duet.clear();
    trio.clear();

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
                if (i > 39) {
                    emit signalToStartBetting(gameId);
                    emit betsData(number, 7, idGameForBet, getSum(i, SOLO));
                }
                if (i > 30) {
                    duet.append(number);
                    duet.append(i);
                }
                if (duet.size() == 4) {
                    int min = duet.at(1);
                    if (duet.at(3) < min)
                        min = duet.at(3);
                    for(int j = 0; j < 4; j += 2)
                        qDebug() << "";
                        //emit betsData(duet.at(i), 7, idGameForBet, getSum(min, DUET));
                }
                if (i > 22) {
                    trio.append(number);
                    trio.append(i);
                }
                if (trio.size() == 6) {
                    int min = duet.at(1);
                    if (trio.at(3) < min)
                        min = trio.at(3);
                    if (trio.at(5) < min)
                        min = trio.at(5);
                    for(int j = 0; j < 6; j += 2)
                        qDebug() << "";
                        //emit betsData(trio.at(i), 7, idGameForBet, getSum(min, TRIO));
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


