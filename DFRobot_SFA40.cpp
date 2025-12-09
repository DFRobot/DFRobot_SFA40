/*!
 * @file DFRobot_SFA40.cpp
 * @brief  Implementation of DFRobot_SFA40 class methods
 * @copyright  Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [fary](feng.yang@dfrobot.com)
 * @version V1.0
 * @date 2025-04-10
 * @url https://github.com/DFRobot/DFRobot_SFA40
 */
#include "DFRobot_SFA40.h"

byte DFRobot_SFA40::begin(void){
  _pWire->begin();
    _pWire->beginTransmission(_deviceAddr);
    return _pWire->endTransmission();
}
void DFRobot_SFA40::startMeasurement(void){
  writeReg(SAF40_COMMAND_START);
}


void DFRobot_SFA40::stopMeasurement(void){
  writeReg(SAF40_COMMAND_STOP);
}

uint8_t DFRobot_SFA40::calcCrc(uint8_t data[],uint8_t length){
  uint8_t crc = SAF40_CRC_INITIAL_VALUE;
  for(int i = 0; i < length; i++) {
    crc ^= data[i];
    for(uint8_t bit = 8; bit > 0; --bit) {
      if(crc & 0x80) {
        crc = (crc << 1) ^ SAF40_CRC_POLYNOMIAL;
      } else {
        crc = (crc << 1);
      }
    }
  }
  return crc;
}
uint8_t * DFRobot_SFA40::getSerialNumber(void){
    memset(_buf,0,9);
    readReg(SAF40_COMMAND_ID,_buf,9);
    uint8_t crcResult = 0;
    uint8_t index = 0;  
    for(int i = 0;i < 9;i+=3)
    {
      crcResult =  calcCrc(_buf+i,2);
      if(crcResult == _buf[i+2])
      {
        serialNumber[index++] = _buf[i];
        serialNumber[index++] = _buf[i+1];
      }
      else
      {
        return NULL;
      }
    }
    return serialNumber;
}


uint8_t DFRobot_SFA40::readMeasurementData(void){
  memset(_buf,0,12);
  readReg(SAF40_COMMAND_READ,_buf,12);
  // HCHO= NAN;  
  // humidity=NAN;
  // temperatureC=NAN;
  // temperatureF=NAN;
  if(_buf[10]==0){
    uint8_t data[3];
    data[0]=_buf[0];
    data[1]=_buf[1];
    data[2]=_buf[2];
    if(calcCrc(data,2)==data[2]){
      HCHO = (data[0]*256 +data[1])/10;  
    }
    data[0]=_buf[3];
    data[1]=_buf[4];
    data[2]=_buf[5];
    if(calcCrc(data,2)==data[2]){
      humidity =125.0 * ((data[0]*256 +data[1]) / 65535.0) -6;
      if(humidity<0){
        humidity=0;
      }
      if(humidity>100){
        humidity=100;
      }  
    }
    data[0]=_buf[6];
    data[1]=_buf[7];
    data[2]=_buf[8];
    if(calcCrc(data,2)==data[2]){
      temperatureC =175.0 * ((data[0]*256 +data[1]) / 65535.0) -45;  
      temperatureF =315.0 * ((data[0]*256 +data[1]) / 65535.0) -49;
    }
  }else if(_buf[10] & 0x01){
    return 1;
  }else if(_buf[10] & 0x02){
    return 2;
  }
  return 0;
}

void DFRobot_SFA40::writeReg(uint16_t command){
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(command>>8);
  _pWire->write(command & 0xFF);
  _pWire->endTransmission();
}
int DFRobot_SFA40::readReg(uint16_t command, void* pBuf, size_t size){
  if(pBuf == NULL){
    DBG("pBuf ERROR!! : null pointer");
    return -1;
    }
    uint8_t * _pBuf = (uint8_t *)pBuf;
    _pWire->beginTransmission(_deviceAddr);
    _pWire->write(command>>8);
    _pWire->write(command & 0xFF);
    if( _pWire->endTransmission() != 0){
    DBG("endTransmission ERROR!! : null pointer");  
    return 0;
    }
    _pWire->requestFrom(_deviceAddr, (uint8_t) size);
    for(size_t i = 0; i < size; i++){
      _pBuf[i] = _pWire->read();
    }
    return size;
}

