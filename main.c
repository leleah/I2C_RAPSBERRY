#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define I2C_BUS "/dev/i2c-1"
#define LM75_ADDR 0x48
unsigned char reg=0x00; // temp registr
unsigned char buff[2];

int main()
{
int fd;
fd=open(I2C_BUS,O_RDWR);
        if(fd<0)
        {
            perror("Can't open i2c bus");
            return 1;
        }
        if(ioctl(fd,I2C_SLAVE,LM75_ADDR)<0)
        {
            perror("Can't connect to scd30");
            close(fd);
            return 1;
        }

printf("Connected to lm75 (0x%02X)\r\n",LM75_ADDR);

write(fd,&reg,1);
sleep(1);
read(fd,buff,2);
int16_t raw =(buff[0]<<8 | buff[1]);
raw >>=7;
float temp = raw*0.5;
printf("Temperature is %f ",temp);

close(fd);
return 0;
}
