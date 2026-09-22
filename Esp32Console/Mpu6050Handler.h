#pragma once

#include <Wire.h>
#include <MPU6050_light.h>


struct MPUData {
  //angles
  float yaw;    //0 if ENABLE_Z_AXIS_ANGLE not defined
  float pitch;
  float roll;

  //acceleration
  float accX;
  float accY;
  float accZ;
};

MPUData getMPUData();

bool  initMPU();

void  updateMPU();          
void  printMPUData();      

void  measureDrift();
void calibrateMpu();
//float getCorrectedYaw();