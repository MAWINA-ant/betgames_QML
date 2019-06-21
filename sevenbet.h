#ifndef SEVENBET_H
#define SEVENBET_H

#include <QPair>

#include "abstractgameclass.h"

class sevenbet : public abstractGameClass
{
    Q_OBJECT

    enum betVariant {SOLO = 1, DUET, TRIO};

public:
    explicit sevenbet();
    void sendDataToQML();
    int getSum(const int &, const betVariant &);

private:
    QMap<int, int> notFallOut;
    QList<QStringList> drawList;
    QList<QPair<QString, int>> drawListQML;
    QList<int> trio; // 3 числа не выпадали более 22
    QList<int> duet; // 2 числа не выпадали более 31
    QList<QPair<int, int>> lstBalls;

protected:
    void parserJsonDocPage(const QJsonDocument &document);

signals:
    void sendDrawData(const QString &, const int &);
    void sendResultToQML(const int &, const int &);
    void betsData(const int &, const int &, const QString &, const int &); // номер шара, id игры, номер розыгрыша, сумма

public slots:
    void getDataFromSite();
};

#endif // SEVENBET_H
