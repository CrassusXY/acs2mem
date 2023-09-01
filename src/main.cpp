#include "flash.h"

void printPackage(const measure &_package);

FlashMemoryPackage _memory;

measure _measure{2, 1, 2, 3, 4, 5.44, 6, 7, 8, 9, 10, -11};
uint8_t test = 1;
int idx = 0;

void setup(void)
{
  // Serial setup
  Serial.begin(115200);
  while(!Serial);
  delay(1000);
  Serial.println("FLASH test"); Serial.println("");
  
  //init
  Serial.println(millis());
  _memory.init();
  Serial.println(millis());
  _measure.state = 0;
}

void loop(void)
{
  //Zapis
  if(test==1) {  
    Serial.println("Writing...");
    Serial.println(millis());
    for(int i = 0; i < MEMORY_SIZE/PACKAGE_SIZE; i++) {
      // mock data
      _measure.timeStamp = millis();

      _measure.accelX -= 0.1;
      _measure.accelY -= 0.1;
      _measure.accelZ-= 0.1;

      _measure.magX -= 0.1;
      _measure.magY -= 0.1;
      _measure.magZ -= 0.1;

      _measure.gyroX -= 0.1;
      _measure.gyroY -= 0.1;
      _measure.gyroZ -= 0.05;

      _memory.savePackage(_measure);
    }
    Serial.println(millis());
    Serial.println("Ended writing successfully");
    test = 0;
  }

  //Odczyt
  if(test==0) {
    for(int i = 0; i < MEMORY_SIZE/PACKAGE_SIZE/10; i++) {
      Serial.print(idx); Serial.print(" - ");
      idx++;
      printPackage(_memory.readPackage());
    }

    test = 2;
  }
}

void printPackage(const measure &_package)
{
    Serial.print(_package.timeStamp);
    Serial.print(", ");
    Serial.print(_package.state);
    Serial.print(", ");
    Serial.print(_package.pressure, 2);  // Assuming we want 2 decimal places
    Serial.print(", ");
    Serial.print(_package.accelX, 2);
    Serial.print(", ");
    Serial.print(_package.accelY, 2);
    Serial.print(", ");
    Serial.print(_package.accelZ, 2);
    Serial.print(", ");
    Serial.print(_package.gyroX, 2);
    Serial.print(", ");
    Serial.print(_package.gyroY, 2);
    Serial.print(", ");
    Serial.print(_package.gyroZ, 2);
    Serial.print(", ");
    Serial.print(_package.magX, 2);
    Serial.print(", ");
    Serial.print(_package.magY, 2);
    Serial.print(", ");
    Serial.println(_package.magZ, 2);
}