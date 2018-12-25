#include "gamethread.h"

gameThread::gameThread(quint8 pageId, quint16 intervalSec) : gameIntervalSec(intervalSec),
                                                             gamePageId(pageId)
{

}

void gameThread::run()
{
    QTimer timer;
        connect( &timer, SIGNAL( timeout() ), SLOT( result() ) );
        timer.start( gameIntervalSec * 1000 );
        exec();
}

void gameThread::result()
{
    qDebug() << QThread::currentThreadId() << " hi " << gamePageId;
}
