#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/types.h"
#include "sys/ioctl.h"
#include "linux/usbdevice_fs.h"
int main(int argc,char** argv)
{
	int ret;
	int usb_fd = open(argv[1],O_RDWR);
	if(usb_fd < 0)
	{
		printf("usb io file open failed!\r\n");
		exit(-1);
	}
	ret = ioctl(usb_fd,USBDEVFS_RESET,0);
	if(ret < 0)
	{
		printf("usb reset failed!\r\n");
	}
	printf("usb reset successful!\r\n");
	close(usb_fd);
	return 0;
}
