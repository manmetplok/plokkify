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

#ifndef SPWRAP_H
#define SPWRAP_H

#include <QThread>
#include <QMutex>
#include <QObject>
#include <QDebug>
#include <vector>

#include "spotify_cpp.h"
#include "appkey.h"
#include "spmain.h"
#include "queue.h"
#include "playback.h"

class SPWrap : public QObject {
    Q_OBJECT

private:
    sp_session_config config;
    sp_error error;
    sp_session *session;
    sp_playlist *current_playlist;
    sp_search *current_search;

    const char *last_error;

    SPMain *sm;
    AudioPlayback *ap;

    Queue play_queue;

    QMutex *session_mutex;

    void PlayTrack(sp_track *t);
    bool shuffle;
    bool play_state;

public:
    sp_playlistcontainer *pc;

    SPWrap();
    ~SPWrap();

    bool Initialize();
    bool Authenticate(const char *u, const char *p);
    const char* GetLastError();

    bool RequestRootlist(sp_session *s);
    bool RequestToplist(sp_session *s);
    bool RequestSearch(const char *query,int num_tracks,int num_album, int num_artist);

    bool RequestImage(const byte *id,void *userdata);

    void SetCurrentPlaylist(sp_playlist *p);
    void SetCurrentSearch(sp_search *s);
    sp_playlist * GetCurrentPlaylist();
    void PlayPlaylistTrack(int offset);
    void PlaySearchTrack(int offset);
    void PlayQueue(int dir);
    void ToggleShuffle();
    void PlayPause();

signals:
    void ShuffleStateChanged(bool);
    void PlayStateChanged(bool);

public slots:
    void on_NotifyMainThread(sp_session *session);
    void on_PlaylistAdded(sp_playlistcontainer *pc, sp_playlist *pl, int position, void *userdata);
    void on_MusicDelivery(sp_session *session, const sp_audioformat *format, const void *frames, int num_frames);
};

#endif // SPWRAP_H
