#include "main.hpp"

int Temp=0;
int Humi = 0;
double ppmval;

void *threadfun1(void *arg)
{    
    IIC_Init();
    LS_UART uart(UART1, B115200, LS_UART_STOP1, LS_UART_DATA8, LS_UART_NONE);
    while (1)
    {
        SHT30_Read_Humiture(&Temp,&Humi);
        printf("温度=%d℃    湿度=%d%RH\n",Temp,Humi);
        AdcFunDemo();
        sleep(3);
    }
 
    return NULL;
}

void *threadfun2(void *arg)
{    
    IIC_Init();
    LS_UART uart(UART1, B115200, LS_UART_STOP1, LS_UART_DATA8, LS_UART_NONE);
    while (1)
    {
        char Temp1=0;
        char Humi1=0;
        char ppmval1=0;
        SHT30_Read_Humiture(&Temp,&Humi);
        ppmval=AdcFunDemo();
        char buf[256];
        int ret = uart.ReadData(buf, sizeof(buf));
        if (ret < 0) {
            printf("Reading error!\n");
            break;
        }
        if(buf[ret-1]=='1')
        {
              Temp1=(char)Temp;
              buf[ret-1]=Temp1;
              buf[ret]='\0';
              ret = uart.WriteData(buf, ret);
        }
        if(buf[ret-1]=='2')
        {
              Humi1=(char)Humi;
              buf[ret-1]=Humi1;
              buf[ret]='\0';
              ret = uart.WriteData(buf, ret);
        }
        if(buf[ret-1]=='3')
        {
              int a=0;
              a=round(ppmval);
              ppmval1=(char)(a&0x00ff);
              buf[ret-1]=ppmval1;
              buf[ret]='\0';
              ret = uart.WriteData(buf, ret);
              ppmval1=(char)((a&0xff00)>>8);
              buf[ret-1]=ppmval1;
              buf[ret]='\0';
              ret = uart.WriteData(buf, ret);
        }
        if (ret < 0) {
            printf("Writeing error!\n");
            break;
        }     
    }
 
    return NULL;
}


int main()
{
    pthread_t tid1;
    pthread_t tid2;
    //创建二个线程
    pthread_create(&tid1, NULL, threadfun1, NULL);
    pthread_create(&tid2, NULL, threadfun2, NULL);
    CameraDemo();
    return 0;
}