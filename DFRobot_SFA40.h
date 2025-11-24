/*!
 * @file DFRobot_SFA40.h
 * @brief DFRobot_SFA40 class infrastructure
 * @copyright  Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [fary](feng.yang@dfrobot.com)
 * @version V1.0
 * @date 2025-04-10
 * @url https://github.com/DFRobot/DFRobot_SFA40
 */
#ifndef _DFROBOT_SFA40_H_
#define _DFROBOT_SFA40_H_

#include <Arduino.h>
#include <Wire.h>



#define ENABLE_DBG 

#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define SAF40_COMMAND_START      0x00AC 
#define SAF40_COMMAND_READ       0xE06D 
#define SAF40_COMMAND_STOP       0x50D2 
#define SAF40_COMMAND_ID         0x0559 
#define SAF40_CRC_INITIAL_VALUE  0xFF
#define SAF40_CRC_POLYNOMIAL     0x31
#define SAF40_IIC_ADDRESS        0x5D
class DFRobot_SFA40{
public:
  /**
   * @fn DFRobot_SFA40
   * @brief Constructor, passing in IIC bus device
  */
  DFRobot_SFA40(TwoWire *pWire = &Wire)
  {
    _pWire=pWire;
    _deviceAddr=SAF40_IIC_ADDRESS;
  }
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
  void startMeasurement(void);
  
  /**
   * @fn stopMeasurement
   * @brief stop measurement
  */
  void stopMeasurement(void);

  /**
   * @fn getSerialNumber
   * @brief get serial number
   * @return serial number
  */
  uint8_t* getSerialNumber(void);

  /**
   * @fn readMeasurementData
   * @brief read measurement data
   * @return int(0-2)
   * @retval 0:The sensor is ready and the data is reliable! 
   * @retval 1:The sensor is not ready!
   * @retval 2:Sensor is not up to specification!
  */
  uint8_t readMeasurementData(void);
  float HCHO= NAN;  
  float humidity=NAN;
  float temperatureC=NAN;
  float temperatureF=NAN;
protected:

  /**
   * @fn writeReg
   * @brief Write command functions
   * @param command sensor control command
   * @return None
  */
  void writeReg(uint16_t command);
  

  /** 
   * @fn readReg
   * @brief Read register functions
   * @param command sensor control command
   * @param pBuf to write data to the storage cache
   * @param size The length of the data to be written
   * @return int
   * @retval -1: The incoming buffer is a null pointer
   * @retval 0: IIC communication failed
   * @retval >0: The number of bytes read
  */
  int readReg(uint16_t command, void* pBuf, size_t size);


  /** 
   * @fn calcCrc
   * @brief CRC check
   * @param data[] Data to be verified
   * @param length The length of the data to be verified
   * @return  The results of the examination
  */
  uint8_t calcCrc(uint8_t data[],uint8_t length);
private:
  TwoWire *_pWire;
  uint8_t _deviceAddr;  
  uint8_t _buf[15];
  uint8_t serialNumber[10];
};

#endif
