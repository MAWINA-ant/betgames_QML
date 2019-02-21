#include "appcore.h"
#include <QMessageBox>

appcore::appcore(QObject *parent) : QObject(parent)
{
    fiveBetGame = new fivebet();
    sevenBetGame = new sevenbet();
    weelBetGame = new weelbet();
    kenoBetGame = new kenobet();

    connect(fiveBetGame, SIGNAL(sendDrawData(QString, int)), this, SIGNAL(sendDataToQML(QString, int)));
    connect(fiveBetGame, SIGNAL(sendResultToQML(int, int)), this, SIGNAL(sendResultToQML(int, int)));
    connect(fiveBetGame, SIGNAL(sendProgressStatus(double, QString)), this, SIGNAL(sendProgressStatus(double, QString)));
    connect(fiveBetGame, SIGNAL(signalToStartBetting(int)), this, SIGNAL(signalToStartBettingQML(int)));

    connect(sevenBetGame, SIGNAL(sendDrawData(QString, int)), this, SIGNAL(sendDataToQML(QString, int)));
    connect(sevenBetGame, SIGNAL(sendResultToQML(int, int)), this, SIGNAL(sendResultToQML(int, int)));
    connect(sevenBetGame, SIGNAL(sendProgressStatus(double, QString)), this, SIGNAL(sendProgressStatus(double, QString)));
    connect(sevenBetGame, SIGNAL(signalToStartBetting(int)), this, SIGNAL(signalToStartBettingQML(int)));

    connect(weelBetGame, SIGNAL(sendDrawData(QString, int)), this, SIGNAL(sendDataToQML(QString, int)));
    connect(weelBetGame, SIGNAL(sendResultToQML(int, int)), this, SIGNAL(sendResultToQML(int, int)));
    connect(weelBetGame, SIGNAL(sendProgressStatus(double, QString)), this, SIGNAL(sendProgressStatus(double, QString)));
    connect(weelBetGame, SIGNAL(signalToStartBetting(int)), this, SIGNAL(signalToStartBettingQML(int)));

    connect(kenoBetGame, SIGNAL(sendDrawData(QString, int)), this, SIGNAL(sendDataToQML(QString, int)));
    connect(kenoBetGame, SIGNAL(sendResultToQML(int, int)), this, SIGNAL(sendResultToQML(int, int)));
    connect(kenoBetGame, SIGNAL(sendProgressStatus(double, QString)), this, SIGNAL(sendProgressStatus(double, QString)));
    connect(kenoBetGame, SIGNAL(signalToStartBetting(int)), this, SIGNAL(signalToStartBettingQML(int)));
}

bool appcore::isValidRow(QString str)
{
    bool ok = true;
    QStringList strList = str.split(" ");
    strList.removeLast();
    foreach (QString num, strList) {
        num.toInt(&ok, 10);
        if (!ok)
            break;
    }
    if (strList.length() < 5)
        ok = false;
    return ok;
}

void appcore::gameChanged(int id)
{
    if (id == 7)
        sevenBetGame->sendDataToQML();
    else if (id == 6)
        fiveBetGame->sendDataToQML();
    else if (id == 2)
        weelBetGame->sendDataToQML();
    else if (id == 9)
        kenoBetGame->sendDataToQML();
}

void appcore::replyFinished(QNetworkReply *reply)
{
    // если нет соединени или нет данных или ошибка
    if (!reply->bytesAvailable() || reply->error()) {
        QMessageBox errorMessage;
        errorMessage.setText("Problem with connection to internet");
        errorMessage.exec();
        return;
    }
    //************************************************
    QByteArray arrayData = reply->readAll();
    qDebug() << QString(arrayData);
}
