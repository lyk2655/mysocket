#include"socket.h"
/*********** server ************/ 
#define SOCKET_ERROR -1
#define Encrypt 0

void main(int argc ,char **argv) 
{ 
	/*初始化SADATA wsaData; */
	int listenfd; 
	int AcceptSocket;
	int iRet;
	/*int iResult = WSAStartup(MAKEWORD(2,2), &wsaData); 
	if (iResult != NO_ERROR) 
	{ 
		printf("Error at WSAStartup() \n"); 
	} */	
	/*建立socket*/
	listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP); 
	if ( listenfd <0 ) 
	{ 
		printf("Error at socket.\n");  
		return; 
	} 
	struct sockaddr_in service; 
	service.sin_family = AF_INET; 
	service.sin_addr.s_addr = inet_addr( "127.0.0.1" ); 
	service.sin_port = htons( 1118 ); 
	iRet=bind(listenfd, (struct sockaddr *) &service, sizeof(service));
	if (iRet) 
	{ 
		printf("bind() failed:%d \n",iRet); 
		close(listenfd); return; 
	} 
	if ( listen( listenfd, 1 ) == SOCKET_ERROR )
	{		
		printf( "Error listening on socket. \n"); 
	}
	printf("Waiting for client to connect... \n"); 
	
	while (1) 
	{ 
		AcceptSocket = SOCKET_ERROR; 
		while ( AcceptSocket == SOCKET_ERROR ) 
		{ 
			AcceptSocket = accept( listenfd, NULL, NULL); 
		} 
		printf( "Client Connected. \n"); 
		listenfd = AcceptSocket; 
		break; 
	}
	int iSent; 
	int iRecv = SOCKET_ERROR; 
	unsigned char sendbuf[32] = "listenfd: Sending Data."; 
	unsigned char recvbuf[1000] = ""; 
	unsigned char desRecBuf[1000];
	unsigned char *key = "12345678";
	int count=0;
	while(recv( listenfd, recvbuf, sizeof(T), 0)>0)
	{ 
		printf("no.%d:%s\n",count,recvbuf);
		DesAlg(key, recvbuf, desRecBuf, Encrypt);
		printf("recvbuf:%s\n",desRecBuf);
		count++;		
	}
	/*DesAlg(key, recvbuf, desRecBuf, Encrypt);
	printf("recvbuf:%s\n",desRecBuf);*/
	/*
	iSent = send( listenfd, sendbuf, strlen(sendbuf), 0); 
	printf("Bytes Sent: %d \n", iSent); */
	return; 
} 
