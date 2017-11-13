#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 			20*1024

int k = 0;
/* 报文头结构 */
typedef struct _tabscale
{
        char Size[4];
        char txncode[6];
        char seqno[4];
}T;

char 	TargetIP[ BUF_SIZE ]={0};			/*  要连接的服务器IP		*/
int 	TargetPort;					        /*  要连接的服务器端口		*/

/* 打印使用方法 */
void Usage()
{
	printf("TcpMs用法:\n");
	exit(-1);
}

/* 初始化套接字 */
int init()
{
	int 			iRet;
	int  			sock;
	struct 	sockaddr_in 	Target;
	Target.sin_family	=AF_INET;
	Target.sin_addr.s_addr	=inet_addr(TargetIP);
	Target.sin_port		=htons(TargetPort);
	
    /* 创建套接字  */
    sock=socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
	if(sock < 0) 
	{ 
		printf("socket() failed \n"); 
		return -1;
	} 
	
	/* 连接 */
	if(connect(sock,(struct sockaddr *)&Target,sizeof(Target))) 
	{
		return -1;
	}
	return sock;
}

/* 设置报文头  */
void SetData(T *data,char *code,int len)
{
	T t;
	memset(&t,' ',sizeof(t));

	strncpy(t.Size,		"0524",			sizeof(t.Size));
	strncpy(t.txncode,	code,			strlen(code));
	if(k == 1)
	{
		strncpy(t.seqno,	"2AA",	sizeof(t.seqno));
		k = 0;
	}
	else 
	{
		strncpy(t.seqno,	"2BB",	sizeof(t.seqno));
		k = 1;
	}
	memcpy(data,&t,sizeof(t));
}

/* 发送报文 */
int SendData(int sock,char *code,char *data,int datalen)
{
	int iRet;
	if(sock < 0){ return -1;}
	T t;
	SetData(&t,code,datalen);
	if ( data == NULL)
	{
		iRet=send(sock,&t,sizeof(t),0); 
		if(iRet < 0) 
		{ 
			printf("\nsend() to target failed"); 
			return -1;
		} 
	}
	else
	{
		int iOfset=sizeof(t);
		int iDataLen=iOfset+datalen;
		char sData[iDataLen];
		
		memcpy(sData,		&t,	iOfset);
		memcpy(sData+iOfset,	data,	datalen);
		iRet=send(sock,sData,iDataLen,0); 
		if(iRet < 0) 
		{ 
			printf("\nsend() to target failed"); 
			return -1;
		} 
	}
	return 0;
}

/* 主函数 */
int main(int argc ,char **argv)
{
	strcpy(TargetIP,"127.0.0.1");				/* 设置连接的IP				*/
	TargetPort=atoi("1118");				/* 设置连接的端口			*/
	int sock=init();
	int i = 0;
	while(i++ < 100)
	{
		if ( SendData(sock,"111111",NULL,0) != 0 )
		{
			 return -1;	
		}
		printf("send stop cmd ok %d\n",i);
		}
	return 0;
}