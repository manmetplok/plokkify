/* ----------------------------------------------------------------------------------------

Copyright 2010 Robin Nilsson <robinnilsson@gmail.com>. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this list of
    conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice, this list
    of conditions and the following disclaimer in the documentation and/or other materials
    provided with the distribution.

THIS SOFTWARE IS PROVIDED BY Robin Nilsson ``AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Robin Nilsson OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of Robin Nilsson.

------------------------------------------------------------------------------------------*/


#ifndef SPCALLBACK_H
#define SPCALLBACK_H

#include <QObject>
#include "spotify_cpp.h"
#include "audio.h"



class SPCallback : public QObject {
    Q_OBJECT

public:
        SPCallback();

        /* Session */
        void ConnectionError(sp_session *session, sp_error error);
        void LoginFailed(sp_session *session,sp_error error);
        void LoginSucceeded(sp_session *session);
        void LoggedOut(sp_session *session);
        void MessageToUser(sp_session *session, const char *message);
        void NotifyMainThread(sp_session *session);
        void MetadataUpdated(sp_session *session);
        int MusicDelivery(sp_session *session, const sp_audioformat *format, const void *frames, int num_frames);
        void PlayTokenLost(sp_session *session);
        void LogMessage(sp_session *session,const char *data);
        void EndOfTrack(sp_session *session);

        /* Rootlist */
        /* static void playlist_added(sp_playlistcontainer *pc, sp_playlist *pl, int position, void *userdata);
        static void playlist_removed(sp_playlistcontainer *pc, sp_playlist *pl, int position, void *userdata);*/
        void RootlistLoaded(sp_playlistcontainer *pc, void *userdata);
        void PlaylistRemoved(sp_playlistcontainer *pc, sp_playlist *pl, int position, void *userdata);
        void PlaylistAdded(sp_playlistcontainer *pc, sp_playlist *pl, int position, void *userdata);

        /* Playlist */
        void TracksAdded(sp_playlist *pl, sp_track * const *tracks, int num_tracks, int position, void *userdata);
        void TracksRemoved(sp_playlist *pl, const int *tracks, int num_tracks, void *userdata);
        void TracksMoved(sp_playlist *pl, const int *tracks, int num_tracks, int new_position, void *userdata);
        void PlaylistRenamed(sp_playlist *pl, void *userdata);

        /* Toplistbrowse */
        void ToplistbrowseLoaded(sp_toplistbrowse *tlb, void* userdata);

        /* Images */
        void ImageLoaded(sp_image *image, void *userdata);

        /* Search */
        void SearchComplete(sp_search *s,void *userdata);

signals:

        void on_NotifyMainThread(sp_session *session);
        void on_LoginFailed(sp_session *session,sp_error error);
        void on_LoginSucceeded(sp_session *session);

        void on_RootlistLoaded(sp_playlistcontainer *pc, void* usedata);
        void on_PlaylistAdded(sp_playlistcontainer *pc, sp_playlist *pl, int position, void *userdata);
        void on_PlaylistRemoved(sp_playlistcontainer *pc, sp_playlist *pl, int position, void *userdata);

        void on_TracksAdded(sp_playlist *pl, sp_track * const *tracks, int num_tracks, int position, void *userdata);
        void on_TracksRemoved(sp_playlist *pl, const int *tracks, int num_tracks, void *userdata);
        void on_TracksMoved(sp_playlist *pl, const int *tracks, int num_tracks, int new_position, void *userdata);
        void on_PlaylistRenamed(sp_playlist *pl, void *userdata);

        void on_ToplistbrowseLoaded(sp_toplistbrowse *tlb, void* userdata);

        void on_ImageLoaded(sp_image *image, void *userdata);

        void on_MusicDelivery(sp_session *session, const sp_audioformat *format, const void *frames, int num_frames);

        void on_SearchComplete(sp_search *s,void *userdata);

};

#endif // SPCALLBACK_H
