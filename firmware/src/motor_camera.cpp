#include "Arduino.h"
#include "motor_camera.h"

#define ON LOW
#define OFF HIGH
#define RUN HIGH
#define STOP LOW


int program = PROGRAM_TEST;
int step = 0;
int motor_time = 10;
int motor_pause = 10;
int focus_time = 5;
int exposure_time = 5;
int exposure_pause = 10;

void camera_af() {
  digitalWrite(D0, OFF);
  digitalWrite(D1, ON);
}

void camera_take_photo() {  
  digitalWrite(D0, ON);
  digitalWrite(D1, ON);
}
  
void camera_clear() {  
  digitalWrite(D0, OFF);
  digitalWrite(D1, OFF);
}
  
void motor_forward() {
  digitalWrite(BUILTIN_LED, ON);
  digitalWrite(D2, RUN);
  digitalWrite(D3, STOP);
}

void motor_backward() {
  digitalWrite(BUILTIN_LED, ON);
  digitalWrite(D2, STOP);
  digitalWrite(D3, RUN);
}

void motor_stop() {
  digitalWrite(BUILTIN_LED, OFF);
  digitalWrite(D2, STOP);
  digitalWrite(D3, STOP);
}

void program_idle() {
    camera_clear();
    motor_stop();
    step = 0;
}

void program_forward() {
    motor_forward();
    camera_clear();
    step = 0;
}

void program_backward() {
    motor_backward();
    camera_clear();
    step = 0;
}

void program_take_photos(int direction) {
    int step_stabilize = motor_pause;
    int step_af = step_stabilize + focus_time;
    int step_take = step_af + exposure_time;
    int step_pause = step_take + exposure_pause;
    int step_move = step_pause + motor_time;

    if (step < step_stabilize) {
        motor_stop();
        camera_clear();
    } else if (step < step_af) {
        motor_stop();
        camera_af();
    } else if (step < step_take) {
        motor_stop();
        camera_take_photo();
    } else if (step < step_pause) {
        motor_stop();
        camera_clear();
    } else if (step < step_move) {
        if (direction == 1) {
            motor_forward();
        } else {
            motor_backward();
        }
        camera_clear();
    } else {
        step = 0;
        motor_stop();
        camera_clear();
    }
    step++;
}

void program_test() {
    int step_stabilize = 10;
    int step_af = step_stabilize + 5;
    int step_take = step_af + 5;
    int step_pause = step_take + 10;
    int step_forward = step_pause + 10;
    int step_forward_pause = step_forward + 10;
    int step_backward = step_forward_pause + 10;

    if (step < step_stabilize) {
        motor_stop();
        camera_clear();
    } else if (step < step_af) {
        motor_stop();
        camera_af();
    } else if (step < step_take) {
        motor_stop();
        camera_take_photo();
    } else if (step < step_pause) {
        motor_stop();
        camera_clear();
    } else if (step < step_forward) {
        motor_forward();
        motor_backward();
        camera_clear();
    } else if (step < step_forward_pause) {
        motor_stop();
        camera_clear();
    } else if (step < step_backward) {
        motor_backward();
        camera_clear();
    } else {
        motor_stop();
        camera_clear();
        step = 0;
        program = PROGRAM_IDLE;
    }
    step++;
}

void init_mc() {
    pinMode(BUILTIN_LED, OUTPUT);
    pinMode(D0, OUTPUT); // Camera take photo 
    pinMode(D1, OUTPUT); // Camera AF
    pinMode(D2, OUTPUT); // motor IN1
    pinMode(D3, OUTPUT); // motor IN2
  
    digitalWrite(BUILTIN_LED, OFF);
    digitalWrite(D0, OFF);
    digitalWrite(D1, OFF);
    digitalWrite(D2, STOP);
    digitalWrite(D3, STOP);
}

void run_program() {
    switch(program) {
        case PROGRAM_IDLE:
            program_idle();
            break;

        case PROGRAM_FORWARD:
            program_forward();
            break;

        case PROGRAM_BACKWARD:
            program_backward();
            break;

        case PROGRAM_PHOTO_FORWAD:
            program_take_photos(1);
            break;

        case PROGRAM_PHOTO_BACKWAD:
            program_take_photos(-1);
            break;

        case PROGRAM_TEST:
            program_test();
            break;
    }
}

void switch_program(int p) {
    program = p;
    step = 0;
}

void set_settings(int mt, int mp, int ft, int et, int ep) {
    int motor_time = mt;
    int motor_pause = mp;
    int focus_time = ft;
    int exposure_time = et;
    int exposure_pause = ep;
    step = 0;
}
