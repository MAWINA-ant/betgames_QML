#ifndef ABSTRACTGAMECLASS_H
#define ABSTRACTGAMECLASS_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QByteArray>
#include <QThread>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QQueue>

class abstractGameClass : public QObject
{
    Q_OBJECT
public:
    abstractGameClass(QObject *parent = nullptr) : QObject(parent), gameIntervalSec(180), gameId(1) {} // конструктор по умолчанию (вдруг понадобится)
    abstractGameClass(quint8 id, quint16 intervalSec, QObject *parent = nullptr); // если вдруг нужно поменять интервал
    ~abstractGameClass();
    virtual void sendDataToQML() = 0;

private:
    quint16 gameIntervalSec; // интервал между розыгрышами в секундах
    QTimer *minuteTimer; // таймер для проверки текущей минуты
    QByteArray gameData; // данные с сайта
    quint8 pageCount = 0; // кол-во страниц статистики

protected:
    QString siteAddress = QString("https://tvbetframe6.com/tvbet/getdata?action=filterResults&date=%1&game_type=%2&my=0&page=%3&clientId=1&lng=ru"); // строка с URL для получения данных
    qint64 dateSeconds;
    int gameId; //номер игры на сайте
    int currentPage = 1;
    QNetworkAccessManager *manager;
    QList<QJsonDocument> documentJsonList;
    QQueue<QString> listURL;

    virtual void parserJsonDocPage(QJsonDocument) = 0;

signals:
    void startGettingData();
    void sendProgressStatus(double, QString);

public slots:
    virtual void getDataFromSite() = 0;
    void loadData();

    void replyFinished(QNetworkReply*);
};

#endif // ABSTRACTGAMECLASS_H
