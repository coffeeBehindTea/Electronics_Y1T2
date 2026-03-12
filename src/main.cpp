#include "VARS.h"
#include "UTLS.h"
#include <Wire.h>
#include <Servo.h>
#include "DUMMY.h"
#include <Arduino.h>
#include "SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h"

NAU7802 loadCell;
Servo armServo;

int ARM_LOW_ANGLE = 0;
int fan_servo_state = 0; // 0 is upward, 1 is toward the cup
int fan_motor_state = 0; // 0 is stopped, 1 is rotating
bool monitor_switch = false;
bool first_time_entry = true;
unsigned long start_time;

void setup()
{
  Serial.begin(115200);
  Wire1.begin();

  Serial.println("========system setup start========");

  // Serial.println("[info] checking load cell...");
  // while (loadCell.begin(Wire1) == false)
  // {
  //   Serial.println("[error] load cell connection fail !");
  //   delay(1000);
  // }

  // Serial.println("[info] initializing load cell...");
  // Serial.println("[info] Please ensure there's NOTHING on the mat");

  // for (int i = 5; i > 0; --i)
  // {
  //   Serial.print("count down: ");
  //   Serial.println(i);
  //   delay(1000);
  // }

  // loadCell.setCalibrationFactor(CALIBRATION_FACTOR);
  // loadCell.calculateZeroOffset();
  // Serial.println("[info] load cell initialized.");

  // Serial.println("[info] checking temperature sensor...");
  // while (!tmp_sensor_connected())
  // {
  //   Serial.println("[error] temperature sensor not connected !");
  //   delay(500);
  // }
  // Serial.println("[info] temperature sensor initialized.");

  Serial.println("[info] checking arm servo...");
  armServo.attach(ARM_SERVO_CONTROL_PIN);
  while (servo_connected())
  {
    Serial.println("[error] arm servo not connected !");
    delay(500);
  }

  ARM_LOW_ANGLE = read_arm_servo_angle();

  Serial.println("[info] all components cheked.");
  Serial.println("[info] entering main loop.");
}


void loop()
{
  /* -------------------------------------------------------------------------- */
  /*       linsten to the microphone here before the monitor switch check       */
  /* -------------------------------------------------------------------------- */
  
  if (!monitor_switch)
  {
    return;
  }
  if (first_time_entry)
  {
    reset_drink_timer(start_time);
    first_time_entry = false;
  }

  // if cup leaved the mat, reset timer
  while (! cup_exist(loadCell))
  {
    first_time_entry = true;
    delay(100);
  }

  check_temp_fan(fan_servo_state, fan_motor_state, ARM_LOW_ANGLE, armServo);

  // just need to remid drink, as in the next loop, if the cup is taken, the wile loop will trap it and wait until cup being put back.
  // also checked cup exist here because during check_temp_fan actions, the system do not take inputs, so if user take cup away during action,
  // no reminding needed here.
  if (check_drink_timer(start_time) && cup_exist(loadCell))
  {
    remind_drink();
  }



}
