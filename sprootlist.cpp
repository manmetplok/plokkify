#include "sprootlist.h"
#include "spcallback.h"

void playlist_added(sp_playlistcontainer *pc, sp_playlist *pl, int position, void *userdata)
{
     spc.PlaylistAdded(pc,pl,position,userdata);
}

void playlist_removed(sp_playlistcontainer *pc, sp_playlist *pl, int position, void *userdata)
{
    spc.PlaylistRemoved(pc,pl,position,userdata);
    //sp_playlist_remove_callbacks(pl, &pl_callbacks, NULL);
}

void container_loaded(sp_playlistcontainer *pc, void *userdata)
{
    spc.RootlistLoaded(pc,userdata);
}
