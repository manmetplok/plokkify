#include "audio.h"

AudioFifo AFifo;

AudioFifo::AudioFifo(void) {

}

void AudioFifo::Push(AudioData *a) {
    this->fifo_mutex.lock();
    this->num_samples += a->samples_count;
    this->audio_fifo.push(a);
    this->fifo_mutex.unlock();
}

AudioData * AudioFifo::Next(void){
    this->fifo_mutex.lock();
    AudioData * a = this->audio_fifo.front();
    this->num_samples -= a->samples_count;
    audio_fifo.pop();
    this->fifo_mutex.unlock();
    return a;
}

int AudioFifo::NumSamples(void){
    return this->num_samples;;
}

int AudioFifo::GetLen(void){
    return this->audio_fifo.size();
}

void AudioFifo::Flush(void){
    while(this->GetLen()>0) {
            this->fifo_mutex.lock();
            /* Remove the object from queue */
            AudioData * a = audio_fifo.front();
            delete a;
            this->audio_fifo.pop();
            this->fifo_mutex.unlock();
    }
    this->num_samples = 0;
}

AudioData::~AudioData() {
    delete this->samples;
}
