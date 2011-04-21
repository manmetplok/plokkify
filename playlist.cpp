#include "playlist.h"

#include <QDebug>

void tracks_added(sp_playlist *pl, sp_track * const *tracks, int num_tracks, int position, void *userdata)
{
    reinterpret_cast<Playlist*> (userdata)->on_tracks_added (pl, tracks, num_tracks, position);
}

void tracks_removed(sp_playlist *pl, const int *tracks, int num_tracks, void *userdata)
{
   reinterpret_cast<Playlist*> (userdata)->on_tracks_removed (pl, tracks, num_tracks);
}

void tracks_moved(sp_playlist *pl, const int *tracks, int num_tracks, int new_position, void *userdata)
{
   reinterpret_cast<Playlist*> (userdata)->on_tracks_moved (pl, tracks, num_tracks, new_position);
}

void playlist_renamed(sp_playlist *pl, void *userdata)
{
    reinterpret_cast<Playlist*> (userdata)->on_playlist_renamed (pl);
}

void playlist_state_changed(sp_playlist *pl, void *userdata)
{
    reinterpret_cast<Playlist*> (userdata)->on_playlist_state_changed (pl);
}

Playlist::Playlist (sp_playlist *playlist) :
    m_spPlaylist (playlist)
{
    sp_playlist_add_callbacks( playlist, &pl_callbacks, this);
}

Playlist::~Playlist ()
{
    if (m_spPlaylist)
        sp_playlist_remove_callbacks(m_spPlaylist, &pl_callbacks, this);
}

QString Playlist::name (void)
{
    return QString::fromUtf8( sp_playlist_name (m_spPlaylist) );
}

void Playlist::on_tracks_added (sp_playlist *pl, sp_track * const *tracks,int num_tracks, int position)
{
    qDebug() << "TODO Playlist::on_tracks_added";
}

void Playlist::on_tracks_removed (sp_playlist *pl, const int *tracks,int num_tracks)
{
    qDebug() << "TODO Playlist::on_tracks_removed";
}

void Playlist::on_tracks_moved (sp_playlist *pl, const int *tracks, int num_tracks, int new_position)
{
    qDebug() << "TODO Playlist::on_tracks_moved";
}

void Playlist::on_playlist_renamed (sp_playlist *pl)
{
    qDebug() << "TODO Playlist::on_playlist_renamed";
}

void Playlist::on_playlist_state_changed(sp_playlist *pl)
{
    emit stateChanged (pl);
}
