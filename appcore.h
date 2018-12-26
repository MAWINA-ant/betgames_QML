#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTextDocument>
#include <QTextDocumentFragment>
#include <QThread>

#include "abstractgameclass.h"

class appcore : public QObject
{
    Q_OBJECT

public:

    explicit appcore(QObject *parent = nullptr);

private:
    QString siteAddress;            // адрес сайта
    int versionOfGame;              // версия игры (7 из 42 или 5 из 36)
    int allPages = 0;                   // всего страниц
    int currentRequest = 0;
    QNetworkAccessManager *manager;
    QStringList parsedList;
    QStringList siteAdresses;
    QMap<int, int> frequencyInRow;
    QMap<int, int> frequencyAll;
    QHash<QString, int> frequencyInRowPair;

    bool isValidRow(QString str);

    QWebEngineView *view;

signals:
    void sendDataToQML(QString drawing, int summOfBalls);
    void sendResultToQML(int numberBall, int freqRow, int freqAll);
    void sendProgressStatus(double progressStatus);
    void semdPairResultToQML(QString pairBalls, int freqRow);

public slots:
    void receiveFromQMLGetData(int countDays);
    void receiveFromQMLCalculate();
    void gameChanged(int id);
    void replyFinished(QNetworkReply *reply);

    void loaded();
};


#endif // APPCORE_H
