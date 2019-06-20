#ifndef WEELBET_H
#define WEELBET_H

#include <QPair>
#include "abstractgameclass.h"

class weelbet : public abstractGameClass
{
    Q_OBJECT

public:
    explicit weelbet();
    void sendDataToQML();

private:
    QMap<int, int> notFallOut;
    QList<QPair<QString, QString>> drawList; // список розыгрышей с номером и цветом
    QList<QPair<QString, int>> drawListQML;

protected:
    void parserJsonDocPage(const QJsonDocument &);

signals:
    void sendDrawData(const QString &, const int &);
    void sendResultToQML(const int &, const int &);

public slots:
    void getDataFromSite();
};

#endif // WEELBET_H
