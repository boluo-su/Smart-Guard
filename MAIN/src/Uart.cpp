#include "Uart.hpp"  

LS_UART::LS_UART()
{

}

LS_UART::LS_UART(const string &uart, speed_t baudrate, uint8_t stop, uint8_t data, uint8_t check)
 : BaudRate(baudrate), Stop(stop), Data(data), Check(check)
{
    this->uart_fd = open(uart.c_str(), O_RDWR);  
    if (this->uart_fd == -1) {  
        printf("Unable to open dev!\n");  
        return;
    }
  
    memset(&this->ts, 0, sizeof(this->ts));
    if (tcgetattr(this->uart_fd, &this->ts) != 0)
    {
        perror("Error tcgetattr");
        close(this->uart_fd);
        return;
    }
    this->ts.c_cflag &= ~CRTSCTS;                      
    this->ts.c_cflag |= CREAD | CLOCAL;                 
    this->ts.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); 
    this->ts.c_iflag &= ~(IXON | IXOFF | IXANY);		 
    this->ts.c_oflag &= ~OPOST; 			        	
    this->ts.c_cc[VMIN] = 0; 							 
    this->ts.c_cc[VTIME] = 5; 			    		    

    this->SetBaudrate(this->BaudRate);

    this->SetStopBit(this->Stop);

    this->SetDataBit(this->Data);

    this->SetChecBit(this->Check);
}

void LS_UART::SetBaudrate(speed_t baudrate)
{
    this->BaudRate = baudrate;
    cfsetispeed(&this->ts, baudrate);   
    cfsetospeed(&this->ts, baudrate);   
    if (tcsetattr(this->uart_fd, TCSANOW, &this->ts) != 0)
    {
        perror("Error set Baudrate");
        return;
    }
}

void LS_UART::SetStopBit(uint8_t stop)
{
    this->Stop = stop;
    switch(this->Stop)
    {
        case LS_UART_STOP1:
            this->ts.c_cflag &= ~CSTOPB;break; 
        case LS_UART_STOP2:
            this->ts.c_cflag |= CSTOPB;break; 
        default:
            printf("Stop bit flag setting error");
            break;
    }
    if (tcsetattr(this->uart_fd, TCSANOW, &this->ts) != 0)
    {
        perror("Error set Stop Bit");
        return;
    }
}

void LS_UART::SetDataBit(uint8_t data)
{
    this->Data = data;
    this->ts.c_cflag &= ~CSIZE;    
    switch(this->Data)
    {
        case LS_UART_DATA5: 
            this->ts.c_cflag |= CS5;break;
        case LS_UART_DATA6: 
            this->ts.c_cflag |= CS6;break;
        case LS_UART_DATA7: 
            this->ts.c_cflag |= CS7;break;
        case LS_UART_DATA8: 
            this->ts.c_cflag |= CS8;break;
        default:
            printf("Data bit flag setting error");
            break;
    }
    if (tcsetattr(this->uart_fd, TCSANOW, &this->ts) != 0)
    {
        perror("Error set Stop Bit");
        return;
    }
}

void LS_UART::SetChecBit(uint8_t check)
{
    this->Check = check;
    this->ts.c_cflag &= ~PARENB;    
    switch (this->Check)
    {
        case LS_UART_NONE:  
            break;
        case LS_UART_ODD:  
            this->ts.c_cflag |= PARENB;
            this->ts.c_cflag &= PARODD;
            break;
        case LS_UART_EVEN:  
            this->ts.c_cflag |= PARENB;
            this->ts.c_cflag |= PARODD;
            break;
        default:
            printf("Check bit flag setting error");
            break;
    }
    if (tcsetattr(this->uart_fd, TCSANOW, &this->ts) != 0)
    {
        perror("Error set Check Bit");
        return;
    }
}

ssize_t LS_UART::WriteData(const char *buf, ssize_t len)
{
    return write(this->uart_fd, buf, len);
}

ssize_t LS_UART::ReadData(char *buf, ssize_t len)
{
    return read(this->uart_fd, buf, len);
}

LS_UART::~LS_UART()
{
    close(this->uart_fd);
}

