#include "appcore.h"
//#include <QUrl>
//#include <QNetworkRequest>

appcore::appcore(QObject *parent) : QObject(parent)
{

}

void appcore::receiveFromQML() {

    parsedList.clear();
    numberOfPage = 1;
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    QDate dateForSiteAddress = QDate::currentDate();
    if (QTime::currentTime().hour() >= 0 && QTime::currentTime().hour() < 3)
        dateForSiteAddress.setDate(dateForSiteAddress.year(), dateForSiteAddress.month(), dateForSiteAddress.day() - 1);
    siteAddress = "https://www.betgamesafrica.co.za/ext/game/results/testpartner/"
                + dateForSiteAddress.toString("yyyy-MM-dd") + "/1/";
    manager->get(QNetworkRequest(QUrl(siteAddress + QString::number(numberOfPage))));
}

//****************************************
// слот отвечает за парсер данных с сайта
// заполняет список всеми розыгрышами
//****************************************

void appcore::replyFinished(QNetworkReply *reply)
{
    QByteArray dataFromPage = reply->readAll();
    QString stringFromPage(dataFromPage);

    QString plainTextString = QTextDocumentFragment::fromHtml(stringFromPage).toPlainText();
    plainTextString = plainTextString.mid(plainTextString.indexOf("Video"));
    QStringList unparsedList = plainTextString.split("\n");

    unparsedList.removeAt(0);
    unparsedList.removeAll(QString("Watch "));
    unparsedList.removeAll(QString("7 out of 42"));
    unparsedList.removeLast();

    //*****************************************************************************
    // в цикле отделяется все лишнее и заносится лист строк с числами через пробел
    //*****************************************************************************

    for (int i = 1; i < unparsedList.size(); i += 2) {
        if (unparsedList.at(i).length() > 3) {
            parsedList.append(unparsedList.at(i));
        }
    }
    if (numberOfPage < (QString(unparsedList.last()).toInt() + 1)) {//&&
        //parsedList.size() < 90) {
        numberOfPage++;
        manager->get(QNetworkRequest(QUrl(siteAddress + QString::number(numberOfPage))));
    } else {
        for (int i = 0; i < parsedList.size(); i++) {

            int sum = 0;
            QString dataQML = parsedList.at(i);
            dataQML.remove(dataQML.size() - 1, 1);

            // подсчет суммы элеентов
            QStringList strList = dataQML.split(" ");
            foreach (QString str, strList) {
                sum += str.toInt();
            }
            //***********************
            emit sendDataToQML(dataQML, sum);
        }
    }
    reply->deleteLater();
}
