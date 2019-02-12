#ifndef KENOBET_H
#define KENOBET_H

#include <QPair>

#include "abstractgameclass.h"

class kenobet : public abstractGameClass
{
    Q_OBJECT

public:
    explicit kenobet();
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

#endif // KENOBET_H
