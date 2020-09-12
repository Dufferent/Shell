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
	int cpct[3] = {0};
	int fixct[3] = {0};
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
				for(int j=10;j<32;j++)
				{
					if(buf[i+j] == ',')
						break;
					cpct[0]++;
				}
				strncpy(cpbuf[0],&buf[i+10],cpct[0]);
			}
			if(buf[i] == 'p' && buf[i+3] == 't')
			{
				for(int j=7;j<16;j++)
				{
					if(buf[i+j] == ',')
						break;
					cpct[1]++;
				}
				strncpy(cpbuf[1],&buf[i+7],cpct[1]);
			}
			if(buf[i] == 'i' && buf[i+1] == 'd')
			{
				for(int j=5;j<48;j++)
				{
					if(buf[i+j] == ',')
						break;
					cpct[2]++;
				}
				strncpy(cpbuf[2],&buf[i+5],cpct[2]);
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
				for(int j=10;j<32;j++)
				{
					if(rqbuf[i+j] == ',')
						break;
					fixct[0]++;
				}
				if(fixct[0] < cpct[0])
				{
					int gap = cpct[0] - fixct[0];
					for(int k=rec-1;k>=i+10;k--)
					{
						rqbuf[k+gap] = rqbuf[k];
					}
					
				}
				else if(fixct[0] > cpct[0])
				{
					int gap = fixct[0] - cpct[0];
					for(int k=i;k<rec-gap;k++)
					{
						rqbuf[k] = rqbuf[k+gap];
					}
				}
				strncpy(&rqbuf[i+10],cpbuf[0],cpct[0]);
			}
			if(rqbuf[i] == 'p' && rqbuf[i+1] == 'o' && rqbuf[i+2] == 'r' && rqbuf[i+3] == 't' && rqbuf[i+7] != 'n' && rqbuf[i-12] != 'y')
			{
				for(int j=7;j<16;j++)
				{
					if(rqbuf[i+j] == ',')
						break;
					fixct[1]++;
				}
				if(fixct[1] < cpct[1])
				{
					int gap = cpct[1] - fixct[1];
					for(int k=rec-1;k>=i+7;k--)
					{
						rqbuf[k+gap] = rqbuf[k];
					}
					
				}
				else if(fixct[1] > cpct[1])
				{
					int gap = fixct[1] - cpct[1];
					for(int k=i;k<rec-gap;k++)
					{
						rqbuf[k] = rqbuf[k+gap];
					}
				}
				strncpy(&rqbuf[i+7],cpbuf[1],cpct[1]);
			}
			if(rqbuf[i] == 'i' && rqbuf[i+1] == 'd' && rqbuf[i+2] == '"')
			{
				for(int j=5;j<48;j++)
				{
					if(rqbuf[i+j] == ',')
						break;
					fixct[2]++;
				}
				if(fixct[2] < cpct[2])
				{
					int gap = cpct[2] - fixct[2];
					for(int k=rec-1;k>=i+5;k--)
					{
						rqbuf[k+gap] = rqbuf[k];
					}
					
				}
				else if(fixct[2] > cpct[2])
				{
					int gap = fixct[2] - cpct[2];
					for(int k=i;k<rec-gap;k++)
					{
						rqbuf[k] = rqbuf[k+gap];
					}
				}
				strncpy(&rqbuf[i+5],cpbuf[2],cpct[2]);
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
