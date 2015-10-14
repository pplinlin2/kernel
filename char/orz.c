#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DATA_NUM 128

int main()
{
	int fd, i;
	char buf[DATA_NUM];
	ssize_t RD, WD;
	
	memset(buf, 0, DATA_NUM);
	fd = open("/dev/testchar", O_RDWR);
	printf("fd = %d\n", fd);
	if(fd < 0){
		perror("open error: ");
		exit(1);
	}

	WD = write(fd, buf, DATA_NUM);
	RD = read(fd, buf, DATA_NUM);

	printf("WD = %d\nRD = %d\n", WD, RD);
	printf("%s\n", buf);

	int on = 1;
	int led_no = 7;
	ioctl(fd, on, led_no);

	return 0;
}
