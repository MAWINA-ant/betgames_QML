#ifndef ABSTRACTGAMECLASS_H
#define ABSTRACTGAMECLASS_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QByteArray>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineSettings>
#include <QThread>

class abstractGameClass : public QObject
{
    Q_OBJECT
public:
    explicit abstractGameClass(quint8 pageId, quint16 intervalSec, QObject *parent = nullptr);
    ~abstractGameClass();

private:
    QString siteAddres; // адресс сайта статистики
    quint16 gameIntervalSec; // интервал между розыгрышами в секундах
    quint8 gamePageId; //номер страницы игры на сайте (1-6)
    QTimer gameTimer; // таймер для обновления данных после каждого розыгрыша
    QByteArray gameData; // данные с сайта
    QWebEngineView *gameWebView; // веб движок

    QString getHtml(const QUrl& url);

signals:

public slots:
    void getDataFromSite();
};

#endif // ABSTRACTGAMECLASS_H
