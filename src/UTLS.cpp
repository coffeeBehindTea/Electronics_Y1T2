#include "UTLS.h"



bool tmp_sensor_connected(int dataPin)
{
    int minv = INT_MAX;
    int maxv = INT_MIN;
    long sum = 0;

    for (int i = 0; i < 20; i++)
    {
        int v = analogRead(dataPin);
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


float read_servo_angle(int pin)
{
    int v = analogRead(pin);

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

bool servo_connected(int feedbackPin)
{
    int minv = INT_MIN;
    int maxv = INT_MAX;

    for (int i = 0; i < 20; i++)
    {
        int v = analogRead(feedbackPin);

        if (v < minv) minv = v;
        if (v > maxv) maxv = v;

        delay(5);
    }

    // 如果值不是0或1023并且有变化
    if (minv > 5 && maxv < 1018)
        return true;

    return false;
}