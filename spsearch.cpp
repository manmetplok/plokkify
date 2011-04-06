#include <QDebug>
#include "spsearch.h"
#include "spcallback.h"

extern SPCallback spc;

void search_complete(sp_search  *result, void *userdata) {
    qDebug()<<"Searchresult received";
    spc.SearchComplete(result,userdata);
}
