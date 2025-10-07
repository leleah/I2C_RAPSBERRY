#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define I2C_BUS "/dev/i2c-1"
#define SCD30_ADDR 0x61


int main()
{
int fd;
fd=open(I2C_BUS,O_RDWR);
        if(fd<0)
        {
            perror("Can't open i2c bus");
            return 1;
        }
        if(ioctl(fd,I2C_SLAVE,SCD30_ADDR)<0)
        {
            perror("Can't connect to scd30");
            close(fd);
            return 1;
        }

printf("Connected to scd30 (0x%02X)\r\n",SCD30_ADDR);
unsigned char cmd[2]={0x00,0x10}; //start measurement 0x0010
write(fd,cmd,2);
sleep(3);
unsigned char read_cmd[2]={0x03,0x00}; //read measurement 0x0300
write(fd,read_cmd,2);
sleep(3);
unsigned char cmd2[2] = {0x02,0x02};
write(fd,cmd2,2);
unsigned char buff[3];
read(fd,buff,3);
for(int i=0;i<18;i++)
{
    printf("0x%x\r\n",buff[i]);
}
if(buff[0]<<8 | buff[1] == 1)
{
    unsigned char data_buff[18];
read(fd,data_buff,18);
for(int i=0;i<18;i++)
{
    printf("0x%x\r\n",data_buff[i]);
}

}


close(fd);
return 0;
}
