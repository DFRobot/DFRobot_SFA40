/*!
 * @file getSensorData.ino
 * @brief This example shows how to obtain data collected by SFA40, including HCHO and temperature and humidity data
 * @copyright  Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [fary](feng.yang@dfrobot.com)
 * @version V1.0
 * @date 2025-04-08
 * @url https://github.com/DFRobot/DFRobot_SFA40
 */
#include "DFRobot_SFA40.h"
DFRobot_SFA40 SFA40;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.print("SFA40 init...");
  while(SFA40.begin()!=0){
    Serial.print("failed,Not found SFA40!");
  }
  Serial.println("successed");
  SFA40.startMeasurement();
  //uint8_t* id = SFA40.getSerialNumber();
  // Serial.print("SerialNumber:");
  // for(uint8_t i=0;i<10;i++){
  //   Serial.print(id[i]);
  //   Serial.print(" ");
  // }
  // Serial.println();

}
  
void loop() {
  uint8_t status = SFA40.readMeasurementData();
  if(status==0){
    Serial.println("The sensor is ready and the data is reliable! ");


    Serial.print("TemperatureC: ");
    Serial.print(SFA40.temperatureC);
    Serial.println(" C");

    Serial.print("TemperatureF:");
    Serial.print(SFA40.temperatureF);
    Serial.println(" F");
  
    Serial.print("humidity:");
    Serial.print(SFA40.humidity);
    Serial.println(" %RH");
  
    Serial.print("HCHO:");
    Serial.print(SFA40.HCHO);
    Serial.println(" ppb");  
    // static int number=0;
    // if(number==100){
    //   SFA40.stopMeasurement();
    //   Serial.print("The sensor has stopped measuring!");
    //   while(1);
    // }
    // number++;
  }else if(status&0x01){
    Serial.println("The sensor is not ready!");
  }else if(status&0x02){
    Serial.println("Sensor is not up to specification!");
  }

   delay(1000);
}
