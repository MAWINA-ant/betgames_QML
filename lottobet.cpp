#include "lottobet.h"

lottobet::lottobet(quint8 id, QObject *parent) : QObject(parent), gameId(id)
{
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    minuteTimer = new QTimer(this);
    connect(minuteTimer, SIGNAL(timeout()), this, SLOT(loadData()));
    minuteTimer->start(10000);
}

void lottobet::sendDataToQML()
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

void lottobet::parseData()
{
    drawListQML.clear();
    notFallOut.clear();
    if (gameId == 3) {
        for (int i = 0; i < drawList.size(); i++) {
            QString draw = drawList.at(i);

            if (!notFallOut.contains(drawList.at(i).toInt())) {
                notFallOut.insert(drawList.at(i).toInt(), i);
                if (i > 250)
                    emit signalToStartBetting(23);
            }
            QPair<QString, int> pair;
            pair.first = draw;
            pair.second = 0;
            drawListQML.append(pair);
        }
    } else {
        for (int i = 0; i < drawList.size(); i++) {
            int sum = 0;
            QString draw = "";
            foreach (QString strNumber, drawList.at(i).split(", ")) {
                int number = strNumber.toInt();
                sum += number;
                if (!notFallOut.contains(number)) {
                    notFallOut.insert(number, i);
                    if (i > 25 && gameId == 2){
                        emit signalToStartBetting(22);}
                    else if (i > 37 && gameId == 1)
                        emit signalToStartBetting(21);
                    else if (i > 100 && gameId == 4)
                        emit signalToStartBetting(24);
                }
                draw.append(strNumber + " ");
            }
            QPair<QString, int> pair;
            pair.first = draw;
            pair.second = sum;
            drawListQML.append(pair);
        }
    }
}


void lottobet::replyFinished(QNetworkReply *reply)
{
    // если нет соединени или нет данных или ошибка
    if (!reply->bytesAvailable() || reply->error()) {
        qDebug() << "Error! dostupno byte -> " << reply->bytesAvailable();
        qDebug() << reply->error();
        return;
    }
    QByteArray gameData = reply->readAll();
    QJsonDocument documentJson = QJsonDocument::fromJson(gameData);
    QJsonObject jsonObject = documentJson.object();
    QJsonArray jsonArray = jsonObject.value("GetMagicResultResult").toArray();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        int version = obj.value("GID").toInt();
        if (version == 3) {
            drawList.append(obj.value("Res").toString());
        } else if (version == 14) {
            drawList.append(obj.value("Res").toString());
        } else if (version == 17) {
            drawList.append(obj.value("Res").toString());
        } else if (version == 20) {
            drawList.append(obj.value("Res").toString());
        }
    }
    if (date == QDate::currentDate()) {
        QUrl url(urlString.arg("GetResult"));
        QNetworkRequest request(url);
        request.setRawHeader("Content-Type", "application/json");
        date = QDateTime::fromSecsSinceEpoch(QDateTime::currentDateTime().toSecsSinceEpoch() - 86400).date();
        QString stringDate = date.toString("yyyy-M-d");
        array.append(params.arg(stringDate).arg(gameId));
        manager->post(request, array);
    } else {
        parseData();
    }
}

void lottobet::loadData()
{
    drawList.clear();
    QUrl url(urlString.arg("GetResult"));
    QNetworkRequest request(url);
    request.setRawHeader("Content-Type", "application/json");
    date = QDate::currentDate();
    QString stringDate = date.toString("yyyy-M-d");
    array.append(params.arg(stringDate).arg(gameId));
    manager->post(request, array);
}
