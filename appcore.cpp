#include "appcore.h"
#include <QMessageBox>

appcore::appcore(QObject *parent) : QObject(parent)
{
    fiveBetGame = new fivebet();
    connect(fiveBetGame, SIGNAL(sendDrawData(QString, int)), this, SIGNAL(sendDataToQML(QString, int)));
    connect(fiveBetGame, SIGNAL(sendResultToQML(int, int)), this, SIGNAL(sendResultToQML(int, int)));
    connect(fiveBetGame, SIGNAL(sendProgressStatus(double, QString)), this, SIGNAL(sendProgressStatus(double, QString)));

    sevenBetGame = new sevenbet();
    connect(sevenBetGame, SIGNAL(sendDrawData(QString, int)), this, SIGNAL(sendDataToQML(QString, int)));
    connect(sevenBetGame, SIGNAL(sendResultToQML(int, int)), this, SIGNAL(sendResultToQML(int, int)));
    connect(sevenBetGame, SIGNAL(sendProgressStatus(double, QString)), this, SIGNAL(sendProgressStatus(double, QString)));

    weelBetGame = new weelbet();
    connect(weelBetGame, SIGNAL(sendDrawData(QString, int)), this, SIGNAL(sendDataToQML(QString, int)));
    connect(weelBetGame, SIGNAL(sendResultToQML(int, int)), this, SIGNAL(sendResultToQML(int, int)));
    connect(weelBetGame, SIGNAL(sendProgressStatus(double, QString)), this, SIGNAL(sendProgressStatus(double, QString)));
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

}
