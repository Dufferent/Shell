#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/types.h"

const char findstr[] = "listen";
char ts[14];

int main(int argc,char **argv)
{
	int fd;
	char Rxbuf[4096];
	int findex;
	int rec;
	fd = open("./config.json",O_RDWR);
	if(fd == -1)
	{
		printf("Check The file in ./...!\r\n");
		return -1;
	}
	while(1)
	{
		int recieve;
		recieve = read(fd,Rxbuf,4096);
		if( !(recieve>0) )
		{
			break;
		}
		rec = recieve;
		for(int i=0;i<rec;i++)
		{
			static int mflag = 0;
			if(Rxbuf[i] == findstr[mflag])
				mflag++;
			else
				mflag=0;
			if(mflag == strlen(findstr))
			{
				findex = i;
				break;
			}
		}
	}
	close(fd);
	//替换端口
	fd = open("./config.json",O_RDWR);
	sprintf(ts,"%c%c%s%c%s%c",' ','"',"0.0.0.0",'"',",  ",'\0');
	printf("listen::%s\r\n",ts);
	printf("rec::%d\r\n",rec);
	strncpy(&Rxbuf[findex+3],ts,strlen(ts));
	write(fd,Rxbuf,rec);
	close(fd);
	return 0;
}
