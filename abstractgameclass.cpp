#include "abstractgameclass.h"
#include <QEventLoop>

abstractGameClass::abstractGameClass(quint8 pageId, quint16 intervalSec, QObject *parent) : QObject(parent),
                                                                                            gameIntervalSec(intervalSec),
                                                                                            gamePageId(pageId)
{

    //********************************************************************************
    // создаётся страница веб движка и по адресу
    // происходит сама загрузка страницы. Как только страница загрузилась происходит
    // получение данных (getDataFromPage())
    //********************************************************************************

    siteAddres = "https://1xbet.betgamestv.eu/ext/game/results/1xbet/2018-12-26/" + QString::number(gamePageId) + "/1/";
    gameWebView = new QWebEngineView();
    connect(gameWebView->page(), SIGNAL(loadFinished(bool)), this, SLOT(getDataFromSite()));
    gameWebView->load(QUrl(siteAddres));
    gameWebView->show();
    //********************************************************************************
}

abstractGameClass::~abstractGameClass()
{

}

void abstractGameClass::getDataFromSite()
{    

    qDebug() << QThread::currentThreadId() << "Eto -> " << gamePageId;
    gameWebView->page()->toPlainText([](QString result) {
            qDebug() << result;
        });
}
