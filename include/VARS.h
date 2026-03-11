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

constexpr int FAN_CONTROL_PIN = A1;

constexpr int TMP_DATA_PIN = A0;
constexpr int TMP_HOT_TEMP = 40;

constexpr int MICROPHONE_DATA_PIN = 6;

constexpr int CALIBRATION_FACTOR = 10;

#endif