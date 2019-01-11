#ifndef FIVEBET_H
#define FIVEBET_H

#include "abstractgameclass.h"

class fivebet : public abstractGameClass
{
    Q_OBJECT

public:
    explicit fivebet();

private:
    QMap<int, int> notFallOut;
    QList<QList<QString>> drawList;

protected:
    void parserJsonDocPage(QJsonDocument document);

public slots:
    void getDataFromSite();
};

#endif // FIVEBET_H