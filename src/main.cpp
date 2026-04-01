#include "VARS.h"
#include "UTLS.h"
#include <Wire.h>
#include <Servo.h>
#include <Arduino.h>
#include "SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h"
#include <ArduinoGraphics.h>
#include <Arduino_LED_Matrix.h>

ArduinoLEDMatrix matrix;

/* ----------------------------- data structure ----------------------------- */
enum KnockState
{
  IDLE,
  WAIT_SECOND
};

/* ---------------------------- components objest --------------------------- */
NAU7802 loadCell;
Servo armServo;
Servo fanServo;

/* ----------------------------- state variables ---------------------------- */
int ARM_LOW_ANGLE = 130;
int fan_servo_state = 0; // 0 is upward, 1 is toward the cup
int fan_motor_state = 0; // 0 is stopped, 1 is rotating
bool monitor_switch = false;
bool first_time_entry = true;
unsigned long start_time;

KnockState knockState = IDLE;
int prevValue = 0;
unsigned long firstKnockTime = 0;
unsigned long lastTriggerTime = 0;

/* ---------------------------- function declear ---------------------------- */
void updateDoubleKnock();
void handleKnock(unsigned long now);
void onDoubleKnockDetected();


void showGoDrink()
{
    matrix.beginDraw();
    matrix.stroke(0xFFFFFFFF);
    matrix.textScrollSpeed(50);   // 数值越小越快

    // x 从右边外侧开始，y=1 基本比较合适
    matrix.beginText(12, 1, 0xFFFFFFFF);
    matrix.print("GO DRINK");
    matrix.endText(SCROLL_LEFT);

    matrix.endDraw();
}


void setup()
{
  Serial.begin(115200);
  Wire1.begin();
  matrix.begin();
  pinMode(FAN_MOTOR_CONTROL_PIN, OUTPUT);

  delay(5000);
  Serial.println("========system setup start========");

  Serial.println("[info] checking load cell...");
  while (loadCell.begin(Wire1) == false)
  {
    Serial.println("[error] load cell connection fail !");
    delay(1000);
  }

  Serial.println("[info] initializing load cell...");
  Serial.println("[info] Please ensure there's NOTHING on the mat");

  for (int i = 5; i > 0; --i)
  {
    Serial.print("count down: ");
    Serial.println(i);
    delay(1000);
  }

  loadCell.setCalibrationFactor(CALIBRATION_FACTOR);
  loadCell.calculateZeroOffset();
  Serial.println("[info] load cell initialized.");

  Serial.println("[info] checking temperature sensor...");
  // while (!tmp_sensor_connected())
  // {
  //   Serial.println("[error] temperature sensor not connected !");
  //   delay(500);
  // }
  Serial.println("[info] temperature sensor initialized.");

  Serial.println("[info] checking arm servo...");
  armServo.attach(ARM_SERVO_CONTROL_PIN);
  while (servo_connected())
  {
    Serial.println("[error] arm servo not connected !");
    delay(500);
  }

  Serial.print("move arm servo to default position: ");
  set_servo_angle(armServo, ARM_LOW_ANGLE);
  // set_servo_angle(armServo, 0);
  Serial.println(ARM_LOW_ANGLE);
  delay(2000);

  // initialize fan servo
  // fanServo.attach(FAN_SERVO_CONTROL_PIN);

  Serial.println("[info] all components cheked.");
  Serial.println("[info] entering main loop.");

  Serial.println("starcting cooling!");
  move_arm(armServo, ARM_LOW_ANGLE, 'h');
  // move_fan(fanServo, fan_servo_state);
  turn_on_off_fan(fan_motor_state);

  // showGoDrink();
}

void loop()
{
  /* -------------------------------------------------------------------------- */
  /*       linsten to the microphone here before the monitor switch check       */
  /* -------------------------------------------------------------------------- */

  // Serial.print("load cell: ");
  // Serial.println(loadCell.getWeight());
  // Serial.print("arm angle: ");
  // Serial.println(read_arm_servo_angle());

  updateDoubleKnock();

  // if (!monitor_switch)
  // {
  //   Serial.println("switch offed");
  //   delay(1000);
  //   return;
  //}
  // Serial.println("=========== entered main loop ===========");
  // if (first_time_entry)
  // {
  //   reset_drink_timer(start_time);
  //   first_time_entry = false;
  //   Serial.println("first time entry!");
  // }

  // // if cup leaved the mat, reset timer
  // while (cup_exist(loadCell) == false)
  // {
  //   first_time_entry = true;
  //   delay(100);
  //   Serial.println("No cup detected!");
  // }

  // check_temp_fan(fan_servo_state, fan_motor_state, ARM_LOW_ANGLE, armServo, fanServo, loadCell);

  // // just need to remid drink, as in the next loop, if the cup is taken, the wile loop will trap it and wait until cup being put back.
  // // also checked cup exist here because during check_temp_fan actions, the system do not take inputs, so if user take cup away during action,
  // // no reminding needed here.
  // if (check_drink_timer(start_time) && cup_exist(loadCell))
  // {
  //   remind_drink(matrix);
  // }
}

void updateDoubleKnock()
{
  int value = analogRead(MICROPHONE_DATA_PIN);
  unsigned long now = millis();

  // 上升沿检测：只有从低于阈值跨到高于阈值时，才算一次新敲击
  bool risingEdge = (value > MICROPHONE_THRESHOLD && prevValue <= MICROPHONE_THRESHOLD);

  if (risingEdge)
  {
    // 消抖：避免一次敲击因为震动产生多个脉冲
    if (now - lastTriggerTime >= MICROPHONE_DEBOUNCE_TIME)
    {
      handleKnock(now);
      lastTriggerTime = now;
    }
  }

  // 如果已经有第一次敲击，但等太久还没来第二次，就超时复位
  if (knockState == WAIT_SECOND)
  {
    if (now - firstKnockTime > MICROPHONE_MAX_INTERVAL)
    {
      knockState = IDLE;
    }
  }

  prevValue = value;
}

void handleKnock(unsigned long now)
{
  switch (knockState)
  {
  case IDLE:
    // 记录第一次敲击时间
    firstKnockTime = now;
    knockState = WAIT_SECOND;
    break;

  case WAIT_SECOND:
    // 判断第二次敲击是否在有效时间窗内
    if (now - firstKnockTime >= MICROPHONE_MIN_INTERVAL &&
        now - firstKnockTime <= MICROPHONE_MAX_INTERVAL)
    {
      onDoubleKnockDetected();
    }

    // 不管成功失败，都重新开始
    knockState = IDLE;
    break;
  }
}

void onDoubleKnockDetected()
{
  Serial.println("Double Knock Detected!");
  monitor_switch = !monitor_switch;
  Serial.print("monitor switch turned to ");
  Serial.println(monitor_switch);
}
