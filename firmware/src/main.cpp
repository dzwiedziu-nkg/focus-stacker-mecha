#include <Arduino.h>
#include "motor_camera.h"
#include "backend.h"
#include "wifi.h"
#include "debug.h"


void setup() {
    init_debug();
    init_wifi();
    init_mc();
    init_server();
}

void loop() {
    run_program();
    delay(100); 
}
