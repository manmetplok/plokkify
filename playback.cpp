#include <QDebug>
#include <stdint.h>
#include "playback.h"

extern AudioFifo AFifo; /* Audioqueue has to be global due to c-callback */

AudioPlayback::AudioPlayback(void) {

    crate = 0;
    cchannels = 0;

    s = audio_init("default", 44100, 2);

}

AudioPlayback::~AudioPlayback(void) {
    audio_exit();
}

pa_simple * AudioPlayback::audio_init(char * dev,uint32_t rate,uint8_t channels)
{

    pa_sample_spec ss;

    ss.format = PA_SAMPLE_S16LE;
    ss.channels = channels;
    ss.rate = rate;

    s = pa_simple_new(NULL,               // Use the default server.
                      "qtify",           // Our application's name.
                      PA_STREAM_PLAYBACK,
                      NULL,               // Use the default device.
                      "qtify-pcm2",            // Description of our stream.
                      &ss,                // Our sample format.
                      NULL,               // Use default channel map
                      NULL,               // Use default buffering attributes.
                      NULL                // Ignore error code.
                      );

    return s;

}

int AudioPlayback::audio_exit (void)
{

    return 0;
}

void AudioPlayback::run() {
    int c=0;
    int error = 0;
    while (true) {

        while(AFifo.GetLen()<=0){
            this->usleep(1);
        }

        AudioData * a;
        a=AFifo.Next();

        if(s==NULL||a->bitrate!=crate||a->nchannels!=cchannels) {
            /* Recreate playback handle */
            audio_init("default",a->bitrate,a->nchannels);
            if(!s) {
                qDebug() << "Audio init failed";
                exit(1);
            } else {
                crate = a->bitrate;
                cchannels = a->nchannels;
            }
        }

        int r;

        r=pa_simple_write(s, a->samples, a->samples_count, &error);
        if (r < 0) {
            qDebug() << __FILE__ << ": pa_simple_write() failed: " << pa_strerror(error);
        }

        /*r=pa_simple_drain(s,&error);
        if (r < 0) {
            qDebug() << __FILE__ << ": pa_simple_drain() failed: " << pa_strerror(error);
        }*/

        delete a;
    }
}

