#ifndef debug_h
#define debug_h

#include <Arduino.h>

extern bool debug_active;

void init_debug();

#define PRINT_LOG(v) if (debug_active) Serial.print(v);
#define PRINTLN_LOG(v) if (debug_active) Serial.println(v);

#endif debug_h