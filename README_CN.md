# DFRobot_SFA40

* [English Version](./README.md)

SFA40 是一款甲醛 （HCHO） 传感器，由于对典型室内气体的交叉敏感度极低，因此在现场具有非常高的灵敏度和准确性。SFA40 专为空气净化器、空调和室内空气质量监测器而开发，即使在其他挥发性有机化合物的背景下，也能满足微型尺寸、低功耗和高精度的关键要求。该传感器适用于准确检测低于 WHO、ASHRAE、WELL 和中国国家标准 GB/T 18883-2022 限值的甲醛浓度

由于其先进的防干技术，坚固的传感器具有较长的使用寿命。每个 SFA40 都经过工厂校准，可以通过 I2C 接口轻松集成到最终设备中。低功耗允许集成到电池驱动设备中。这使得 SFA40 成为可靠、易于使用且高质量的甲醛传感解决方案。

![正反面svg效果图](./resources/images/SFA40.png)

## 产品链接（ https://www.dfrobot.com.cn/ ）

SEN0661 Gravity: SFA40 甲醛传感器

## 目录

* [简介](#简介)
* [安装](#安装)
* [方法](#方法)
* [兼容性](#兼容性)
* [历史](#历史)
* [贡献者](#贡献者)

## 简介

本库提供了在Arduino IDE下驱动SFA40的办法，可获取甲醛、温湿度以及传感器的序列号。

## 安装

1.要使用此库，首先下载库文件，将其粘贴到 `\Arduino\libraries` 目录中，然后打开示例文件夹并运行其中的示例。

## 方法
```c++
  /**
   * @fn begin
   * @brief 查找IIC总线上是否存在SFA40设备
   * @return 是否发现传感器设备
   * @retval 0:存在传感器设备，其他值：不存在传感器设备
  */ 
  byte begin(void);
  /**
   * @fn startMeasurement
   * @brief 开始测量
  */
  void startMeasurement();
  
  /**
   * @fn stopMeasurement
   * @brief 停止测量
  */
  void stopMeasurement();

  /**
   * @fn getSerialNumber
   * @brief 获取SFA40唯一序列号
   * @return SFA40序列号
  */
  uint8_t* getSerialNumber();

  /**
   * @fn readMeasurementData
   * @brief 读取测量数据
   * @return int(0-2)
   * @retval 0:传感器数据已经准备好，数据有效！
   * @retval 1:传感器还没准备好！
   * @retval 2:传感器未达到规格！
  */
  uint8_t readMeasurementData();

```


## 兼容性

MCU                | 表现良好	|表现异常	|未测试	|备注 |
------------------ | :----------: | :----------: | :---------: | -----
Arduino UNO        |      √       |              |             | 
Arduino MEGA2560        |      √       |              |             | 
Arduino Leonardo        |      √       |              |             | 
FireBeetle-ESP32        |      √       |              |             | 
FireBeetle-ESP8266        |      √       |              |             | 
FireBeetle-M0        |      √       |              |             | 
Micro:bit        |      √       |              |             |


## 历史

- Date 2025-04-10
- Version V1.0.0


## 贡献者

Written by fary(feng.yang@dfrobot.com), 2025.04.10 (Welcome to our [website](https://www.dfrobot.com.cn/))
