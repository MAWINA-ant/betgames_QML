#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTextDocument>
#include <QTextDocumentFragment>

class appcore : public QObject
{
    Q_OBJECT
public:
    explicit appcore(QObject *parent = 0);

private:
    QString siteAddress;            // адрес сайта
    int numberOfPage;               // номер страницы результатов
    QNetworkAccessManager *manager;
    QStringList parsedList;
    QMap<int, int> frequencyInRow;
    QMap<int, int> frequencyAll;

signals:
    void sendDataToQML(QString drawing, int summOfBalls);
    void sendResultToQML(int numberBall, int freqRow, int freqAll);

public slots:
    void receiveFromQMLGetData();
    void receiveFromQMLCalculate();
    void replyFinished(QNetworkReply *reply);
};


#endif // APPCORE_H
