#ifndef FIVEBET_H
#define FIVEBET_H

#include "abstractgameclass.h"

class fivebet : public abstractGameClass
{
    Q_OBJECT

public:
    explicit fivebet();
    void sendDataToQML();

private:
    QMap<int, int> notFallOut;
    QList<QStringList> drawList;
    QList<QPair<QString, int>> drawListQML;

protected:
    void parserJsonDocPage(QJsonDocument document);

signals:
    void sendDrawData(QString, int);
    void sendResultToQML(int, int);

public slots:
    void getDataFromSite();

};

#endif // FIVEBET_H
