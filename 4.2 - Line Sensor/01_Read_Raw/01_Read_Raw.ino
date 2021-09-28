#include <QTRSensors.h>

QTRSensors lineSensor;

const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];

const uint8_t sensorPins[] = {3, 4, 5, 6};

void setup()
{
  // configure the sensors
  lineSensor.setTypeRC();
  lineSensor.setSensorPins(sensorPins, SensorCount);
  lineSensor.setEmitterPin(2);
  lineSensor.setTimeout(1500);

  Serial.begin(9600);
}


void loop()
{
  // read raw sensor values
  lineSensor.read(sensorValues);

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
