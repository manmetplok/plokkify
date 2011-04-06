#include <QDebug>
#include "spplaylist.h"

extern SPCallback spc;

void tracks_added(sp_playlist *pl, sp_track * const *tracks, int num_tracks, int position, void *userdata)
{
    qDebug() << "Tracks added";
   //  spc.TracksAdded(pl,tracks,num_tracks,position,userdata);
}

void tracks_removed(sp_playlist *pl, const int *tracks, int num_tracks, void *userdata)
{
   // spc.TracksRemoved(pl,tracks,num_tracks,userdata);
}

void tracks_moved(sp_playlist *pl, const int *tracks, int num_tracks, int new_position, void *userdata)
{
   // spc.TracksMoved(pl,tracks,num_tracks,new_position,userdata);
}

void playlist_renamed(sp_playlist *pl, void *userdata)
{
    spc.PlaylistRenamed(pl,userdata);
}
