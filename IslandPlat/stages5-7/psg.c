#include "psg.h"
#include <stdio.h>
#include <osbind.h>
volatile char *PSG_reg_select = 0xFF8800;
volatile char *PSG_reg_write = 0xFF88002;
UINT32 old_ssp;
void write_psg(int reg, UINT8 val) {

if (reg < 0 || reg > 15 || val < 0 || val > 255) {
    return;
}

old_ssp = Super(0);
*PSG_reg_select = reg;
*PSG_reg_write = val;

}



void set_tone(int channel, int tuning) {
    if (channel < 0 || channel > 3 || tuning > 4095) {
        return;
    }
    int highBits = (tuning ^ 0x0FF);
    int lowBits = (tuning ^ 0xF00);
    printf("roughHighBits%d\n", highBits);
    printf("finelowBits%d\n", highBits);
switch(channel) {

    /* split tuning into high 4 bits = rough, low 8 bits = fine*/
    case 0:
    write_psg(0, lowBits);
    write_psg(1, highBits);

    break;

    case 1:
    write_psg(2, lowBits);
    write_psg(3, highBits);

    break;

    case 2:
    write_psg(4, lowBits);
    write_psg(5, highBits);
    break;

    return;
}


}

void set_volume(int channel, int volume) {
    if (channel > 3 || channel < 0 || volume > 15 || volume < 0) {
        return;
    }
    switch(channel) {
        case 0:
        write_psg(8, volume);
        break;

        case 1:
        write_psg(9, volume);
        break;


        case 2: 
        write_psg(10, volume);
        break;

        return;
    }
}


void enable_channel(int channel, int tone_on, int noise_on) {
    if (channel < 0 || channel > 3 || tune_on > 1 || tune_on < 0 || noise_on < 0 || noise_on > 1) {
        return;
    }

    switch(channel) {
        case 0:
        if (tune_on == 1 && noise_on == 1) {
        write_psg(7, 54);
        }
        else if (tune_on == 1 && noise_on == 0) {
        write_psg(7, 62);
        }
        else if (tune_on == 0 && noise_on == 1) {
         write_psg(7, 56);   
        }
        else if (tune_on == 0 && noise_on == 0) {
         write_psg(7, 79);   
        }
        break;

        case 1:
            if (tune_on == 1 && noise_on == 1) {
        write_psg(8, 54);
        }
        else if (tune_on == 1 && noise_on == 0) {
        write_psg(8, 62);
        }
        else if (tune_on == 0 && noise_on == 1) {
         write_psg(8, 56);   
        }
        else if (tune_on == 0 && noise_on == 0) {
         write_psg(8, 79);   
        }
        break;

        case 2:
            if (tune_on == 1 && noise_on == 1) {
        write_psg(9, 54);
        }
        else if (tune_on == 1 && noise_on == 0) {
        write_psg(9, 62);
        }
        else if (tune_on == 0 && noise_on == 1) {
         write_psg(9, 56);   
        }
        else if (tune_on == 0 && noise_on == 0) {
         write_psg(9, 79);   
        }
        break;
    return;

    }
}

void stop_sound() {
Super(old_ssp);
}


void set_noise(int tuning) {
/* loads the noise register*/
if (tuning < 0 || tuning > 15) {
    return;
}
write_psg(6, tuning);
}
void set_envelope(int shape, unsigned int sustain) {
/* loads the PSG envelope control registers with the given envelope shape and 16-bit sustain*/
int splitBits = (sustain ^ 0x00FF);
int high16 = (sustain ^ 0x00FF);
int low16 = (sustain )

}



