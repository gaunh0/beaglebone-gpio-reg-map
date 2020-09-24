#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "main.h"

int main(int argc, char *argv[])
{
    volatile void *gpio_addr = NULL;
    volatile unsigned int *gpio_oe_addr = NULL;
    volatile unsigned int *gpio_setdataout_addr = NULL;
    volatile unsigned int *gpio_cleardataout_addr = NULL;
    volatile unsigned int *gpio_dataout_addr = NULL;
    volatile unsigned int *gpio_datain_addr = NULL;

    unsigned int reg;

    int fd = open("/dev/mem", O_RDWR | O_SYNC);

    printf("Mapping %X - %X (size: %X)\n", GPIO2_START_ADDR, GPIO2_END_ADDR, GPIO2_SIZE);

    gpio_addr = mmap(0, GPIO2_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO2_START_ADDR);

    if (gpio_addr == MAP_FAILED)
    {
        printf("Unable to map GPIO\n");
        exit(1);
    }

    gpio_oe_addr = gpio_addr + GPIO_OE;
    gpio_setdataout_addr = gpio_addr + GPIO_SETDATAOUT;
    gpio_cleardataout_addr = gpio_addr + GPIO_CLEARDATAOUT;
    gpio_dataout_addr = gpio_addr + GPIO_DATAOUT;
    gpio_datain_addr = gpio_addr + GPIO_DATAIN;

    printf("GPIO mapped to %p\n", gpio_addr);
    printf("GPIO OE mapped to %p\n", gpio_oe_addr);
    printf("GPIO SETDATAOUTADDR mapped to %p\n", gpio_setdataout_addr);
    printf("GPIO CLEARDATAOUT mapped to %p\n", gpio_cleardataout_addr);
    printf("GPIO DATAOUT mapped to %p\n", gpio_dataout_addr);
    printf("GPIO DATAIN mapped to %p\n", gpio_datain_addr);

    reg = *gpio_oe_addr;
    printf("GPIO1 configuration: %X\n", reg);
    reg = reg & (0xFFFFFFFF ^ (PIN_OUT1 | PIN_OUT2));
    *gpio_oe_addr = reg;
    printf("GPIO1 configuration: %X\n", reg);

    printf("Start toggling PIN \n");

    // while(1)
    {

        //	if(*gpio_datain_addr & PIN_IN1)
        //	{
        //		*gpio_setdataout_addr= PIN_OUT1;
        //	}
        //	else
        //	{
        //        	*gpio_cleardataout_addr = PIN_OUT1;
        //	}
        //	usleep(100);
        *gpio_dataout_addr |= (PIN_OUT1 | PIN_OUT2);
        sleep(1);
        //        *gpio_dataout_addr &= ~(PIN_OUT1 | PIN_OUT2);
        sleep(1);
    }

    close(fd);

    return 0;
}
