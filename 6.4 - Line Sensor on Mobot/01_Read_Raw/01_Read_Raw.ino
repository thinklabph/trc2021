#include <QTRSensors.h>

QTRSensors qtr_front;
QTRSensors qtr_back;
QTRSensors qtr_left;
QTRSensors qtr_right;

const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];

void setupLineSensors()
{
  const uint16_t def_timeout = 1000;
  Serial.println("initializinf line sensors . . .");
  
  //front line sensor
  qtr_front.setTimeout(def_timeout);
  qtr_front.setTypeRC();
  qtr_front.setSensorPins((const uint8_t[]) {
    A0, A1, A2, A3
  }, SensorCount);
  qtr_front.setEmitterPin(33);
/*
  //back line sensor
  qtr_back.setTimeout(def_timeout);
  qtr_back.setTypeRC();
  qtr_back.setSensorPins((const uint8_t[]) {
    A15, A14, A13, A12
  }, SensorCount);
  qtr_back.setEmitterPin(32);
  
  //left line sensor
  qtr_left.setTimeout(def_timeout);
  qtr_left.setTypeRC();
  qtr_left.setSensorPins((const uint8_t[]) {
    A7, A6, A5, A4
  }, SensorCount);
  qtr_left.setEmitterPin(30);

  //right line sensor
  qtr_right.setTimeout(def_timeout);
  qtr_right.setTypeRC();
  qtr_right.setSensorPins((const uint8_t[]) {
    A8, A9, A10, A11
  }, SensorCount);
  qtr_right.setEmitterPin(31);*/
}

void setup()
{
  Serial.begin(9600);

  //configure line sensors
  setupLineSensors();
}


void loop()
{
  // read raw sensor values
  qtr_front.read(sensorValues);

  // print the sensor values as numbers from 0 to 2500, where 0 means maximum
  // reflectance and 2500 means minimum reflectance
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();

  delay(250);
}
