#include "appcore.h"
#include <QMessageBox>

appcore::appcore(QObject *parent) : QObject(parent)
{
    gameChanged(1);

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    qDebug() << "Eto appcore thread ->" << QThread::currentThreadId();

    QThread *first = new QThread();
    abstractGameClass *firstGame = new abstractGameClass(1, 300);
    firstGame->moveToThread(first);
    first->start();

    QThread *second = new QThread();
    abstractGameClass *secondGame = new abstractGameClass(3, 300);
    secondGame->moveToThread(second);
    second->start();

    QThread *third = new QThread();
    abstractGameClass *thirdGame = new abstractGameClass(4, 300);
    thirdGame->moveToThread(third);
    third->start();

    /*view = new QWebEngineView();

         connect(view->page(), SIGNAL(loadFinished(bool)), this, SLOT(loaded()));
         //view->show();
         view->load(QUrl("https://1xbet.betgamestv.eu/ext/game/results/1xbet/2018-12-26/1/1/"));*/


}

bool appcore::isValidRow(QString str)
{
    bool ok = true;
    QStringList strList = str.split(" ");
    strList.removeLast();
    foreach (QString num, strList) {
        num.toInt(&ok, 10);
        if (!ok)
            break;
    }
    if (strList.length() < 5)
        ok = false;
    return ok;
}

void appcore::receiveFromQMLGetData(int countDays) {
    parsedList.clear();
    currentRequest = 0;
    allPages = 0;


    QDateTime dateTime = QDateTime::currentDateTime();
    long long seconds = dateTime.toSecsSinceEpoch() - (60 * 60 * 3); // секунды по гринвичу
    dateTime = QDateTime::fromSecsSinceEpoch(seconds);
    int fiveMinuteCount = (dateTime.time().hour() * 60 + dateTime.time().minute()) / 5; // кол-во пятиминуток за сегодня
    int countOfPages = fiveMinuteCount % 30 > 0 ? fiveMinuteCount / 30 + 1: fiveMinuteCount / 30; // кол-во страниц сайта за сегодня

    //*****************************************************************************
    // подсчет даты для адреса сайта. Заполняется список адресов сайтов
    QDate dateForSiteAddress = dateTime.date();
    for (int i = 0; i < countDays; i++){                   
        siteAddress = "http://www.betgamesafrica.co.za/ext/game/results/testpartner/"
                    + dateForSiteAddress.toString("yyyy-MM-dd") + "/" +  QString::number(versionOfGame) + "/";

        for (int i = 1; i <= countOfPages; i++) {
            siteAdresses.append(siteAddress + QString::number(i));
            allPages++;
        }
        dateForSiteAddress = dateForSiteAddress.addDays(-1);
        countOfPages = 10;
    }
    //**************************************************************
    manager->get(QNetworkRequest(QUrl(siteAdresses.at(0))));
    siteAdresses.removeFirst();  // удаляю выбранный адрес сайта
}

//****************************************
// слот отвечает за парсер данных с сайта
// заполняет список всеми розыгрышами
//****************************************

void appcore::replyFinished(QNetworkReply *reply)
{
    if (!reply->bytesAvailable() || reply->error()) {
        QMessageBox errorMessage;
        errorMessage.setText("Problem with connection to internet");
        errorMessage.exec();
        return;
    }
    QStringList currentParsedList;
    currentParsedList.clear();
    currentRequest++;
    QByteArray dataFromPage = reply->readAll();
    QString stringFromPage(dataFromPage);
    QString plainTextString = QTextDocumentFragment::fromHtml(stringFromPage).toPlainText();
    plainTextString = plainTextString.mid(plainTextString.indexOf("Video"));
    QStringList unparsedList = plainTextString.split("\n");

    /*unparsedList.removeAt(0);
    unparsedList.removeAll(QString("Watch "));
    if (versionOfGame == 1)
        unparsedList.removeAll(QString("7 out of 42"));
    else if (versionOfGame == 3)
        unparsedList.removeAll(QString("5 out of 36"));*/
    unparsedList.removeLast();
    //*****************************************************************************
    // в цикле отделяется все лишнее и заносится лист строк с числами через пробел
    //*****************************************************************************
    for (int i = 1; i < unparsedList.size(); i ++) {
        if (!isValidRow(unparsedList.at(i)))
            continue;
        if (unparsedList.at(i) != "Draw was canceled. ") {
            parsedList.append(unparsedList.at(i));
            currentParsedList.append(unparsedList.at(i));
        }
    }
    emit sendProgressStatus(currentRequest * 1.0 / allPages);
    for (int i = 0; i < currentParsedList.size(); i++) {
        int sum = 0;
        QString dataQML = currentParsedList.at(i);
        dataQML.remove(dataQML.size() - 1, 1);

        // подсчет суммы элеентов
        QStringList strList = dataQML.split(" ");
        foreach (QString str, strList) {
            sum += str.toInt();
        }
        //***********************
        emit sendDataToQML(dataQML, sum);
    }
    reply->deleteLater();
    if (!siteAdresses.isEmpty()) {
        manager->get(QNetworkRequest(QUrl(siteAdresses.at(0))));
        siteAdresses.removeFirst();
    }
}

void appcore::loaded()
{
    view->page()->toHtml([](const QString &result) {
        qDebug() << "dasdassad";
              qDebug()<<result;
        });
}

//**************************************
// вычисляются и выводятся все шарики и
// как давно они не выпадали
// выделяются красным
//**************************************

void appcore::receiveFromQMLCalculate()
{
    frequencyInRow.clear();
    frequencyAll.clear();
    gameChanged(versionOfGame);
    for (int i = 0; i < parsedList.size(); i++) {
        QStringList pari = parsedList.at(i).split(" ");
        pari.removeLast();
        for (int j = 0; j < pari.size(); j++) {
            int key = pari.at(j).toInt();
            frequencyAll[key]++;
            if (frequencyInRow.contains(key)) {
                continue;
            } else {
                frequencyInRow.insert(key, i);
            }
        }
    }
    QMapIterator<int, int> it(frequencyInRow);
    while (it.hasNext()) {
        it.next();
        emit sendResultToQML(it.key(), it.value(), frequencyAll.value(it.key()));
    }
    for (int i = 0; i < parsedList.size(); i++) {
        QStringList pari = parsedList.at(i).split(" ");
        pari.removeLast();
        QList<int> pariNumbers;
        foreach (QString num, pari) {
            pariNumbers.append(num.toInt());
        }
        qSort(pariNumbers.begin(), pariNumbers.end());
        pari.clear();
        foreach (int num, pariNumbers) {
            pari.append(QString::number(num));
        }
        for (int j = 0; j < pari.size() - 1; j++) {
            if (frequencyInRowPair.contains(pari.at(j) + " " + pari.at(j+1))) {
                if (frequencyInRowPair.value(pari.at(j) + " " + pari.at(j+1)) == -1)
                    frequencyInRowPair[pari.at(j) + " " + pari.at(j+1)] = i;
            }
        }
    }
    QHashIterator<QString, int> itPair(frequencyInRowPair);
    while (itPair.hasNext()) {
        itPair.next();
        emit semdPairResultToQML(itPair.key(), itPair.value());
    }
}

void appcore::gameChanged(int id)
{
    versionOfGame = id;
    frequencyInRow.clear();
    frequencyInRowPair.clear();
    if (id == 1) {
        for (int i = 1; i < 42; i++) {
            frequencyInRowPair.insert(QString::number(i) + " " + QString::number(i+1), -1);
        }
    } else if (id == 3) {
        for (int i = 1; i < 36; i++) {
            frequencyInRowPair.insert(QString::number(i) + " " + QString::number(i+1), -1);
        }
    }
}
