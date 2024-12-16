/*
 * @Author: SingleBiu
 * @Date: 2021-08-31 20:26:58
 * @LastEditors: SingleBiu
 * @LastEditTime: 2024-12-16 20:39:28
 * @Description: file content
 */
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define NET_CFG_FILE "net.conf"
#define DEBUG 0
#define ERROR -1

int year, month ,day, hour, minute ,second;

int i_get_initial_day()
{
	printf("Please input year:\n");
	scanf("%d",&year);
	if (year < 2024 )
	{
		printf("Invalid input\n");
		return ERROR;
	}
	printf("Please input month:\n");
	scanf("%d",&month);
	if (month <= 0 || month >= 13)
	{
		printf("Invalid input\n");
		return ERROR;
	}
	printf("Please input day:\n");
	scanf("%d",&day);
	if (day <= 0 || day >= 32)
	{
		printf("Invalid input\n");
		return ERROR;
	}
	printf("Please input hour\n");
	scanf("%d",&hour);
	if (hour < 0 || hour >= 24)
	{
		printf("Invalid input\n");
		return ERROR;
	}
	printf("Please input minute\n");
	scanf("%d",&minute);
	if (minute < 0 || minute >= 60)
	{
		printf("Invalid input\n");
		return ERROR;
	}
	printf("Please input second\n");
	scanf("%d",&second);
	if (second < 0 || second >= 60)
	{
		printf("Invalid input\n");
		return ERROR;
	}

	#if DEBUG
		printf("Got year:%d month:%d day:%d hour:%d minutes:%d second:%d\n",
		year,month,day,hour,minute,second);
	#endif

	return 0;
}

void v_display()
{
	while (1)
	{
		if (year%4 == 0 || year%400 == 0)
		{
			#if DEBUG
				printf("Year:%d is leap year\n",year);
			#endif

			#if 1

				sleep(1);
				printf("Current time: %d/%d/%d %d:%d:%d\n",year,month,day,hour,minute,second);
				second++;
				if (second >59)
				{
					second = 0;
					minute ++;
				}
				if (minute > 59)
				{
					minute = 0;
					hour++;
				}
				if (hour > 23)
				{
					day++;
					hour = 0;
				}
				if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
				{
					if (day > 31)
					{
						day = 1;
						month++;
					}
				}else if (month == 4 || month == 6 || month == 9 || month == 11)
				{
					if (day > 30)
					{
						day = 1;
						month++;
					}
				}
				else
				{
					if (day >29)
					{
						day = 1;
						month++;
					}
				}				
				if (month > 12)
				{
					year++;
					month = 1;
				}
				
			#endif
		}
		else
		{
			#if DEBUG
				printf("Year:%d is not a leap year\n",year);
			#endif

			sleep(1);
			printf("Current time: %d/%d/%d %d:%d:%d\n",year,month,day,hour,minute,second);
			second++;
			if (second >59)
			{
				second = 0;
				minute ++;
			}
			if (minute > 59)
			{
				minute = 0;
				hour++;
			}
			if (hour > 23)
			{
				day++;
				hour = 0;
			}
			if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
			{
				if (day > 31)
				{
					day = 1;
					month++;
				}
			}else if (month == 4 || month == 6 || month == 9 || month == 11)
			{
				if (day > 30)
				{
					day = 1;
					month++;
				}
			}
			else
			{
				if (day >28)
				{
					day = 1;
					month++;
				}
			}				
			if (month > 12)
			{
				year++;
				month = 1;
			}
		}
	}
}



int creat_tcp_socket(char *ip,short port)
{
    int sock;
    int ret;

    sock = socket(AF_INET,SOCK_STREAM,0);
    if (sock == -1)
    {
        perror("create tcp socket errno");
        return -1;
    }

    struct sockaddr_in sa;
    memset(&sa,0,sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = inet_addr(ip);

    ret = bind(sock,(struct sockaddr*) &sa,sizeof(sa));
    if (ret == -1)
    {
        perror("bind error");
        close(sock);
        return -1;
    }
    
    ret = listen(sock,10);
    if (ret == -1)
    {
        perror("listen error");
        close(sock);
        return -1;
    }

    return sock;
}

void handle_connection(int conn_fd)
{
    int n = 0;
    char sendbuf[128];
    char recvbuf[128];
    memset(sendbuf,0,sizeof(sendbuf));
    memset(recvbuf,0,sizeof(recvbuf));
    
    while (1)
    {
        if (year%4 == 0 || year%400 == 0)
		{
			#if DEBUG
				printf("Year:%d is leap year\n",year);
			#endif

			#if 1

				sleep(1);
				printf("Current time: %d/%d/%d %d:%d:%d\n",year,month,day,hour,minute,second);
				second++;
				if (second >59)
				{
					second = 0;
					minute ++;
				}
				if (minute > 59)
				{
					minute = 0;
					hour++;
				}
				if (hour > 23)
				{
					day++;
					hour = 0;
				}
				if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
				{
					if (day > 31)
					{
						day = 1;
						month++;
					}
				}else if (month == 4 || month == 6 || month == 9 || month == 11)
				{
					if (day > 30)
					{
						day = 1;
						month++;
					}
				}
				else
				{
					if (day >29)
					{
						day = 1;
						month++;
					}
				}				
				if (month > 12)
				{
					year++;
					month = 1;
				}
				
			#endif
		}
		else
		{
			#if DEBUG
				printf("Year:%d is not a leap year\n",year);
			#endif

			sleep(1);
			printf("Current time: %d/%d/%d %d:%d:%d\n",year,month,day,hour,minute,second);
			second++;
			if (second >59)
			{
				second = 0;
				minute ++;
			}
			if (minute > 59)
			{
				minute = 0;
				hour++;
			}
			if (hour > 23)
			{
				day++;
				hour = 0;
			}
			if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
			{
				if (day > 31)
				{
					day = 1;
					month++;
				}
			}else if (month == 4 || month == 6 || month == 9 || month == 11)
			{
				if (day > 30)
				{
					day = 1;
					month++;
				}
			}
			else
			{
				if (day >28)
				{
					day = 1;
					month++;
				}
			}				
			if (month > 12)
			{
				year++;
				month = 1;
			}
		}
        n = recv(conn_fd,recvbuf,sizeof(recvbuf),0);
        sprintf(sendbuf,"%d/%d/%d/%d:%d:%d\n",year,month,day,hour,minute,second);
        send(conn_fd,sendbuf,sizeof(sendbuf),0);

        if (n == 0)
        {
            //conn_fd closed by the client
            close(conn_fd);
            printf("Client exit\n");
            break;
        }
        
        printf("received: %s\n",recvbuf);
        
        //信息处理
        //func()
        
        memset(sendbuf,0,sizeof(sendbuf));
        memset(recvbuf,0,sizeof(recvbuf));
    }
}

int main(int argc, char *argv[])
{
    //从配置文件中读取服务器ip和端口号
    char servIp[15];
    char servPort[5];
    FILE* cfgFp = fopen(NET_CFG_FILE,"r");
    fscanf(cfgFp,"%s",servIp);
    fscanf(cfgFp,"%s",servPort);

    int sock = creat_tcp_socket(servIp,atoi(servPort));
    if (sock == -1)
    {
        printf("failed to create tcp socket\n");
        return -1;
    }

    printf("Hello! Welcome to the time server intitialization.\n");
    sleep(1);
    begin:
        system("clear");
        int flag = 1;
        flag = i_get_initial_day();
        
        if (-1 == flag)
        {
            goto begin;
        }

    #if 0
    
    int main()
    {
        printf("Hello! Welcome to use this time tool.\n");

    begin:
        system("clear");
        int flag = 0;
        flag = i_get_initial_day();
        
        if (-1 == flag)
        {
            goto begin;
        }
        
        v_display();

        return 0;
    }
    #endif

    while (1)
    {
        struct sockaddr_in client;
        socklen_t addrlen = sizeof(client);
        int conn_fd = accept(sock,(struct sockaddr*) &client,&addrlen);
        if (conn_fd > 0)
        {
            // 成功建立连接
            printf("Client ip:%s\tport:%u\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
        
            // 并发服务器
            pid_t pid = fork();
            if (pid > 0)
            {
                // 父进程
                close(conn_fd);
            }
            else if (pid == 0)
            {
                // 子进程
                handle_connection(conn_fd);
                exit(0);
            }
        }
    }
    return 0;
}