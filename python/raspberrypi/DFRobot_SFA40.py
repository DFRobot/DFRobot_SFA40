# -*- coding: utf-8 -*-
'''
  @file DFRobot_SFA40.py
  @brief Define the basic structure and methods of the DFRobot_SFA40 class.
  @copyright   Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT license (MIT)
  @author [fary](feng.yang@dfrobot.com)
  @version  V1.0
  @date  2025-04-10
  @https://github.com/DFRobot/DFRobot_SFA40
'''
from smbus import SMBus
import struct

class DFRobot_SFA40:
    SAF40_COMMAND_START      = 0x00AC
    SAF40_COMMAND_READ       = 0xE06D
    SAF40_COMMAND_STOP       = 0x50D2
    SAF40_COMMAND_ID         = 0x0559
    SAF40_CRC_INITIAL_VALUE  = 0xFF
    SAF40_CRC_POLYNOMIAL     = 0x31
    
    def __init__(self, bus=1, address=0x5D):
        self.bus = SMBus(bus)
        self.address = address
        self._buf = [0] * 15

    def _write_command(self, command):
        '''
        @fn _write_command
        @brief Write command functions
        @param command sensor control command
        @return None
        '''
        self.bus.write_i2c_block_data(self.address,(command >> 8) & 0xFF,[command & 0xFF])
    
    def _read_bytes(self, length):
        '''
        @fn _read_bytes
        @brief Read register functions
        @param length The length of the data to be written
        @return data
        '''
        return self.bus.read_i2c_block_data(self.address,0x00,length)
        
    
    def _calc_crc(self, data):
        '''
        @fn _calc_crc
        @brief CRC check
        @param data Data to be verified
        @return  The results of the examination       
        '''
        crc = self.SAF40_CRC_INITIAL_VALUE
        for byte in data:
            crc ^= byte
            for _ in range(8):
                if crc & 0x80:
                    crc = (crc << 1) ^ self.SAF40_CRC_POLYNOMIAL
                else:
                    crc <<= 1
                crc &= 0xFF
        return crc

    def begin(self):
        '''
        @fn begin
        @brief Check whether the SFA40 device exists on the IIC bus.
        @return Whether the sensor device is found.
        @retval 0: Sensor device exists, -1: Sensor device does not exist.
        '''
        try:
            self.bus.write_byte(self.address, 0)
            self.stop_measurement()
            return 0
        except Exception as e:
            print("Init error: {}".format(e))
            return -1
    def start_measurement(self):
        '''
        @fn start_measurement
        @brief start measurement
        '''
        self._write_command(self.SAF40_COMMAND_START)
    
    def stop_measurement(self):
        '''
        @fn stop_measurement
        @brief stop measurement
        '''
        self._write_command(self.SAF40_COMMAND_STOP)
    
    def read_measurement_data_raw(self):
        '''
        @fn read_measurement_data_raw
        @brief read measurement data
        @return int(0-2)
        @retval 0:The sensor is ready and the data is reliable! 
        @retval 1:The sensor is not ready!
        @retval 2:Sensor is not up to specification!
        '''
        self._write_command(self.SAF40_COMMAND_READ)
        self._buf = self._read_bytes(12)
        self.temperature_c = float('nan')
        self.temperature_f = float('nan')
        self.HCHO = float('nan')
        self.humidity = float('nan')
        if self._buf[10]==0:
            chunk = self._buf[0:3]
            if self._calc_crc(chunk[:2]) == chunk[2]:
                self.HCHO = (chunk[0] * 256 + chunk[1]) * 0.1
            chunk = self._buf[3:6]
            if self._calc_crc(chunk[:2]) == chunk[2]:
                self.humidity = 125.0 * (chunk[0] * 256 + chunk[1]) / 65535 - 6
            chunk = self._buf[6:9]
            if self._calc_crc(chunk[:2]) == chunk[2]:
                self.temperature_c = 175.0 * (chunk[0] * 256 + chunk[1]) / 65535 - 45
                self.temperature_f = 315.0 * (chunk[0] * 256 + chunk[1]) / 65535 - 49
        elif self._buf[10] & 0x01:
            return 1
        elif self._buf[10] & 0x02:
            return 2
        return 0
    
    def get_serial_number(self):
        '''
        @fn get_serial_number
        @brief get serial number
        @return serial number
        '''
        # Clear buffer
        self._buf = [0] * 9
        self._write_command(self.SAF40_COMMAND_ID)
        self._buf = self._read_bytes(9)
        
        serial_number = []
        for i in range(0, 9, 3):
            crc_result = self._calc_crc(self._buf[i:i+2])
            
            if crc_result == self._buf[i+2]:
                serial_number.append(self._buf[i])
                serial_number.append(self._buf[i+1])
            else:
                return None
    
        return bytes(serial_number)