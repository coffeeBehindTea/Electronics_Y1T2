
#include <Arduino.h>
#include <Wire.h>
#include "SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h"

NAU7802 myScale;

// 这里填入你刚才算出来的那个数字！
float myCalibrationFactor = 10;

void setup()
{
  Serial.begin(115200);
  Wire1.begin();

  if (myScale.begin(Wire1) == false)
  {
    Serial.println("连接失败");
    while (1)
      ;
  }

  Serial.println("--- 校准模式 ---");
  Serial.println("1. 请确保秤台上【没有任何物体】");
  Serial.println("2. 在串口监视器输入任何字符并回车开始清零...");
  while (!Serial.available())
    ;
  Serial.read();

  myScale.calculateZeroOffset();
  Serial.println("已清零。");

  Serial.println("3. 请放上一个【已知重量】的物体（例如 100g）");
  Serial.println("4. 放好后，在串口输入该物体的【实际克数】并回车...");
}

void loop()
{
  if (myCalibrationFactor == 0)
  {
    if (Serial.available())
    {
      float actualWeight = Serial.parseFloat(); // 读取你输入的克数
      if (actualWeight > 0)
      {
        // 获取当前原始读数差值
        long currentReading = myScale.getReading();
        long zeroOffset = myScale.getZeroOffset();

        // 计算系数：系数 = 原始差值 / 实际克数
        float newCalibrationFactor = (float)(currentReading - zeroOffset) / actualWeight;

        Serial.print("校准完成！你的校准系数是: ");
        Serial.println(newCalibrationFactor, 4);
        myCalibrationFactor = newCalibrationFactor;
        myScale.setCalibrationFactor(myCalibrationFactor);
        myScale.calculateZeroOffset(); // 启动时自动去皮
      }
    }
  }
  else
  {
    if (myScale.available())
    {
      // 现在 getWeight() 就会自动除以系数，返回真正的“克”了
      float weight = myScale.getWeight();

      Serial.print("当前重量: ");
      Serial.print(weight, 1); // 显示一位小数
      Serial.println(" g");
    }
    delay(200);
  }
}