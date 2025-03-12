#include "input.h"
#include "types.h"
#include <osbind.h>

int prevKey = 0;

void getKey() {
    if (Cconis()) {
        prevKey = Cnecin();
    }
    else {
        prevKey = 0;
    }
}

int detectWKeyPress() {
return (prevKey == JUMP_KEY);
}
int detectAKeyPress() {
return (prevKey == MOVE_LEFT_KEY);
}
int detectDKeyPress() {
return (prevKey == MOVE_RIGHT_KEY);
}
int detectQKeyPress() {
return (prevKey == QUIT_KEY);
}