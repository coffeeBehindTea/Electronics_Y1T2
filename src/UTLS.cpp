#include "UTLS.h"


// true if temperature sensor connected
bool tmp_sensor_connected()
{
    int minv = INT_MAX;
    int maxv = INT_MIN;
    long sum = 0;

    for (int i = 0; i < 20; i++)
    {
        int v = analogRead(TEMP_DATA_PIN);
        sum += v;
        if (v < minv) minv = v;
        if (v > maxv) maxv = v;
        delay(10);
    }

    float avg = sum / 20.0f;
    float tmp = (avg * (1500.0 / 1024.0)) / 10.0;

    Serial.print("[debug] min=");
    Serial.print(minv);
    Serial.print(" max=");
    Serial.print(maxv);
    Serial.print(" diff=");
    Serial.print(maxv - minv);
    Serial.print(" avg=");
    Serial.print(avg);
    Serial.print(" tmp=");
    Serial.println(tmp);

    if ((maxv - minv < 20) && (tmp >= 20) && (tmp < 30))
        return true;

    return false;
}

// return temperature sensor reading in float
float read_temp_sensor()
{
    long sum = 0;

    for (int i = 0; i < 10; i++)
    {
        sum += analogRead(TEMP_DATA_PIN);
        delay(2);
    }

    float avg = sum / 10.0f;

    float voltage = avg * (3.3f / 1024.0f);

    return voltage * 100.0f;
}


float read_arm_servo_angle()
{
    int v = analogRead(ARM_SERVO_FEEDBACK_PIN);

    if (v < SERVO_FB_MIN) v = SERVO_FB_MIN;
    if (v > SERVO_FB_MAX) v = SERVO_FB_MAX;

    return (float)(v - SERVO_FB_MIN) * 270.0 / (SERVO_FB_MAX - SERVO_FB_MIN);
}

void set_servo_angle(Servo &servo, float angle)
{
    if (angle < 0) angle = 0;
    if (angle > 270) angle = 270;

    int pulse = 500 + angle * 2000.0 / 270.0;

    servo.writeMicroseconds(pulse);
}

// true if servo connected
bool servo_connected()
{
    int minv = INT_MIN;
    int maxv = INT_MAX;

    for (int i = 0; i < 20; i++)
    {
        int v = analogRead(ARM_SERVO_FEEDBACK_PIN);

        if (v < minv) minv = v;
        if (v > maxv) maxv = v;

        delay(5);
    }

    //if value not 0 or 1023 and has changes
    if (minv > 5 && maxv < 1018)
        return true;

    return false;
}


void reset_drink_timer(unsigned long &start_time)
{
    start_time = millis();
}

// true if its time to drink
bool check_drink_timer(unsigned long &start_time)
{
    return millis() - start_time >= TIMER_THRESHOLD;
}

//! dummy function
void remind_drink()
{

}

// true if cup exist
bool cup_exist(NAU7802 &loadCell)
{
    if (loadCell.available())
    {
        float weight = loadCell.getWeight();
        return weight > MIN_CUP_WEIGHT ? true : false;
    }
    else
    {
        return false;
    }
}

// true if arm at low position
bool arm_at_low(int arm_low_angle)
{
    return abs(read_arm_servo_angle() - arm_low_angle) < 1.5 ? true : false;
}

// true if arm at high position
bool arm_at_high(int arm_low_angle)
{
    return abs(read_arm_servo_angle() - arm_low_angle - ARM_HIGH_ANGLE) < 1.5 ? true : false;
}

// 'h' for move to high position, 'l' for move to low position
void move_arm(Servo &servo, int arm_low_angle, char p)
{
    if (p == 'h')
    {
        set_servo_angle(servo, ARM_HIGH_ANGLE  + arm_low_angle);
        delay(2000);
    }
    else if (p == 'l')
    {
        set_servo_angle(servo, arm_low_angle);
        delay(2000);
    }
}

//! dummy function
void move_fan(int &fan_servo_state)
{
    if (fan_servo_state == 0)
    {
        // rotate the fan toward the cup.
        delay(1000);
        fan_servo_state = 1;
    }
    else
    {
        // rotate the fan back.
        delay(1000);
        fan_servo_state = 0;
    }
}

//! dummy function
void turn_on_off_fan(int &fan_motor_state)
{
    if (fan_motor_state == 0)
    {
        // turn on;
        delay(10);
        fan_motor_state = 1;
    }
    else
    {
        // turn off
        delay(10);
        fan_motor_state = 0;
    }
}

// do sequense of action depends on the temperature
void check_temp_fan(int fan_servo_state, int fan_motor_state, int arm_low_angle, Servo &servo)
{
    if (read_temp_sensor() > MIN_HOT_TEMP) // if cooling needed
    {
        if (arm_at_low(arm_low_angle))
        {
            move_arm(servo, arm_low_angle, 'h');
            move_fan(fan_servo_state);
            turn_on_off_fan(fan_motor_state);
        }
    }
    else
    {
        if (arm_at_high(arm_low_angle))
        {
            turn_on_off_fan(fan_motor_state);
            move_fan(fan_servo_state);
            move_arm(servo, arm_low_angle, 'l');
        }
    }
}


