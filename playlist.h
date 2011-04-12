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


#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>

#include "spotify_cpp.h"

void tracks_added(sp_playlist *pl, sp_track * const *tracks,int num_tracks, int position, void *userdata);
void tracks_removed(sp_playlist *pl, const int *tracks,int num_tracks, void *userdata);
void tracks_moved(sp_playlist *pl, const int *tracks, int num_tracks, int new_position, void *userdata);
void playlist_renamed(sp_playlist *pl, void *userdata);
void playlist_state_changed(sp_playlist *pl, void *userdata);

static sp_playlist_callbacks pl_callbacks = {
    &tracks_added,
    &tracks_removed,
    &tracks_moved,
    &playlist_renamed,
    &playlist_state_changed,
    NULL,
    NULL
};

class Playlist : public QObject
{
    Q_OBJECT

public:
    Playlist (sp_playlist *playlist);
    virtual ~Playlist ();

    void on_tracks_added (sp_playlist *pl, sp_track * const *tracks,int num_tracks, int position);
    void on_tracks_removed (sp_playlist *pl, const int *tracks,int num_tracks);
    void on_tracks_moved(sp_playlist *pl, const int *tracks, int num_tracks, int new_position);
    void on_playlist_renamed(sp_playlist *pl);
    void on_playlist_state_changed(sp_playlist *pl);

signals:
    void stateChanged (sp_playlist *pl);

private:
    sp_playlist* m_spPlaylist;
};


#endif // PLAYLIST_H
