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

public slots:
    void getDataFromSite();

protected:
    void parserJsonDocPage(QJsonDocument document);
};

#endif // FIVEBET_H
