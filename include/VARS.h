#ifndef VARS_H
#define VARS_H

#include <Arduino.h>

constexpr int FAN_ARM_FORWARD_SIGNAL = 1700;
constexpr int FAN_ARM_STOP_SIGNAL = 1500;
constexpr int FAN_ARM_BACKWARD_SIGNAL = 1300;
constexpr int FAN_ARM_CONTROL_PIN = 9;

constexpr int ARM_HIGH_ANGLE = 45;
constexpr int ARM_SERVO_CONTROL_PIN = 8;
constexpr int ARM_SERVO_FEEDBACK_PIN = A1;
constexpr int SERVO_FB_MIN = 66;
constexpr int SERVO_FB_MAX = 633;

constexpr int FAN_MOTOR_CONTROL_PIN = A1;
constexpr int FAN_SERVO_CONTROL_PIN = A2;

constexpr int TEMP_DATA_PIN = A0;
constexpr int MIN_HOT_TEMP = 40;

constexpr unsigned long TIMER_THRESHOLD = 20UL * 60UL * 1000UL; // 20 min

constexpr int MICROPHONE_DATA_PIN = 6;

constexpr int CALIBRATION_FACTOR = 10;
constexpr int MIN_CUP_WEIGHT = 10000;

#endif