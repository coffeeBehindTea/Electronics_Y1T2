// #include <Arduino.h>

// // --- 用户配置区 ---
// // 定义传感器连接的引脚，建议使用 A1-A5
// const int sensorPin = A1;

// // 如果你用的是 TMP36，请把下面这行改为 true
// const bool isTMP36 = false;

// // 采样次数，用于取平均值，减少读数波动
// const int numSamples = 20;

// void setup()
// {
//     // 1. 初始化串口，用于输出数据
//     Serial.begin(9600);

//     // 等待串口连接（针对某些板子，可选）
//     delay(1000);

//     // 2. 设置基准电压 (关键修复！)
//     // Arduino Uno R4 WiFi 使用 AR_INTERNAL，内部电压固定为 1.5V
//     // 这比使用默认的 5V 基准精度高很多
//     analogReference(AR_INTERNAL);

//     // 3. 设置ADC分辨率
//     // Uno R4 支持最高 14位 (0-16383)，这里我们使用默认的 10位 (0-1023)
//     // 保持与老代码兼容，计算更简单
//     analogReadResolution(10);

//     Serial.println("温度传感器初始化完成 (Uno R4 WiFi Mode)");
// }

// void loop()
// {
//     // --- 第一步：多次采样取平均值 (平滑处理) ---
//     long totalReading = 0;
//     for (int i = 0; i < numSamples; i++)
//     {
//         totalReading += analogRead(sensorPin);
//         delay(10); // 每次读取间隔10ms
//     }
//     // 计算平均读数
//     float averageReading = totalReading / (float)numSamples;

//     // --- 第二步：将读数转换为电压 (mV) ---
//     // 公式：读数 * (基准电压 / 分辨率)
//     // Uno R4 AR_INTERNAL = 1500 mV
//     // 10位分辨率 = 1024
//     float voltageMilliVolts = averageReading * (1500.0 / 1024.0);

//     // --- 第三步：将电压转换为温度 (°C) ---
//     float temperatureC = 0;

//     if (isTMP36)
//     {
//         // TMP36 公式: (电压mV - 500) / 10
//         temperatureC = (voltageMilliVolts - 500.0) / 10.0;
//     }
//     else
//     {
//         // LM35 公式: 电压mV / 10
//         temperatureC = voltageMilliVolts / 10.0;
//     }

//     // --- 第四步：打印结果 ---
//     Serial.print("Raw ADC: ");
//     Serial.print(averageReading, 1); // 保留1位小数
//     Serial.print(" | Voltage: ");
//     Serial.print(voltageMilliVolts, 1);
//     Serial.print(" mV | Temp: ");
//     Serial.print(temperatureC, 2); // 保留2位小数
//     Serial.println(" C");

//     delay(1000); // 每秒刷新一次
// }