# -*- coding: utf-8 -*-
'''
  @file DFRobot_SFA40.py
  @brief This example shows how to obtain data collected by SFA40, including HCHO and temperature and humidity data
  @copyright   Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT license (MIT)
  @author [fary](feng.yang@dfrobot.com)
  @version  V1.0
  @date  2025-04-10
  @https://github.com/DFRobot/DFRobot_SFA40
'''
import time
import sys
sys.path.append("../")
from DFRobot_SFA40 import DFRobot_SFA40

sfa40 = DFRobot_SFA40(bus=1)
def setup():
  print("SFA40 init...")
  if sfa40.begin()!=0:
    print("failed,Not found SFA40!")
  print("successed")
  #print("serial number:{}.".format(sfa40.get_serial_number()))
  sfa40.start_measurement()
  time.sleep(1)

def loop():
  while True:
    status = sfa40.read_measurement_data_raw()
    if status==0 :
      print("The sensor is ready and the data is reliable! ")
      print("Temperature: {} ℃, {} ℉, humidity: {} %RH, HCHO: {} ppb".format(sfa40.temperature_c,sfa40.temperature_f,sfa40.humidity,sfa40.HCHO))
    elif status==1 :
      print("The sensor is not ready.")
    elif status==2:
      print("Sensor is not up to specification.")
    time.sleep(1)
    #number+=1
    #if number==100:
    #  sfa40.stop_measurement()
    #  print("The sensor has stopped measuring!")
    #  break
# Execute setup function
setup()
# Execute loop function
loop()