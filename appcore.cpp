#include "appcore.h"
#include <QMessageBox>

appcore::appcore(QObject *parent) : QObject(parent)
{
    //fivebet *fiveBetGame = new fivebet();
    sevenBetGame = new sevenbet();
    connect(sevenBetGame, SIGNAL(sendDrawData(QString, int)), this, SIGNAL(sendDataToQML(QString, int)));
    connect(sevenBetGame, SIGNAL(sendResultToQML(int, int)), this, SIGNAL(sendResultToQML(int, int)));
    connect(sevenBetGame, SIGNAL(sendProgressStatus(double, QString)), this, SIGNAL(sendProgressStatus(double, QString)));
    //weelbet *weelBetGame = new weelbet();
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
    qDebug() << id;
    sevenBetGame->sendDataToQML();
}
