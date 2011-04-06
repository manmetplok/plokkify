#include "spsession.h"


void connection_error(sp_session *session, sp_error error)
{
    spc.ConnectionError(session,error);
}

void logged_in(sp_session *session, sp_error error)
{
    if (SP_ERROR_OK != error) {
        spc.LoginFailed(session,error);
        return;
    }
    spc.LoginSucceeded(session);
}

void logged_out(sp_session *session)
{
    spc.LoggedOut(session);
}

void notify_main_thread(sp_session *session)
{
    spc.NotifyMainThread(session);
}

void metadata_updated(sp_session *session)
{
    spc.MetadataUpdated(session);
}

void message_to_user(sp_session *session, const char *message)
{
    spc.LogMessage(session,message);
}

int music_delivery(sp_session *session, const sp_audioformat *format, const void *frames, int num_frames)
{
    return spc.MusicDelivery(session,format,frames,num_frames);
}

void play_token_lost(sp_session *session)
{
    spc.PlayTokenLost(session);
}

void log_message(sp_session *session, const char *data)
{
    spc.LogMessage(session,data);
}

void end_of_track(sp_session *session)
{
    spc.EndOfTrack(session);
}
