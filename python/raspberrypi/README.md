# DFRobot_SFA40

* [中文版](./README_CN.md)

The SFA40 is a formaldehyde (HCHO) sensor with remarkably high sensitivity and accuracy in the field due to exceptionally low cross-sensitivity to typical indoor gases. Developed for air purifiers, air conditionersand indoor air quality monitors, the SFA40 meets the key requirements of miniature size, low power consumption and high accuracy even in a background of other volatile organic compounds. The sensor is suitable for accurately detecting formaldehyde concentrations below the limits of WHO, ASHRAE, WELL and Chinese National Standard GB/T 18883-2022

The robust sensor has a long lifetime due to its advanced anti-dry technology. Each SFA40 is factorycalibrated and can be easily integrated via I2C interface into the final device. The low power consumption  allows for integration into battery-driven devices. This makes SFA40 a reliable, easy-to-use and high quality formaldehyde sensing solution.
![Product Image](../../resources/images/SFA40.png)

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

This library provides a way to drive the SFA40 under a Raspberry Pi to obtain formaldehyde, temperature and humidity, and the serial number of the sensor.


## Installation

To use this library, first download the library to your Raspberry Pi and then open the use cases folder. To perform a use case demox.py, enter the python demox.py on the command line.
This library depends on the SMBUS library, please ensure that SMBUS has been installed before using this library. Installation: pip install smbus2

## Methods
```python
  
    def begin(self)
        """
        @fn begin
        @brief Check whether the SFA40 device exists on the IIC bus.
        @return Whether the sensor device is found.
        @retval 0: Sensor device exists, -1: Sensor device does not exist.
        """
    def start_measurement(self)
        """
        @fn start_measurement
        @brief start measurement
        """
    def stop_measurement(self)
        """
        @fn stop_measurement
        @brief stop measurement
        """
    def read_measurement_data_raw(self)
        """
        @fn read_measurement_data_raw
        @brief read measurement data
        @return int(0-2)
        @retval 0:The sensor is ready and the data is reliable! 
        @retval 1:The sensor is not ready!
        @retval 2:Sensor is not up to specification!
        """
    def get_serial_number(self)
        """
        @fn get_serial_number
        @brief get serial number
        @return serial number
        """

```

## Compatibility

| MCU         | Work Well | Work Wrong  | Untested | Remarks |
| ------------ | :--: | :----: | :----: | :--: |
| RaspberryPi4 |  √   |        |        |      |

* Python version 

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :--: | :----: | :----: | ---- |
| Python2 |  √   |        |        |      |
| Python3 |  √   |        |        |      |
## History 

- 2025/03/17 - Version 1.0.0 released.

## Credits

Written by fary(feng.yang@dfrobot.com), 2025.04.10 (Welcome to our [website](https://www.dfrobot.com/))



