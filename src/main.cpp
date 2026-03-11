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
  // while (!tmp_sensor_connected(TMP_DATA_PIN))
  // {
  //   Serial.println("[error] temperature sensor not connected !");
  //   delay(500);
  // }
  // Serial.println("[info] temperature sensor initialized.");

  Serial.println("[info] checking arm servo...");
  armServo.attach(ARM_SERVO_CONTROL_PIN);
  while (servo_connected(ARM_SERVO_FEEDBACK_PIN))
  {
    Serial.println("[error] arm servo not connected !");
    delay(500);
  }

  ARM_LOW_ANGLE = read_servo_angle(ARM_SERVO_FEEDBACK_PIN);

  Serial.println("[info] all components cheked.");
  Serial.println("[info] entering main loop.");
}

void loop()
{

  // if (loadCell.available())
  // {
  //   // 现在 getWeight() 就会自动除以系数，返回真正的“克”了
  //   float weight = loadCell.getWeight();

  //   Serial.print("当前重量: ");
  //   Serial.print(weight, 1); // 显示一位小数
  //   Serial.println(" g");
  // }
  // delay(200);
}
