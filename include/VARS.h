#ifndef VARS_H
#define VARS_H

#include <Arduino.h>

constexpr int FAN_ARM_FORWARD_SIGNAL = 1700;
constexpr int FAN_ARM_STOP_SIGNAL = 1500;
constexpr int FAN_ARM_BACKWARD_SIGNAL = 1300;

constexpr int ARM_HIGH_ANGLE = 80;
constexpr int ARM_SERVO_CONTROL_PIN = D8;
constexpr int ARM_SERVO_FEEDBACK_PIN = A0;
constexpr int SERVO_FB_MIN = 66;
constexpr int SERVO_FB_MAX = 633;

constexpr int FAN_MOTOR_CONTROL_PIN = D1;
constexpr int FAN_SERVO_CONTROL_PIN = D12;
constexpr int FAN_SERVO_MOVE_TIME = 1000;

constexpr int TEMP_DATA_PIN = A2;
constexpr int MIN_HOT_TEMP = 23;

constexpr unsigned long TIMER_THRESHOLD = 20UL * 60UL * 1000UL; // 20 min

constexpr int MICROPHONE_DATA_PIN = A3;
constexpr int MICROPHONE_THRESHOLD = 130;
constexpr int MICROPHONE_DEBOUNCE_TIME = 300;
constexpr int MICROPHONE_MIN_INTERVAL = 30;
constexpr int MICROPHONE_MAX_INTERVAL = 400;

constexpr int CALIBRATION_FACTOR = 10;
constexpr int MIN_CUP_WEIGHT = 1000;

#endif