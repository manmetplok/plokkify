#include <QDebug>
#include <QMetaType>
#include <inttypes.h>

#include "spcallback.h"

SPCallback spc;

extern AudioFifo AFifo; /* Audioqueue has to be global due to c-callback */

SPCallback::SPCallback() {
    qRegisterMetaType<sp_error>("sp_error");
}

/* Connected */
void SPCallback::NotifyMainThread(sp_session *session){
   qDebug() << "Callback received: Notify main thread";
   emit this->on_NotifyMainThread(session);
}
void SPCallback::LoginFailed(sp_session *session,sp_error error){
    qDebug() << "Callback received: Login failed";
    emit this->on_LoginFailed(session,error);
}
void SPCallback::LoginSucceeded(sp_session *session){
    qDebug() << "Callback received: Login succeeded";
    emit this->on_LoginSucceeded(session);
}
int SPCallback::MusicDelivery(sp_session *session, const sp_audioformat *format, const void *frames, int num_frames)
{

    qDebug() << "Deliver try";
    /* Check if we got any frames */
    if (num_frames == 0) {
        qDebug() << "No frames delivered, returning 0";
        return 0;
    }

    /* Check if the buffer is full, then return 0 to request later delivery */
    if (AFifo.NumSamples() > format->sample_rate*16) {
        return 0;
    }
        qDebug() << "Deliver success";

    /* Prepare PCM-data for queueing */
    AudioData * ad = new AudioData();

    int16_t * t_buf = new int16_t[num_frames*format->channels];
    //int16_t * t_buf = (int16_t*)malloc(num_frames*format->channels*sizeof(int16_t));

    memcpy(t_buf,frames,num_frames*format->channels*sizeof(int16_t));

    ad->samples = t_buf;
    ad->bitrate = format->sample_rate;
    ad->nchannels = format->channels;
    ad->samples_count = num_frames*format->channels*sizeof(int16_t);

    /* Put audio data to queue */
    AFifo.Push(ad);

    return num_frames;

}

/* ToDo: Connect */
void SPCallback::ConnectionError(sp_session *session, sp_error error){
    qDebug() << "Callback received: Connection error";
}



void SPCallback::LoggedOut(sp_session *session){
    qDebug() << "Callback received: Logged out";
}
void SPCallback::MessageToUser(sp_session *session, const char *message){
    qDebug() << "Callback received: Message to user: " << message;
}

void SPCallback::MetadataUpdated(sp_session *session){
    qDebug() << "Callback received: Metadata updated";
}
/* Musicdelivery here */
void SPCallback::PlayTokenLost(sp_session *session){
    qDebug() << "Callback received: Play-token lost";
}
void SPCallback::LogMessage(sp_session *session,const char *data){
    qDebug() << "Callback received: Log message" << data;
}
void SPCallback::EndOfTrack(sp_session *session){
    qDebug() << "EndOfTrack";
}


/* ------------ Rootlist */
void SPCallback::RootlistLoaded(sp_playlistcontainer *pc,void *userdata){
    qDebug() << "Rootlist loaded2";
    emit this->on_RootlistLoaded(pc,userdata);
}
void SPCallback::PlaylistAdded(sp_playlistcontainer *pc, sp_playlist *pl, int position, void *userdata){
    qDebug() << "Playlist added";
    emit this->on_PlaylistAdded(pc,pl,position,userdata);
}
void SPCallback::PlaylistRemoved(sp_playlistcontainer *pc, sp_playlist *pl, int position, void *userdata){
    qDebug() << "Playlist removed";
    emit this->on_PlaylistRemoved(pc,pl,position,userdata);
}

/* Playlist */
void SPCallback::TracksAdded(sp_playlist *pl, sp_track * const *tracks, int num_tracks, int position, void *userdata){
    emit this->on_TracksAdded(pl,tracks,num_tracks,position,userdata);
}

void SPCallback::TracksRemoved(sp_playlist *pl, const int *tracks, int num_tracks, void *userdata){
    emit this->on_TracksRemoved(pl,tracks,num_tracks,userdata);
}

void SPCallback::TracksMoved(sp_playlist *pl, const int *tracks, int num_tracks, int new_position, void *userdata){
    emit this->on_TracksMoved(pl,tracks,num_tracks,new_position,userdata);
}

void SPCallback::PlaylistRenamed(sp_playlist *pl, void *userdata){
    emit this->on_PlaylistRenamed(pl,userdata);
}

//void SPCallback::PlaylistStateChanged(sp_playlist *pl, void *userdata) {
//    emit this->on_PlaylistStateChanged(pl,userdata);
//}



/* Toplist */
void SPCallback::ToplistbrowseLoaded(sp_toplistbrowse *tlb, void* userdata) {
    emit this->on_ToplistbrowseLoaded(tlb,userdata);
}

/* Image */
void SPCallback::ImageLoaded(sp_image *image, void* userdata) {
    emit this->on_ImageLoaded(image,userdata);
}

/* Search */
void SPCallback::SearchComplete(sp_search *s,void *userdata) {
    emit this->on_SearchComplete(s,userdata);
}
