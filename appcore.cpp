#include "appcore.h"
#include <QMessageBox>

appcore::appcore(QObject *parent) : QObject(parent)
{    
    fiveBetGame = new fivebet();
    sevenBetGame = new sevenbet();
    weelBetGame = new weelbet();
    kenoBetGame = new kenobet();

    lotto_1 = new lottobet(1, this);
    lotto_2 = new lottobet(2, this);
    lotto_3 = new lottobet(3, this);
    lotto_4 = new lottobet(4, this);

    myBot = new bettingBot(this);

    connect(fiveBetGame, SIGNAL(sendDrawData(QString, int)), this, SIGNAL(sendDataToQML(QString, int)));
    connect(fiveBetGame, SIGNAL(sendResultToQML(int, int)), this, SIGNAL(sendResultToQML(int, int)));
    connect(fiveBetGame, SIGNAL(sendProgressStatus(double, QString)), this, SIGNAL(sendProgressStatus(double, QString)));
    connect(fiveBetGame, SIGNAL(signalToStartBetting(int)), this, SIGNAL(signalToStartBettingQML(int)));
    connect(fiveBetGame, SIGNAL(betsData(int, int, QString, int)), myBot, SLOT(makeBet(int, int, QString, int)));

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

    connect(lotto_1, SIGNAL(sendDrawData(QString, int)), this, SIGNAL(sendDataToQML(QString, int)));
    connect(lotto_1, SIGNAL(sendResultToQML(int, int)), this, SIGNAL(sendResultToQML(int, int)));
    connect(lotto_1, SIGNAL(signalToStartBetting(int)), this, SIGNAL(signalToStartBettingQML(int)));

    connect(lotto_2, SIGNAL(sendDrawData(QString, int)), this, SIGNAL(sendDataToQML(QString, int)));
    connect(lotto_2, SIGNAL(sendResultToQML(int, int)), this, SIGNAL(sendResultToQML(int, int)));
    connect(lotto_2, SIGNAL(signalToStartBetting(int)), this, SIGNAL(signalToStartBettingQML(int)));

    connect(lotto_3, SIGNAL(sendDrawData(QString, int)), this, SIGNAL(sendDataToQML(QString, int)));
    connect(lotto_3, SIGNAL(sendResultToQML(int, int)), this, SIGNAL(sendResultToQML(int, int)));
    connect(lotto_3, SIGNAL(signalToStartBetting(int)), this, SIGNAL(signalToStartBettingQML(int)));

    connect(lotto_4, SIGNAL(sendDrawData(QString, int)), this, SIGNAL(sendDataToQML(QString, int)));
    connect(lotto_4, SIGNAL(sendResultToQML(int, int)), this, SIGNAL(sendResultToQML(int, int)));
    connect(lotto_4, SIGNAL(signalToStartBetting(int)), this, SIGNAL(signalToStartBettingQML(int)));

}

bool appcore::isValidRow(const QString &str)
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

void appcore::gameChanged(const int &id)
{
    if (id == 7)
        sevenBetGame->sendDataToQML();
    else if (id == 6)
        fiveBetGame->sendDataToQML();
    else if (id == 2)
        weelBetGame->sendDataToQML();
    else if (id == 9)
        kenoBetGame->sendDataToQML();
    else if (id == 21)
        lotto_1->sendDataToQML();
    else if (id == 22)
        lotto_2->sendDataToQML();
    else if (id == 23)
        lotto_3->sendDataToQML();
    else if (id == 24)
        lotto_4->sendDataToQML();;

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
