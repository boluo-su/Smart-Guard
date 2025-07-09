#include "ADC.hpp"


#define ADC_0 "in_voltage0_raw"
#define ADC_1 "in_voltage1_raw"
#define ADC_2 "in_voltage2_raw"
#define ADC_3 "in_voltage3_raw"
#define ADC_4 "in_voltage4_raw"
#define ADC_5 "in_voltage5_raw"
#define ADC_6 "in_voltage6_raw"
#define ADC_7 "in_voltage7_raw"

#define ADC_SCALE "/sys/bus/iio/devices/iio:device0/in_voltage_scale"

double AdcFunDemo()
{
    double ADC_Num,R0,Rs,ppmval;
    int fd_scale = open(ADC_SCALE, O_RDONLY);
    if(fd_scale < 0)
    {
        perror("open1");
        return 0;
    }
    char scale[10] = {0};
    if (read(fd_scale, scale, sizeof(scale)) != sizeof(scale))
    {
        perror("read1");
        return 0;
    }
    close(fd_scale);

    double scaleNum = strtod(scale, nullptr);
    string str = "/sys/bus/iio/devices/iio:device0/" + string(ADC_0);
    char num[4] = {0};
    double Num = 0;
    int fd_adc = open(str.c_str(), O_RDONLY);
    if (fd_adc < 0)
    {
        perror("open2");
        return 0;
    }
    if (read(fd_adc, num, sizeof(num)) <= 0)
    {
        perror("read2");
    }
    close(fd_adc);
    Num = strtod(num, nullptr);
    ADC_Num=(scaleNum*Num)/1000;
    R0=6.64;
    Rs=(5-ADC_Num) / ADC_Num * 0.5;
    ppmval=pow(11.5428*R0/Rs,0.6549)*100;
    printf("ADC = %.2fV, 烟雾浓度 = %.2fppm\n", ADC_Num,ppmval);
    memset(num, 0, sizeof(num));
    sleep(1);
    return ppmval;

}
