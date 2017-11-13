#include"socket.h"
#define Encrypt 1
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
        printf("A---------SetData-------------\n");
	T t;
	memset(&t,' ',sizeof(t));
        unsigned char recvbuf[1000] = ""; 
	unsigned char desRecBuf[1000];
         printf("A---------key-------------\n");
        unsigned char *key = "12345678";
        printf("A---------keykkk-------------\n");
	strncpy(t.Size,		"0524",			sizeof(t.Size));
	strncpy(t.txncode,	code,			strlen(code));
	if(k == 1)
	{
		strncpy(t.seqno,	"2AADDDDDDDDDDDDD",	sizeof(t.seqno));
		k = 0;
	}
	else 
	{
		strncpy(t.seqno,	"2BBCCCCCC",	sizeof(t.seqno));
		k = 1;
	}
        printf("A----------------------\n");
        memcpy(recvbuf,&t,sizeof(t));
        printf("buf:%s\n",recvbuf);
        DesAlg(key, recvbuf, desRecBuf, Encrypt);
	printf("des:%s\n",desRecBuf);
	memcpy(data,desRecBuf,sizeof(t));
}

/* 发送报文 */
int SendData(int sock,char *code,char *data,int datalen)
{
        printf("A---------SendData-------------\n");
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
        printf("A---------SendData end-------------\n");
	return 0;
}

/* 主函数 */
int main(int argc ,char **argv)
{
	strcpy(TargetIP,"127.0.0.1");				/* 设置连接的IP				*/
	TargetPort=atoi("1118");				/* 设置连接的端口			*/
	int sock=init();
	int i = 0;
	while(i++ < 1000)
	{
		if ( SendData(sock,"111111",NULL,0) != 0 )
		{
			 return -1;	
		}
		printf("send stop cmd ok %d\n",i);
		}
	return 0;
}