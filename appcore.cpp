#include "appcore.h"
#include <QMessageBox>
#include <QDebug>

appcore::appcore(QObject *parent) : QObject(parent)
{
    gameChanged(1);

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

void appcore::receiveFromQMLGetData(int countDays) {
    parsedList.clear();
    currentRequest = 0;
    allPages = 0;

    //*****************************************************************************
    // подсчет даты для адреса сайта. Заполняется список адресов сайтов
    QDate dateForSiteAddress = QDate::currentDate();
    for (int i = 0; i < countDays; i++){
        int countOfPages = 10;
        if (QTime::currentTime().hour() >= 0 && QTime::currentTime().hour() < 3) {
            dateForSiteAddress.setDate(dateForSiteAddress.year(), dateForSiteAddress.month(), dateForSiteAddress.day() - 1);
            //countOfPages--;
        }
        siteAddress = "https://www.betgamesafrica.co.za/ext/game/results/testpartner/"
                    + dateForSiteAddress.toString("yyyy-MM-dd") + "/" +  QString::number(versionOfGame) + "/";
        if (dateForSiteAddress == QDate::currentDate()) {
            int fiveMinuteCount = ((QTime::currentTime().hour() - 3) * 60 + QTime::currentTime().minute()) / 5;
            countOfPages = fiveMinuteCount % 30 > 0 ? fiveMinuteCount / 30 + 1: fiveMinuteCount / 30;
        }
        for (int i = 1; i <= countOfPages; i++) {
            siteAdresses.append(siteAddress + QString::number(i));
            allPages++;
        }
        dateForSiteAddress = dateForSiteAddress.addDays(-1);
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
    if (!reply->bytesAvailable()) {
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

    unparsedList.removeAt(0);
    unparsedList.removeAll(QString("Watch "));
    if (versionOfGame == 1)
        unparsedList.removeAll(QString("7 out of 42"));
    else if (versionOfGame == 3)
        unparsedList.removeAll(QString("5 out of 36"));
    unparsedList.removeLast();

    //*****************************************************************************
    // в цикле отделяется все лишнее и заносится лист строк с числами через пробел
    //*****************************************************************************
    for (int i = 1; i < unparsedList.size(); i += 2) {
        if (unparsedList.at(i).length() > 3 && unparsedList.at(i) != "Draw was canceled. ") {
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
