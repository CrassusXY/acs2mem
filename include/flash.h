#ifndef FLASHMEMORYPACKAGE
#define FLASHMEMORYPACKAGE

#include "flash.h"
#include <Arduino.h>

#define PACKAGE_SIZE sizeof(measure)
#define MEMORY_SIZE 20 * 100 * PACKAGE_SIZE
#define SECTOR_SIZE 4096


//Struct containing data to be saved
struct measure {
    uint32_t timeStamp;
    uint8_t state;
    float pressure;

    // IMU:
    float accelX, accelY, accelZ;
    float gyroX, gyroY, gyroZ;
    float magX, magY, magZ;
};


class FlashMemoryPackage {
private:
    uint32_t addrR, addrW;
    void writeField(const void *data, size_t size);
    void readField(void *data, size_t size);

public:
    int init();
    int savePackage(const measure &_package);
    measure readPackage();
};
int FlashMemoryPackage::init() {
    Serial.print("Initializing flash memory for: ");
    Serial.print(MEMORY_SIZE);
    Serial.println(" bytes.");

    addrR = 0x150000;
    addrW = 0x150000;

    //Erase memory
    for(uint32_t i = addrW; i < addrW + MEMORY_SIZE; i += SECTOR_SIZE) {
        ESP.flashEraseSector(i/SECTOR_SIZE);
    }
    return 0;
}

void FlashMemoryPackage::writeField(const void *data, size_t size) {
    ESP.flashWrite(addrW, (uint32_t*) data, size);
    addrW += size;
}

void FlashMemoryPackage::readField(void *data, size_t size) {
    ESP.flashRead(addrR, (uint32_t*) data, size);
    addrR += size;
}


int FlashMemoryPackage::savePackage(const measure &_package) {
    writeField(&_package.timeStamp, sizeof(uint32_t));
    writeField(&_package.state, sizeof(uint8_t));
    writeField(&_package.pressure, sizeof(float));
    writeField(&_package.accelX, sizeof(float));
    writeField(&_package.accelY, sizeof(float));
    writeField(&_package.accelZ, sizeof(float));
    writeField(&_package.gyroX, sizeof(float));
    writeField(&_package.gyroY, sizeof(float));
    writeField(&_package.gyroZ, sizeof(float));
    writeField(&_package.magX, sizeof(float));
    writeField(&_package.magY, sizeof(float));
    writeField(&_package.magZ, sizeof(float));
    return 0;
}

measure FlashMemoryPackage::readPackage() {
    measure _package;
    readField(&_package.timeStamp, sizeof(uint32_t));
    readField(&_package.state, sizeof(uint8_t));
    readField(&_package.pressure, sizeof(float));
    readField(&_package.accelX, sizeof(float));
    readField(&_package.accelY, sizeof(float));
    readField(&_package.accelZ, sizeof(float));
    readField(&_package.gyroX, sizeof(float));
    readField(&_package.gyroY, sizeof(float));
    readField(&_package.gyroZ, sizeof(float));
    readField(&_package.magX, sizeof(float));
    readField(&_package.magY, sizeof(float));
    readField(&_package.magZ, sizeof(float));
    return _package;
}

#endif