#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTextDocument>
#include <QTextDocumentFragment>
#include <QThread>

#include "fivebet.h"
#include "sevenbet.h"
#include "weelbet.h"
#include "kenobet.h"
#include "lottobet.h"

class appcore : public QObject
{
    Q_OBJECT

public:

    explicit appcore(QObject *parent = nullptr);

private:
    weelbet *weelBetGame;
    fivebet *fiveBetGame;
    sevenbet *sevenBetGame;
    kenobet *kenoBetGame;

    lottobet *lotto_1;
    lottobet *lotto_2;
    lottobet *lotto_3;
    //lottobet *lotto_4;

    bool isValidRow(QString str);

signals:
    void sendDataToQML(QString drawing, int summOfBalls);
    void sendResultToQML(int numberBall, int freqRow);
    void sendProgressStatus(double progressStatus, QString progressGameType);
    void signalToStartBettingQML(int gameType);

public slots:
    void gameChanged(int id);

    void replyFinished(QNetworkReply*);

};


#endif // APPCORE_H
