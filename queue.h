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


#ifndef QUEUE_H
#define QUEUE_H

#include <vector>
#include <stdlib.h>

#include "spotify_cpp.h"

class Track {
public:
    int idx;
    sp_track* track;
};

class Queue {
private:

    std::vector<Track> track_queue;
    int current_idx;
    int track_count;

    void Clear();
    sp_track * GetShuffleTrack();

public:

    Queue();
    void FromPlaylist(sp_playlist *p,int offset);
    void FromSearch(sp_search *playlist, int offset);

    sp_track * GetTrackAt(int idx);
    sp_track * GetPrevTrack(bool shuffle);
    sp_track * GetNextTrack(bool shuffle);

};

#endif // QUEUE_H
