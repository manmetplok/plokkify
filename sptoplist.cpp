#include <QDebug>
#include "sptoplist.h"

extern SPCallback spc;

void toplistbrowse_loaded(sp_toplistbrowse *tlb, void* userdata) {
    qDebug() << "TLB is loaded";
    spc.ToplistbrowseLoaded(tlb,userdata);
}
