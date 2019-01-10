#ifndef SEVENBET_H
#define SEVENBET_H

#include "abstractgameclass.h"

class sevenbet : abstractGameClass
{
    Q_OBJECT

public:
    explicit sevenbet();

private:
    QMap<int, int> notFallOut;
    QList<QList<QString>> drawList;

protected:
    void parserJsonDocPage(QJsonDocument document);

public slots:
    void getDataFromSite();
};

#endif // SEVENBET_H
