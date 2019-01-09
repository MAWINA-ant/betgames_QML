#include "abstractgameclass.h"
#include <QEventLoop>

abstractGameClass::abstractGameClass(quint8 pageId, quint16 intervalSec, QObject *parent) : QObject(parent),
                                                                                            gameIntervalSec(intervalSec),
                                                                                            gamePageId(pageId)
{

    //********************************************************************************
    //
    //
    //
    //********************************************************************************

    siteAddres = "https://tvbetframe6.com/tvbet/getdata?action=filterResults&date=1546981200&game_type=6&my=0&page=1&clientId=1&lng=ru";

    //********************************************************************************
}

abstractGameClass::~abstractGameClass()
{

}

void abstractGameClass::getDataFromSite()
{    


}
