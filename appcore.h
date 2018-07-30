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

signals:
    void sendDataToQML(QString drawing, int summOfBalls);

public slots:
    void receiveFromQML();
    void replyFinished(QNetworkReply *reply);
};


#endif // APPCORE_H
