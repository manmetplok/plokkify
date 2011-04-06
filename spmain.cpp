#include "spmain.h"

void SPMain::run() {
    while (true) {
        int timeout = -1;

        this->mutex->lock();
        sp_session_process_events(this->session, &timeout);
        this->mutex->unlock();

        this->usleep(5+timeout);
    }
}

void SPMain::setSessionMutex(QMutex *mutex) {
    this->mutex = mutex;
}
void SPMain::setSession(sp_session *session) {
    this->session = session;
}
