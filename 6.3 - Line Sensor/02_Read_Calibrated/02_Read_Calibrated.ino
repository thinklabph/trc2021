#include <QTRSensors.h>

QTRSensors lineSensor;

const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];

const uint8_t sensorPins[] = {3, 4, 5, 6};

void setup()
{
  Serial.begin(9600);
  
  lineSensor.setTypeRC();
  lineSensor.setSensorPins(sensorPins, SensorCount);
  lineSensor.setEmitterPin(2);
  lineSensor.setTimeout(2500);
  
  Serial.println("Calibrating . . .");
  Serial.println("Slowly move the sensor across the electrical tape");
  // 2.5 ms RC read timeout (default) * 10 reads per calibrate() call
  // = ~25 ms per calibrate() call.
  // Call calibrate() 400 times to make calibration take about 10 seconds.
  for (uint16_t i = 0; i < 400; i++)
  {
    lineSensor.calibrate();
  }
  Serial.println();
  
  Serial.print("Minimum Values: ");
  // print the calibration minimum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(lineSensor.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();

  Serial.print("Maximum Values: ");
  // print the calibration maximum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(lineSensor.calibrationOn.maximum[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println("Done calibrating!");
  delay(1000);
  Serial.println();
}

void loop()
{
  // read calibrated sensor values and obtain a measure of the line position
  // from 0 to 5000 (for a white line, use readLineWhite() instead)
  uint16_t position = lineSensor.readLineBlack(sensorValues);

  // print the sensor values as numbers from 0 to 1000, where 0 means maximum
  // reflectance and 1000 means minimum reflectance, followed by the line
  // position
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println(position);

  delay(250);
}
