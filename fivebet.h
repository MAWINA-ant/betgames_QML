#ifndef FIVEBET_H
#define FIVEBET_H

#include "abstractgameclass.h"

class fivebet : public abstractGameClass
{
    Q_OBJECT

public:
    explicit fivebet();
    void sendDataToQML();
    int getSum(const int &);

private:
    QMap<int, int> notFallOut;
    QList<QStringList> drawList;
    QList<QPair<QString, int>> drawListQML;

protected:
    void parserJsonDocPage(const QJsonDocument &document);

signals:
    void sendDrawData(const QString &, const int &);
    void sendResultToQML(const int &, const int &);
    void betsData(const int &, const int &, const QString &, const int &); // номер шара, id игры, номер розыгрыша, сумма

public slots:
    void getDataFromSite();

};

#endif // FIVEBET_H
