#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "sys/types.h"
#include "fcntl.h"

#define BSIZE 4096
char buf[BSIZE] = {0};
char cpbuf[3][BSIZE] = {0};
char rqbuf[BSIZE] = {0};

int main(void)
{
	int fd;
	int fd_o;
	int rec;
	fd = open("./change-msg",O_RDWR);
	if(fd == -1)
	{
		printf("file open failed!\r\n");
		return -1;
	}
	fd_o = open("./config.json",O_RDWR);
	if(fd_o == -1)
	{
		printf("file open failed!\r\n");
		return -1;
	}
	//读新的配置文件
	do{
		rec = read(fd,buf,sizeof(buf));
	//	printf("%s",buf);
		if(rec <= 0)
			break;
		for(int i=0;i<rec;i++)
		{
			if(buf[i] == 'a' && buf[i+6] == 's')
			{
				strncpy(cpbuf[0],&buf[i+10],16);
			}
			if(buf[i] == 'p' && buf[i+3] == 't')
			{
				strncpy(cpbuf[1],&buf[i+7],5);
			}
			if(buf[i] == 'i' && buf[i+1] == 'd')
			{
				strncpy(cpbuf[2],&buf[i+5],38);
			}
		}
		for(int j=0;j<3;j++)
			printf("%s\n",cpbuf[j]);
	}while(rec > 0);
	//读要修改的配置文件
	do{
		rec = read(fd_o,rqbuf,sizeof(rqbuf));
		if(rec <= 0)
			break;
		//配对字符串
		for(int i=0;i<rec;i++)
		{
			if(rqbuf[i] == 'a' && rqbuf[i+6] == 's' && rqbuf[i+10] != 'n')
			{
				strncpy(&rqbuf[i+10],cpbuf[0],16);
			}
			if(rqbuf[i] == 'p' && rqbuf[i+1] == 'o' && rqbuf[i+2] == 'r' && rqbuf[i+3] == 't' && rqbuf[i+7] != 'n' && rqbuf[i-12] != 'y')
			{
				strncpy(&rqbuf[i+7],cpbuf[1],5);
			}
			if(rqbuf[i] == 'i' && rqbuf[i+1] == 'd' && rqbuf[i+2] == '"')
			{
				strncpy(&rqbuf[i+5],cpbuf[2],38);
			}
		}
	}while(rec > 0);

	//关闭文件
	close(fd);
	close(fd_o);
//写要修改的配置文件
	fd_o = open("./config.json",O_RDWR);
	write(fd_o,rqbuf,sizeof(rqbuf));
	close(fd_o);
}
