#ifndef motor_camera_h
#define motor_camera_h

#define PROGRAM_IDLE 0
#define PROGRAM_FORWARD 1
#define PROGRAM_BACKWARD 2
#define PROGRAM_PHOTO_FORWAD 3
#define PROGRAM_PHOTO_BACKWAD 4
#define PROGRAM_TEST 5

extern int program;
extern int motor_time;
extern int motor_pause;
extern int focus_time;
extern int exposure_time;
extern int exposure_pause;

void init_mc();
void run_program();
void switch_program(int p);
void set_settings(int mt, int mp, int ft, int et, int ep);

#endif