#include "motor_camera.h"

#include <Arduino.h>

#define D_MOTOR_PWMA D2
#define D_MOTOR_DB D4
#define D_CAMERA_FOCUS D1
#define D_CAMERA_SHUTTER D0

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
    digitalWrite(D_CAMERA_SHUTTER, OFF);
    digitalWrite(D_CAMERA_FOCUS, ON);
}

void camera_take_photo() {  
    digitalWrite(D_CAMERA_SHUTTER, ON);
    digitalWrite(D_CAMERA_FOCUS, ON);
}
  
void camera_clear() {  
    digitalWrite(D_CAMERA_SHUTTER, OFF);
    digitalWrite(D_CAMERA_FOCUS, OFF);
}
  
void motor_forward() {
    digitalWrite(D_MOTOR_PWMA, RUN);
    digitalWrite(D_MOTOR_DB, STOP);
}

void motor_backward() {
    digitalWrite(D_MOTOR_PWMA, RUN);
    digitalWrite(D_MOTOR_DB, RUN);
}

void motor_stop() {
    digitalWrite(D_MOTOR_PWMA, STOP);
    digitalWrite(D_MOTOR_DB, STOP);
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
    pinMode(D_CAMERA_SHUTTER, OUTPUT); // Camera take photo 
    pinMode(D_CAMERA_FOCUS, OUTPUT); // Camera AF
    pinMode(D_MOTOR_PWMA, OUTPUT); // motor IN1
    pinMode(D_MOTOR_DB, OUTPUT); // motor IN2
  
    digitalWrite(D_CAMERA_SHUTTER, OFF);
    digitalWrite(D_CAMERA_FOCUS, OFF);
    digitalWrite(D_MOTOR_PWMA, STOP);
    digitalWrite(D_MOTOR_DB, STOP);
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
    motor_time = mt;
    motor_pause = mp;
    focus_time = ft;
    exposure_time = et;
    exposure_pause = ep;
    step = 0;
}

void run_debug_program(int cf, int ce, int d, int pwm) {
    step = 0;
    program = PROGRAM_DEBUG;

    digitalWrite(D_CAMERA_FOCUS, cf);
    digitalWrite(D_CAMERA_SHUTTER, ce);
    digitalWrite(D_MOTOR_DB, d);
    digitalWrite(D_MOTOR_PWMA, pwm);
}
