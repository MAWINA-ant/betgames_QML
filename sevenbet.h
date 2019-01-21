#ifndef SEVENBET_H
#define SEVENBET_H

#include <QPair>

#include "abstractgameclass.h"

class sevenbet : public abstractGameClass
{
    Q_OBJECT

public:
    explicit sevenbet();
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

#endif // SEVENBET_H
