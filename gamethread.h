#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QDebug>

class gameThread : public QThread
{
    Q_OBJECT

private:
    quint16 gameIntervalSec; // интервал между розыгрышами в секундах
    quint8 gamePageId; //номер страницы игры на сайте (1-6)
    QTimer gameTimer; // таймер для обновления данных после каждого розыгрыша

public:
    gameThread(quint8 pageId, quint16 intervalSec);

protected:
    void run();

public slots:
    void result();

};

#endif // GAMETHREAD_H
