#ifndef SEVENBET_H
#define SEVENBET_H

#include "abstractgameclass.h"

class sevenbet : public abstractGameClass
{
    Q_OBJECT

public:
    explicit sevenbet();

private:
    QMap<int, int> notFallOut;
    QList<QList<QString>> drawList;

protected:
    void parserJsonDocPage(QJsonDocument document);

signals:
    void sendDrawData(QString, int);

public slots:
    void getDataFromSite();
};

#endif // SEVENBET_H
