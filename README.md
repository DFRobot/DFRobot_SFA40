# DFRobot_SFA40

* [中文版](./README_CN.md)

The SFA40 is a formaldehyde (HCHO) sensor with remarkably high sensitivity and accuracy in the field due to exceptionally low cross-sensitivity to typical indoor gases. Developed for air purifiers, air conditionersand indoor air quality monitors, the SFA40 meets the key requirements of miniature size, low power consumption and high accuracy even in a background of other volatile organic compounds. The sensor is suitable for accurately detecting formaldehyde concentrations below the limits of WHO, ASHRAE, WELL and Chinese National Standard GB/T 18883-2022

The robust sensor has a long lifetime due to its advanced anti-dry technology. Each SFA40 is factorycalibrated and can be easily integrated via I2C interface into the final device. The low power consumption  allows for integration into battery-driven devices. This makes SFA40 a reliable, easy-to-use and high quality formaldehyde sensing solution.
   
   
![正反面svg效果图](./resources/images/SFA40.png)

## Product Link（https://www.dfrobot.com/)
    SEN0661 Gravity: SFA40 HCHO Sensor
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)


## Summary


This library provides a way to drive the SFA40 under the Arduino IDE, which can obtain formaldehyde, temperature and humidity, and the serial number of the sensor.

## Installation

1.To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo 
## Methods
```C++

  /**
   * @fn begin
   * @brief Check whether the SFA40 device exists on the IIC bus.
   * @return Whether the sensor device is found.
   * @retval 0: Sensor device exists, other values: Sensor device does not exist.
  */
  byte begin(void);
  /**
   * @fn startMeasurement
   * @brief start measurement
  */
  void startMeasurement();
  
  /**
   * @fn stopMeasurement
   * @brief stop measurement
  */
  void stopMeasurement();

  /**
   * @fn getSerialNumber
   * @brief get serial number
   * @return serial number
  */
  uint8_t* getSerialNumber();

  /**
   * @fn readMeasurementData
   * @brief read measurement data
   * @return int(0-2)
   * @retval 0:The sensor is ready and the data is reliable! 
   * @retval 1:The sensor is not ready!
   * @retval 2:Sensor is not up to specification!
  */
  uint8_t readMeasurementData();


```

## Compatibility

MCU                | Work Well | Work Wrong  | Untested | Remarks |
------------------ | :----------: | :----------: | :---------: | -----
Arduino UNO        |      √       |              |             | 
Arduino MEGA2560        |      √       |              |             | 
Arduino Leonardo        |      √       |              |             | 
FireBeetle-ESP32        |      √       |              |             | 
FireBeetle-ESP8266        |      √       |              |             | 
FireBeetle-M0        |      √       |              |             | 
Micro:bit        |      √       |              |             |

## History

- Date 2025-04-10
- Version V1.0.0
## Credits
Written by fary(feng.yang@dfrobot.com), 2025.04.10 (Welcome to our [website](https://www.dfrobot.com/))
