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


PlaylistContainer::PlaylistContainer ()
{

}

PlaylistContainer::~PlaylistContainer ()
{

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
    qDebug() << "PlaylistContainer >> Nr of playlists loaded: " << sp_playlistcontainer_num_playlists (pc);
}
