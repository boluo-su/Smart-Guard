#include "HW_GPIO.hpp"

HWGpio::HWGpio()
{
    this->GPIO_ONE   = NULL;
    this->GPIO_O     = NULL;
    this->GPIO_I     = NULL;
    this->GPIO_REUSE = NULL;
    this->Gpio       = -1;
}

HWGpio::HWGpio(uint8_t gpio, uint8_t mode) : Gpio(gpio)
{
    this->GPIO_ONE = AddressMap(LS_GPIO_BASE_ADDR + LS_GPIO_OEN_OFFSET(gpio), PAGE_SIZE);
    this->GPIO_O   = AddressMap(LS_GPIO_BASE_ADDR + LS_GPIO_O_OFFSET(gpio), PAGE_SIZE);
    this->GPIO_I   = AddressMap(LS_GPIO_BASE_ADDR + LS_GPIO_I_OFFSET(gpio), PAGE_SIZE);
    // 配置引脚复用为 GPIO 模式   88  / 16 = 5
    GpioReuse(this->Gpio, 0b00);
    this->GpioDirection(mode);
}

void HWGpio::GpioDirection(uint8_t mode)
{
    if(mode == 1){
        LS_writel(this->GPIO_ONE, LS_readl(this->GPIO_ONE) | BIT(this->Gpio % 8));
    }else if(mode == 0){
        LS_writel(this->GPIO_ONE, LS_readl(this->GPIO_ONE) & ~BIT(this->Gpio % 8));
    }else
        cout << "模式设置错误" << endl;
}

void HWGpio::SetGpioValue(uint8_t value)
{
    if(value == 1){
        LS_writel(this->GPIO_O, LS_readl(this->GPIO_O) | BIT(this->Gpio % 8));
    }else if(value == 0){
        LS_writel(this->GPIO_O, LS_readl(this->GPIO_O) & ~BIT(this->Gpio % 8));
    }else
        cout << "输出值设置失败" << endl;
}

bool HWGpio::GetGpioValue()
{
    return ((LS_readl(this->GPIO_I) & BIT(this->Gpio % 8)) == BIT(this->Gpio % 8));
}

HWGpio::~HWGpio()
{
    munmap(this->GPIO_ONE, PAGE_SIZE);
    munmap(this->GPIO_O, PAGE_SIZE);
    munmap(this->GPIO_I, PAGE_SIZE);
    munmap(this->GPIO_REUSE, PAGE_SIZE);
}
