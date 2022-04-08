#include "debug.h"

bool debug_active = false;

void init_debug() {
    Serial.begin(9600);
    debug_active = true;
}
