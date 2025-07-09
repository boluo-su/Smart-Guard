#include "MAP_ADDR.hpp"

void *AddressMap(uint32_t PhyAddr, size_t size)
{
    int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if(mem_fd < 0){
        perror("Open /dev/mem error");
        exit(EXIT_FAILURE);
    }
    void *addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, PhyAddr & ~(PAGE_SIZE - 1));
    close(mem_fd);
    if(addr == MAP_FAILED){
        perror("mmap error");
        exit(EXIT_FAILURE);
    }
    return (void*)((uintptr_t)addr + (PhyAddr & (PAGE_SIZE - 1)));
}

void GpioReuse(uint8_t gpio, int mux)
{
    void *GPIO_REUSE_REG = AddressMap(LS_GPIO_REUSE_ADDR + (gpio / 16) * LS_GPIO_REUSE_OFS, PAGE_SIZE);
    LS_writel(GPIO_REUSE_REG, (LS_readl(GPIO_REUSE_REG) & ~(0b11 << (gpio % 16 * 2))) | (mux << (gpio % 16 * 2)));
    munmap(GPIO_REUSE_REG, PAGE_SIZE);
}
