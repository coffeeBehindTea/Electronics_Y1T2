#ifndef UTLS_h
#define UTLS_h

#include <Arduino.h>
#include <Servo.h>
#include <climits>
#include "VARS.h"
#include "SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h"


bool tmp_sensor_connected();

float read_arm_servo_angle();
void set_servo_angle(Servo &servo, float angle);
bool servo_connected();

void reset_drink_timer(unsigned long &start_time);
bool check_drink_timer(unsigned long &start_time);
void remind_drink();

bool cup_exist(NAU7802 &loadCell);


bool arm_at_low(int arm_low_angle);
bool arm_at_high(int arm_low_angle);
void move_arm(Servo &servo, int arm_low_angle, char p);

void move_fan(int &fan_servo_state);
void turn_on_off_fan(int &fan_motor_state);

void check_temp_fan(int fan_servo_state, int fan_motor_state, int arm_low_angle, Servo &servo);




#endif