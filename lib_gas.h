#ifndef LIB_GAS_H
#define LIB_GAS_H

#include <Arduino.h>
#include <cstdint>
#include <driver/adc.h>

class LibGas {
private:
    uint16_t ADC_MAX_VALUE;
    uint16_t ADC_MIN_VALUE;
    uint8_t ADC_SAMPLES;
    uint16_t ADC_SAMPLE_DELAY;

public:
    LibGas(uint16_t maxValue = 4095U, uint16_t minValue = 0U, uint8_t samples = 3U, uint16_t sampleDelay = 100U);
    bool init();
    bool read(uint16_t* no2, uint16_t* nh3, uint16_t* co);
};

#endif
