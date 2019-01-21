#include "weelbet.h"

weelbet::weelbet() : abstractGameClass (2, 180)
{
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

void weelbet::sendDataToQML()
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

void weelbet::getDataFromSite()
{
    drawList.clear();
    drawListQML.clear();
    notFallOut.clear();
    foreach (QJsonDocument doc, documentJsonList) {
        parserJsonDocPage(doc);
    }
    for (int i = 0; i < drawList.size(); i++) {
        QString draw = drawList.at(i).first + " " + drawList.at(i).second;

        if (!notFallOut.contains(drawList.at(i).first.toInt()))
            notFallOut.insert(drawList.at(i).first.toInt(), i);
        QPair<QString, int> pair;
        pair.first = draw;
        pair.second = 0;
        drawListQML.append(pair);
    }
}
