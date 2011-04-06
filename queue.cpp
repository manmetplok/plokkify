#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"

Queue::Queue() {
    this->current_idx = 0;
}

void Queue::FromPlaylist(sp_playlist *playlist, int offset) {

    if(sp_playlist_is_loaded(playlist)) {

        /* Clear queue */
        this->Clear();

        /* Get track count */
        this->track_count = sp_playlist_num_tracks(playlist);
        for(int i=0;i<this->track_count;i++){

            /* Get track and check it's loaded */
            sp_track *t = sp_playlist_track(playlist,i);
            if(sp_track_is_loaded(t)) {
                Track t_tmp;
                t_tmp.idx = i;
                t_tmp.track = t;
                this->track_queue.push_back(t_tmp);
            }
        }

        this->current_idx = offset;

    }
}

void Queue::FromSearch(sp_search *playlist, int offset) {

    if(sp_search_is_loaded(playlist)) {

        /* Clear queue */
        this->Clear();

        /* Get track count */
        this->track_count = sp_search_num_tracks(playlist);
        for(int i=0;i<this->track_count;i++){

            /* Get track and check it's loaded */
            sp_track *t = sp_search_track(playlist,i);
            if(sp_track_is_loaded(t)) {
                Track t_tmp;
                t_tmp.idx = i;
                t_tmp.track = t;
                this->track_queue.push_back(t_tmp);
            }
        }

        this->current_idx = offset;

    }
}

void Queue::Clear() {
    this->track_queue.clear();
}

sp_track * Queue::GetTrackAt(int search_idx) {
    this->current_idx = search_idx;
    std::vector<Track>::iterator it;
    for(it = this->track_queue.begin();it != this->track_queue.end();it++) {
        if((*it).idx == search_idx) {
            return ((*it).track);
        }
    }
    return NULL;
}

sp_track * Queue::GetNextTrack(bool shuffle) {

    if(shuffle) return this->GetShuffleTrack();

    sp_track * ret = NULL;
    int timeout = 50;

    while(ret==NULL){

        /* Increase current index by 1 */
        this->current_idx +=1;

        /* If we have passed the end, start over at 0 */
        if(this->current_idx>this->track_count-1)this->current_idx = 0;

        /* Search for next playable track */
        std::vector<Track>::iterator it;
        for(it = this->track_queue.begin();it != this->track_queue.end();it++) {
            if((*it).idx == current_idx) {
                /* Track found, return it */
                return ((*it).track);
            }
        }

        if((timeout--)<=0)break;
    }

    /* No tracks found, this shouldn't happen if we have song in the queue */
    return NULL;

}

sp_track * Queue::GetPrevTrack(bool shuffle) {

    if(shuffle) return this->GetShuffleTrack();

    sp_track * ret = NULL;
    int timeout = 50;

    while(ret==NULL){

        /* Decrease current index by 1 */
        this->current_idx -=1;

        /* If we have passed the start, shart over from end */
        if(this->current_idx<0) this->current_idx = this->track_count-1;

        /* Search for next playable track */
        std::vector<Track>::iterator it;
        for(it = this->track_queue.begin();it != this->track_queue.end();it++) {
            if((*it).idx == current_idx) {
                /* Track found, return it */
                return ((*it).track);
            }
        }

        if((timeout--)<=0)break;

    }

    /* No tracks found, this shouldn't happen if we have song in the queue */
    return NULL;

}

sp_track * Queue::GetShuffleTrack() {

    sp_track * ret = NULL;
    int timeout = 50;

    while(ret==NULL){

        /* Randomize track index */
        int rnd_idx = rand() % this->track_count;
        qDebug() << "Trying a rnd track " << rnd_idx ;

        if(!(rnd_idx == this->current_idx)) {

            /* Check if shuffled track is playable */
            std::vector<Track>::iterator it;
            for(it = this->track_queue.begin();it != this->track_queue.end();it++) {
                if((*it).idx == rnd_idx) {
                    /* Track found, return it */
                    this->current_idx -= rnd_idx;
                    return ((*it).track);
                }
            }

        }
        if((timeout--)<=0)break;

    }

    /* No tracks found, this shouldn't happen if we have song in the queue */
    return NULL;

}
