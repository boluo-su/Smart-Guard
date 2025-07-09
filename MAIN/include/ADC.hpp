#pragma once

#include "main.hpp"

#define ADC_0 "in_voltage0_raw"
#define ADC_1 "in_voltage1_raw"
#define ADC_2 "in_voltage2_raw"
#define ADC_3 "in_voltage3_raw"
#define ADC_4 "in_voltage4_raw"
#define ADC_5 "in_voltage5_raw"
#define ADC_6 "in_voltage6_raw"
#define ADC_7 "in_voltage7_raw"

#define ADC_SCALE "/sys/bus/iio/devices/iio:device0/in_voltage_scale"

double AdcFunDemo();

