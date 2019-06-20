#ifndef LOTTOBET_H
#define LOTTOBET_H

#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <QDate>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class lottobet : public QObject
{
    Q_OBJECT
public:
    explicit lottobet(quint8 id, QObject *parent = nullptr);

private:
    QString urlString = "https://amazon.betsfactory.net/RNGAPI/WidgetSupportService_v2/RNG_API.svc/%1"; // %1 = функция АПИ (GetResult)
    QString params = "{\"t1\":\"%1\",\"t\":180,\"sID\":%2,\"c\":\"ru\",\"token\":\"389E9109-0B4D-4988-A71A-F96CA16A9993\"}"; // %1 = дата (гггг-м-дд)
                                                                                                                             // %2 = версия игры
    QByteArray array; // массив байт с параметрами запроса
    QDate date;       // дата для запроса (вчера и сегодня)

    QNetworkAccessManager *manager;
    QTimer *minuteTimer;
    quint8 gameId;

    QStringList drawList;
    QMap<int, int> notFallOut;
    QList<QPair<QString, int>> drawListQML;

public:
    void sendDataToQML();
    void parseData();

signals:
    void sendDrawData(const QString &, const int &);
    void sendResultToQML(const int &, const int &);
    void signalToStartBetting(const int &);

public slots:
    void replyFinished(QNetworkReply *reply);
    void loadData();
};

#endif // LOTTOBET_H
