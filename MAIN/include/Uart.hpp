#pragma once

#include <iostream>
#include <string>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

using namespace std;

#define UART1 "/dev/ttyS1" 

enum
{
    LS_UART_STOP1,  
    LS_UART_STOP2,  
};

enum
{
    LS_UART_DATA5,  
    LS_UART_DATA6,  
    LS_UART_DATA7,  
    LS_UART_DATA8   
};

enum
{
    LS_UART_NONE,  
    LS_UART_ODD,    
    LS_UART_EVEN    
};

class LS_UART
{
public:
    /*!
     * @brief   
     */
    LS_UART();

    /*!
     * @brief   
     * @param   uart     
     * @param   baudrate 
     * @param   stop     
     * @param   data     
     * @param   check    
     */
    LS_UART(const string &uart, speed_t baudrate, uint8_t stop, uint8_t data, uint8_t check);

    /*!
     * @brief   
     * @param   baudrate 
     */
    void SetBaudrate(speed_t baudrate);

    /*!
     * @brief   
     * @param   stop 
     */
    void SetStopBit(uint8_t stop);

    /*!
     * @brief   
     * @param   stop 
     */
    void SetDataBit(uint8_t data);

    /*!
     * @brief   
     * @param   stop 
     */
    void SetChecBit(uint8_t check);

    /*!
     * @brief   
     * @param   buf 
     * @param   len 
     */
    ssize_t WriteData(const char *buf, ssize_t len);

    /*!
     * @brief   
     * @param   buf 
     * @param   len 
     */
    ssize_t ReadData(char *buf, ssize_t len);

    /*!
     * @brief  
     * @param   stop 
     */
    ~LS_UART();

private:
    /*!
     * @brief  
     */
    int uart_fd;

    /*!
     * @brief   
     */
    struct termios ts;

    speed_t BaudRate;  
    uint8_t Stop;       
    uint8_t Data;       
    uint8_t Check;      
};
