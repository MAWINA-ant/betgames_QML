#ifndef WEELBET_H
#define WEELBET_H

#include <QPair>
#include "abstractgameclass.h"

class weelbet : public abstractGameClass
{
    Q_OBJECT

public:
    explicit weelbet();

private:
    QList<QPair<QString, QString>> drawList; // список розыгрышей с номером и цветом

protected:
    void parserJsonDocPage(QJsonDocument);

public slots:
    void getDataFromSite();
};

#endif // WEELBET_H
