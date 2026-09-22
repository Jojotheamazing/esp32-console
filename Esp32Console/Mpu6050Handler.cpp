#include <Wire.h>
#include <MPU6050_light.h>
#include <math.h>
#include "Mpu6050Handler.h"

//ignore updated to use same i2c as mcp
#define MPU_SDA_PIN 10
#define MPU_SCL_PIN 11
#define MPU_INT_PIN 12

#define OUTPUT_READABLE_YAWPITCHROLL
#define OUTPUT_READABLE_REALACCEL
// #define ENABLE_Z_AXIS_ANGLE

static MPU6050* mpu = nullptr;

static float gyroZdrift = 0;
static float correctedYaw = 0;
static unsigned long lastYawTime = 0;

static const int DRIFT_SAMPLES = 3000;

void measureDrift() {
  Serial.println("Measuring gyro Z drift, keep sensor perfectly still...");
  float sum = 0;
  for (int i = 0; i < DRIFT_SAMPLES; i++) {
    mpu->update();
    sum += mpu->getGyroZ();
    delay(2);
  }
  gyroZdrift = sum / DRIFT_SAMPLES;
  Serial.print("Drift rate: ");
  Serial.print(gyroZdrift, 4);
  Serial.println(" deg/s  (will be subtracted continuously)");
}

static void updateCorrectedYaw() {
  unsigned long now = millis();
  float dt = (now - lastYawTime) * 0.001f;
  lastYawTime = now;

  float gyroZ = mpu->getGyroZ();

  if (fabs(gyroZ) < 0.3f)
    gyroZdrift = gyroZdrift * 0.999f + gyroZ * 0.001f;

  gyroZ -= gyroZdrift;

  if (fabs(gyroZ) < 0.15f)
    gyroZ = 0;

  correctedYaw += gyroZ * dt;
}

bool initMPU() {
  //Wire.begin(MPU_SDA_PIN, MPU_SCL_PIN);
  //Wire.setClock(400000);
  delay(100);

  mpu = new MPU6050(Wire);

  Serial.println(F("Initializing MPU6050..."));
  byte status = mpu->begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);

  if (status != 0) {
    Serial.println(F("MPU6050 connection failed! Check wiring."));
    delete mpu;
    mpu = nullptr;
    return false;
  }

  Serial.println(F("Calculating offsets, do not move MPU6050..."));
  delay(1000);
  mpu->calcOffsets();
  Serial.println(F("Offsets done."));

#ifdef ENABLE_Z_AXIS_ANGLE
  measureDrift();
#endif

  lastYawTime = millis();
  Serial.println(F("Ready!"));
  return true;
}

void calibrateMpu() {
  Serial.println(F("Calculating offsets, do not move MPU6050..."));
  //delay(1000);
  mpu->calcOffsets();
  Serial.println(F("Offsets done."));

#ifdef ENABLE_Z_AXIS_ANGLE
  measureDrift();
#endif

  lastYawTime = millis();
  Serial.println(F("Ready!"));
  return;
}

void updateMPU() {
  if (!mpu) return;
  mpu->update();

#ifdef ENABLE_Z_AXIS_ANGLE
  updateCorrectedYaw();
#endif
}

MPUData getMPUData() {
  MPUData data = { 0 };
  if (!mpu) return data;

#ifdef ENABLE_Z_AXIS_ANGLE
  data.yaw = correctedYaw;
#else
  data.yaw = 0;
#endif

  data.pitch = mpu->getAngleX();
  data.roll = mpu->getAngleY();

  data.accX = mpu->getAccX();
  data.accY = mpu->getAccY();
  data.accZ = mpu->getAccZ();

  return data;
}

void printMPUData() {
  if (!mpu) return;

#ifdef OUTPUT_READABLE_YAWPITCHROLL
  Serial.print("ypr");

#ifdef ENABLE_Z_AXIS_ANGLE
  Serial.print("\t");
  Serial.print(correctedYaw);
#endif

  Serial.print("\t");
  Serial.print(mpu->getAngleY());
  Serial.print("\t");
  Serial.println(mpu->getAngleX());
#endif

#ifdef OUTPUT_READABLE_REALACCEL
  Serial.print("areal\t");
  Serial.print(mpu->getAccX());
  Serial.print("\t");
  Serial.print(mpu->getAccY());
  Serial.print("\t");
  Serial.println(mpu->getAccZ());
#endif
}