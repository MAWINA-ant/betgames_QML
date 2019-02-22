#ifndef LOTTOBET_H
#define LOTTOBET_H

#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

class lottobet : public QObject
{
    Q_OBJECT
public:
    explicit lottobet(QObject *parent = nullptr);

private:
    QString urlString = "https://amazon.betsfactory.net/RNGAPI/WidgetSupportService_v2/RNG_API.svc/%1"; // %1 = функция АПИ (GetResult)
    QString params = "{\"t1\":\"%1\",\"t\":180,\"sID\":%2,\"c\":\"ru\",\"token\":\"389E9109-0B4D-4988-A71A-F96CA16A9993\"}"; // %1 = дата (гггг-м-дд)
                                                                                                                             // %2 = версия игры
    QNetworkAccessManager *manager;

signals:

public slots:
};

#endif // LOTTOBET_H
