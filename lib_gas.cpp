#include "lib_gas.h"

LibGas::LibGas(uint16_t maxValue, uint16_t minValue, uint8_t samples, uint16_t sampleDelay)
    : ADC_MAX_VALUE(maxValue), ADC_MIN_VALUE(minValue), ADC_SAMPLES(samples), ADC_SAMPLE_DELAY(sampleDelay) {}

bool LibGas::init() {
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);
    return true;
}

bool LibGas::read(uint16_t* no2, uint16_t* nh3, uint16_t* co) {
    if (!no2 || !nh3 || !co) {
        return false;
    }

    uint16_t tempNo2 = 0U;
    uint16_t tempNh3 = 0U;
    uint16_t tempCo = 0U;
    uint8_t count = 0U;
    bool result = true;

    while (result && count < ADC_SAMPLES) {
        if (count > 0U) {
            delay(ADC_SAMPLE_DELAY);
        }

        int temp = adc1_get_raw(ADC1_CHANNEL_6);
        if (temp >= ADC_MIN_VALUE && temp <= ADC_MAX_VALUE) {
            tempNo2 += (uint16_t)temp;
        } else {
            result = false;
        }

        if (result) {
            temp = adc1_get_raw(ADC1_CHANNEL_7);
            if (temp >= ADC_MIN_VALUE && temp <= ADC_MAX_VALUE) {
                tempNh3 += (uint16_t)temp;
            } else {
                result = false;
            }
        }

        if (result) {
            temp = adc1_get_raw(ADC1_CHANNEL_4);
            if (temp >= ADC_MIN_VALUE && temp <= ADC_MAX_VALUE) {
                tempCo += (uint16_t)temp;
                count++;
            } else {
                result = false;
            }
        }
    }

    if (result) {
        *no2 = ADC_MAX_VALUE - (tempNo2 / ADC_SAMPLES);
        *nh3 = ADC_MAX_VALUE - (tempNh3 / ADC_SAMPLES);
        *co = ADC_MAX_VALUE - (tempCo / ADC_SAMPLES);
    }

    return result;
}