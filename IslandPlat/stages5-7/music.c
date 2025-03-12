#include "music.h"
#include "types.h"
#include "psg.h"
#include <osbind.h>

void start_music() {

    /* begin the playing of the song by loading the data for the first note into the psg*/
    set_tone(0, 248);
    enable_channel(0, 1, 0);
    set_volume(0, 11);


}

void update_music(UINT32 time_elapsed) {
    if (time_elapsed > 35) {
    set_tone(0, 50);
    enable_channel(0, 1, 0);
    set_volume(0, 8);
    }
    if (time_elapsed > 70) {
        set_tone(0, 350);
        enable_channel(0, 1, 0);
        set_volume(0, 11);
    }
    return;
}

