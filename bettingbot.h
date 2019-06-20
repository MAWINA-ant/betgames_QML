#ifndef BETTINGBOT_H
#define BETTINGBOT_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QByteArray>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class bettingBot : public QObject
{
    Q_OBJECT

public:
    explicit bettingBot(QObject *parent = nullptr);

private:
    QNetworkAccessManager *manager;

public slots:
    void replyFinished(QNetworkReply*);
    void makeBet(const int &, const int &, const QString &, const int &);
};

#endif // BETTINGBOT_H
