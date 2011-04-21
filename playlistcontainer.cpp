#include "playlistcontainer.h"

#include <QDebug>

void playlist_added (sp_playlistcontainer *pc, sp_playlist *pl, int position, void *userdata)
{
     reinterpret_cast<PlaylistContainer*> (userdata)->on_playlist_added (pc, pl, position);
}

void playlist_removed(sp_playlistcontainer *pc, sp_playlist *pl, int position, void *userdata)
{
    reinterpret_cast<PlaylistContainer*> (userdata)->on_playlist_removed (pc, pl, position);
}

void container_loaded(sp_playlistcontainer *pc, void *userdata)
{
    reinterpret_cast<PlaylistContainer*> (userdata)->on_container_loaded (pc);
}


PlaylistContainer::PlaylistContainer (sp_session* session)
{
    m_spPlaylistContainer = sp_session_playlistcontainer (session);

    sp_playlistcontainer_add_callbacks (m_spPlaylistContainer, &pc_callbacks, this);
}

PlaylistContainer::~PlaylistContainer ()
{
    if (m_spPlaylistContainer)
    {
        sp_playlistcontainer_remove_callbacks (m_spPlaylistContainer, &pc_callbacks, this);
    }
}

void PlaylistContainer::on_playlist_added (sp_playlistcontainer *pc, sp_playlist *pl, int position)
{
    qDebug() << "TODO PlaylistContainer::on_playlist_added";
}

void PlaylistContainer::on_playlist_removed (sp_playlistcontainer *pc, sp_playlist *pl, int position)
{
    qDebug() << "TODO PlaylistContainer::on_playlist_removed";
}

void PlaylistContainer::on_container_loaded(sp_playlistcontainer *pc)
{   
    int c = sp_playlistcontainer_num_playlists (pc);

    for (int i = 0; i < c; i++)
    {
        sp_playlist* sp_pl = sp_playlistcontainer_playlist (pc, i);

        QSharedPointer <Playlist> playlist = QSharedPointer<Playlist>(new Playlist (sp_pl));

        m_playlists.push_back (playlist);
    }

    emit containerLoaded (pc);
}
