#include "spcallback.h"
#include "spsession.h"
#include "spwrap.h"
#include "sprootlist.h"
#include "spplaylist.h"
#include "sptoplist.h"
#include "spimage.h"
#include "spsearch.h"
#include "audio.h"

extern AudioFifo AFifo;

SPWrap::SPWrap() {
    this->last_error = NULL;

    /* Create main event-handling thread */
    this->sm = new SPMain();
    this->session_mutex = new QMutex();
    this->sm->setSessionMutex(this->session_mutex);

    this->shuffle = false;
    this->play_state = false;

    /* Create playback thread */
    this->ap = new AudioPlayback();
    this->ap->start(); // This will go on it's own from now, no interaction required

    /* Connect signals */
    this->connect(&spc,SIGNAL(on_NotifyMainThread(sp_session*)),this,SLOT(on_NotifyMainThread(sp_session*)));
    this->connect(&spc,SIGNAL(on_PlaylistAdded(sp_playlistcontainer *, sp_playlist *, int, void *)),this,SLOT(on_PlaylistAdded(sp_playlistcontainer *, sp_playlist *, int, void *)));
    this->connect(&spc,SIGNAL(on_MusicDelivery(sp_session *, const sp_audioformat *, const void *, int)),this,SLOT(on_MusicDelivery(sp_session *, const sp_audioformat *, const void *, int)));
}

SPWrap::~SPWrap() {

}

bool SPWrap::Initialize() {

    this->config.api_version = SPOTIFY_API_VERSION;
    this->config.cache_location = "tmp";
    this->config.settings_location = "tmp";
    this->config.application_key = g_appkey;
    this->config.application_key_size = g_appkey_size;
    this->config.user_agent = "spotify-session-example";
    this->config.callbacks = &g_callbacks;

    this->session_mutex->lock();
    this->error = sp_session_create(&this->config, &this->session);
    this->session_mutex->unlock();

    if (SP_ERROR_OK != this->error) {
        this->last_error = sp_error_message(this->error);
        return false;
    }

    /* Add playlistcontainer callbacks */
    sp_playlistcontainer_add_callbacks(sp_session_playlistcontainer(this->session),&pc_callbacks,NULL);

    return true;

}

bool SPWrap::Authenticate(const char* u, const char* p) {

    this->session_mutex->lock();
    sp_session_login(this->session, u, p);
    this->session_mutex->unlock();

    return true;

}


const char* SPWrap::GetLastError() {

    return this->last_error;

}

bool SPWrap::RequestRootlist(sp_session *s) {
    this->session_mutex->lock();
    this->pc = sp_session_playlistcontainer(s);
    this->session_mutex->unlock();

    if(this->pc!=NULL) {
        return true;
    }
    return false;

}

bool SPWrap::RequestToplist(sp_session *s) {
    sp_toplistbrowse *p;
    p = sp_toplistbrowse_create(s, SP_TOPLIST_TYPE_ALBUMS, SP_TOPLIST_REGION_USER, NULL, &toplistbrowse_loaded, NULL);
    if(p!=NULL) {
        return true;
    }
    return false;

}

sp_playlist * SPWrap::GetStarredPlaylist(sp_session * s) {
    return sp_session_starred_create	(s);
}


bool SPWrap::RequestImage(const byte *id,void *userdata) {
    qDebug() << "Requesting image " << id;
    sp_image *i;

    this->session_mutex->lock();
    i = sp_image_create (this->session, id);
    this->session_mutex->unlock();

    sp_image_add_load_callback (i,  &image_loaded, userdata);
}

void SPWrap::SetCurrentPlaylist(sp_playlist *p) {
    this->current_playlist = p;
}

void SPWrap::SetCurrentSearch(sp_search *s) {
    this->current_search = s;
}

sp_playlist * SPWrap::GetCurrentPlaylist() {
    return this->current_playlist;
}

void SPWrap::PlayPlaylistTrack(int offset) {

    sp_track *t = sp_playlist_track(this->current_playlist,offset);

    if(t && sp_track_is_loaded(t) && sp_track_error(t)==SP_ERROR_OK){

        this->PlayTrack(t);

        /* Send this playlist to queue */
        this->play_queue.FromPlaylist(this->current_playlist,offset);
    } else {
        qDebug() << "Invalid/Not loaded track";
    }

}

void SPWrap::PlaySearchTrack(int offset) {

    sp_track *t = sp_search_track(this->current_search,offset);

    if(t && sp_track_is_loaded(t) && sp_track_error(t)==SP_ERROR_OK){

        this->PlayTrack(t);

        /* Send this playlist to queue */
        this->play_queue.FromSearch(this->current_search,offset);
    } else {
        qDebug() << "Invalid/Not loaded track";
    }

}

void SPWrap::PlayTrack(sp_track *t) {

    this->session_mutex->lock();

    sp_session_player_unload(this->session);

    AFifo.Flush();

    this->play_state = true;
    emit this->PlayStateChanged(true);

    if(sp_session_player_load(this->session, t)==SP_ERROR_OK){
        sp_session_player_play(this->session, true);
    } else {
        qDebug()<<"Track failed to load";
        this->play_state = false;
        emit this->PlayStateChanged(false);
    }

    this->session_mutex->unlock();


}

void SPWrap::on_NotifyMainThread(sp_session *session) {

    qDebug()  << "Main thread notified";

    /* Start main loop */
    if(!this->sm->isRunning()) {
        qDebug()  << "Main thread started";
        this->sm->setSession(session);
        this->sm->start();
    }

}

void SPWrap::on_PlaylistAdded(sp_playlistcontainer *pc, sp_playlist *pl, int position, void *userdata) {
    sp_playlist_add_callbacks(pl, &pl_callbacks, NULL);
}

void SPWrap::on_MusicDelivery(sp_session *session, const sp_audioformat *format, const void *frames, int num_frames) {
    qDebug() << "Music delivery";
}

bool SPWrap::RequestSearch(const char *query,int num_tracks,int num_album, int num_artist) {
    this->session_mutex->lock();
    sp_search *s = sp_search_create(this->session, query, 0, num_tracks, 0, num_album, 0, num_artist, &search_complete, NULL);
    this->session_mutex->unlock();
    if(sp_search_error(s)==SP_ERROR_OK) {
        return true;
    }
    return false;
}

void SPWrap::PlayQueue(int dir) {

    sp_track * t = NULL;

    if(dir>0) {
        t = this->play_queue.GetNextTrack(this->shuffle);
    } else if(dir<0) {
        t = this->play_queue.GetPrevTrack(this->shuffle);
    }

    if(t!=NULL) this->PlayTrack(t);

}

void SPWrap::ToggleShuffle() {
    this->shuffle = !this->shuffle;
    emit this->ShuffleStateChanged(this->shuffle);
}

void SPWrap::PlayPause() {

    this->session_mutex->lock();

    if(this->play_state) {
        this->play_state = false;
        emit this->PlayStateChanged(false);

        AFifo.Flush();

        sp_session_player_play(this->session, false);

    } else {
        this->play_state = true;
        emit this->PlayStateChanged(true);

        sp_session_player_play(this->session, true) ;

    }
    this->session_mutex->unlock();
}
