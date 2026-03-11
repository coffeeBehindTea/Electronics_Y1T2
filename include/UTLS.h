#ifndef UTLS_h
#define UTLS_h

#include <Arduino.h>
#include <Servo.h>
#include <climits>
#include "VARS.h"


bool tmp_sensor_connected(int dataPin);

float read_servo_angle(int pin);
void set_servo_angle(Servo &servo, float angle);
bool servo_connected(int feedbackPin);

#endif