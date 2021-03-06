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


#ifndef PLAYLISTCONTAINER_H
#define PLAYLISTCONTAINER_H

#include <QObject>
#include <QVector>
#include <QSharedPointer>

#include "spotify_cpp.h"

#include "playlist.h"

void playlist_added(sp_playlistcontainer *pc, sp_playlist *pl, int position, void *userdata);
void playlist_removed(sp_playlistcontainer *pc, sp_playlist *pl, int position, void *userdata);
void container_loaded(sp_playlistcontainer *pc, void *userdata);

static sp_playlistcontainer_callbacks pc_callbacks = {
    &playlist_added,
    &playlist_removed,
    NULL,
    &container_loaded
};

class PlaylistContainer : public QObject
{
    Q_OBJECT

public:
    PlaylistContainer (sp_session* session);
    virtual ~PlaylistContainer ();

    void on_playlist_added (sp_playlistcontainer *pc, sp_playlist *pl, int position);
    void on_playlist_removed (sp_playlistcontainer *pc, sp_playlist *pl, int position);
    void on_container_loaded(sp_playlistcontainer *pc);

    QVector<QSharedPointer <Playlist> > playlists (void) {return m_playlists;}


    sp_playlistcontainer* spPlaylistContainer (void) {return m_spPlaylistContainer;}
signals:
    void containerLoaded (sp_playlistcontainer *pc);

private:
    sp_playlistcontainer* m_spPlaylistContainer;

    QVector<QSharedPointer <Playlist> > m_playlists;
};

#endif // PLAYLISTCONTAINER_H
