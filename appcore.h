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
#include "bettingbot.h"

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
    lottobet *lotto_4;

    bettingBot *myBot;

    bool isValidRow(const QString &str);

signals:
    void sendDataToQML(const QString &drawing, const int &summOfBalls);
    void sendResultToQML(const int &numberBall, const int &freqRow);
    void sendProgressStatus(const double &progressStatus, const QString &progressGameType);
    void signalToStartBettingQML(const int &gameType);

public slots:
    void gameChanged(const int &id);

    void replyFinished(QNetworkReply*);

};


#endif // APPCORE_H
