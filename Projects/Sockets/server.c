#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>

#define CLIENT_QUEUE 10
#define ARRAY_LENGTH 100  

int e_i32CreateTCPSocket(void);
int e_i32CreateAndListenTcp(unsigned short int p_ui16DestPort);
int e_i32ListenTcp(int p_i32Sockfd, unsigned short int p_ui16ListenPort);
int e_i32CloseConnection(int p_i32Socketfd);
int e_i32ReadInputData(int p_i32FileDescriptor, unsigned char* p_ptrDataBuffer,int p_i32BufferSize);
int e_i32CreateAndConnectTcp(const char* p_ptrDestIP,unsigned short int p_ui16DestPort);
int e_i32ConnectTcp(int p_i32Sockfd,const char* p_ptrDestIP,unsigned short int p_ui16DestPort);
int e_i32ConnectTcpByHost(int p_i32Sockfd,const char* p_ptrHostName,unsigned short int p_ui16DestPort);
int e_i32SendArray(int p_i32Socketfd,const char *p_ptrBuffer,int p_i32BufferSize);
int e_i32CreateUDPSocket(void);
int e_i32SendUdp(int p_i32Sockfd,const char* p_ptrDestIP,unsigned short int p_ui16DestPort,
					const char* p_ptrBuffer, unsigned int p_ui32BufferSize);
int e_i32RecvUdp(int p_i32Sockfd,char* buffer,int size);

unsigned char p_ptrBuffer[ARRAY_LENGTH];

//unsigned char response[4096];

char p_ptrMessageToSend[]="Hola desde raspberry";

int main(int argc, char **argv)
{

	/*******SERVER*************/
	
	int SocketFD=e_i32CreateAndListenTcp(6001);
	
	if(SocketFD<0)
		return -1;
	while(1){

	while(e_i32ReadInputData(SocketFD,p_ptrBuffer,ARRAY_LENGTH)==0);
	
	printf("Cliente: :%s \n", p_ptrBuffer);

	scanf("%s",p_ptrMessageToSend);
	
	e_i32SendArray(SocketFD,p_ptrMessageToSend,20);

	}	
	e_i32CloseConnection(SocketFD);
	
	/***************************/
	
	/*******CLIENTE*************/
	/*int socketOut= e_i32CreateAndConnectTcp("192.168.0.140",6000);
	if(socketOut<0)
		return -1;
		
	e_i32SendArray(socketOut,p_ptrMessageToSend,20);
	e_i32CloseConnection(socketOut);
		

	return 0;*/
}


/**********General TCP/IP********************/
int e_i32CreateTCPSocket(void)
{
	int p_i32Result;
	p_i32Result= socket(AF_INET, SOCK_STREAM, 0); //AF_INET manejo  direcciones ipv4, TCP/IP, variacion protocolo

	if(p_i32Result==-1)
		printf( "(errno: %d) Error creating tcp socket. \n",errno);
	else
		printf("Tcp socket created.[%d] \n",p_i32Result);

	return p_i32Result;
}

int e_i32CloseConnection(int p_i32Socketfd)
{
	int p_i32Result;
	p_i32Result= close(p_i32Socketfd);


	if(p_i32Result==-1)
		printf( "(errno: %d) Error closing connection. \n",errno);
	else
		printf("Connection successfully closed.\n");

	return p_i32Result;
}

/**********FIN General TCP/IP********************/

/************Server****************/

int e_i32ListenTcp(int p_i32Sockfd, unsigned short int p_ui16ListenPort)
{
	struct sockaddr_in serv_addr;
	int connfd;
	if(p_i32Sockfd<0)
	{
		printf( "File descriptor < 0. \n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(p_ui16ListenPort);

	if(bind(p_i32Sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1) //asocia socket con la direccion local
	{
		printf( "errno: %d) Error binding socket. \n",errno);
		e_i32CloseConnection(p_i32Sockfd);
		return -1;
	}

	listen(p_i32Sockfd, CLIENT_QUEUE);

	connfd = accept(p_i32Sockfd, (struct sockaddr*)NULL, NULL);

	if(connfd==-1)
		printf( "(errno: %d) Error accepting socket.\n",errno);
	else
		printf( "Socket accepted and listening. FD=%d \n",connfd);

	return connfd;
}

int e_i32CreateAndListenTcp(unsigned short int p_ui16DestPort)
{
	int sktFd;

	sktFd=e_i32CreateTCPSocket();

	return e_i32ListenTcp(sktFd,p_ui16DestPort);
}

int e_i32ReadInputData(int p_i32FileDescriptor, unsigned char* p_ptrDataBuffer,int p_i32BufferSize)
{
	int p_i32Result;
	p_i32Result= read(p_i32FileDescriptor,p_ptrDataBuffer,p_i32BufferSize);

	if(p_i32Result==-1)
	{
		printf( "(errno: %d) Error reading.[-1] \n", errno);
		return -1;
	}
	return p_i32Result;
}
/************FIN Server****************/

/*************Cliente*********************/

int e_i32ConnectTcpByHost(int p_i32Sockfd,const char* p_ptrHostName,unsigned short int p_ui16DestPort)
{
	int p_i32Result;
	struct sockaddr_in p_strServAddr;
	struct hostent *server;
	
	server = gethostbyname(p_ptrHostName);
    if (server == NULL){
		printf("Error, no such host \n");
		return -1;
	}

	bzero(&p_strServAddr,sizeof(p_strServAddr));
	p_strServAddr.sin_family =  AF_INET;
	p_strServAddr.sin_port=htons(p_ui16DestPort);
	memcpy(&p_strServAddr.sin_addr.s_addr,server->h_addr,server->h_length);
	p_i32Result=connect(p_i32Sockfd, (struct sockaddr *)&p_strServAddr, sizeof(p_strServAddr));

	if(p_i32Result==-1)
		printf( "errno: %d) No connection could be made. \n",errno);
	else
	{
		printf("Successfully connected.[%d]\n",p_i32Result);
	}
	
	

	return p_i32Result;
}

int e_i32ConnectTcp(int p_i32Sockfd,const char* p_ptrDestIP,unsigned short int p_ui16DestPort)
{
	int p_i32Result;
	struct sockaddr_in p_strServAddr;

	bzero(&p_strServAddr,sizeof(p_strServAddr));
	p_strServAddr.sin_family =  AF_INET;
	p_strServAddr.sin_addr.s_addr=inet_addr(p_ptrDestIP);
	p_strServAddr.sin_port=htons(p_ui16DestPort);
	p_i32Result=connect(p_i32Sockfd, (struct sockaddr *)&p_strServAddr, sizeof(p_strServAddr));

	if(p_i32Result==-1)
		printf( "errno: %d) No connection could be made. \n",errno);
	else
	{
		printf("Trying to connect via tcp//%s:%d \n",p_ptrDestIP,p_ui16DestPort);
		printf("Successfully connected.[%d]\n",p_i32Result);
	}
	


	return p_i32Result;
}

int e_i32CreateAndConnectTcp(const char* p_ptrDestIP,unsigned short int p_ui16DestPort)
{
	int sktFd;
	int ConnFd;
	sktFd=e_i32CreateTCPSocket();
	if(sktFd<0)
		return -1;
	ConnFd=e_i32ConnectTcp(sktFd, p_ptrDestIP, p_ui16DestPort);
	if(ConnFd==-1)
	{
		e_i32CloseConnection(sktFd);
		return -1;
	}
	return sktFd;
}

int e_i32SendArray(int p_i32Socketfd,const char *p_ptrBuffer,int p_i32BufferSize)
{
	int p_i32Result;
	p_i32Result= send(p_i32Socketfd,p_ptrBuffer,p_i32BufferSize,0);

	if(p_i32Result==-1)
		printf( "(errno: %d) Error sending array,.[-1] \n",errno);
	/*else
		printf("Array successfully sent, size:%d .[%d] \n",p_i32BufferSize,p_i32Result);*/

	return p_i32Result;
}


/***************FIN cliente*************************/

/****************UDP************************/
int e_i32CreateUDPSocket(void)
{
	int p_i32Result;
	p_i32Result= socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if(p_i32Result==-1)
		printf( "errno: %d) Error creating udp socket.[-1] \n",errno);
	else
		printf("Udp socket created.[%d] \n",p_i32Result);


	return p_i32Result;
}

int e_i32SendUdp(int p_i32Sockfd,const char* p_ptrDestIP,unsigned short int p_ui16DestPort,
					const char* p_ptrBuffer, unsigned int p_ui32BufferSize)
{
	int p_i32Result;
	struct sockaddr_in p_strUdpAddr;

	bzero(&p_strUdpAddr,sizeof(p_strUdpAddr));
	p_strUdpAddr.sin_family =  AF_INET;
	p_strUdpAddr.sin_addr.s_addr=inet_addr(p_ptrDestIP);
	p_strUdpAddr.sin_port=htons(p_ui16DestPort);

	p_i32Result= sendto(p_i32Sockfd,p_ptrBuffer,p_ui32BufferSize,0,
	             (struct sockaddr *)&p_strUdpAddr,sizeof(p_strUdpAddr));

	if(p_i32Result==-1)
		printf( "errno: %d, Error sending Udp packet \n",errno);
	else
	{
		printf("Cliente.[%d] \n",p_i32Result);
	}


	return p_i32Result;

}

int e_i32RecvUdp(int p_i32Sockfd,char* buffer,int size)
{
	int p_i32Result;
	struct sockaddr_storage sender;
	socklen_t sendsize = sizeof(sender);
	bzero(&sender, sizeof(sender));

	p_i32Result= recvfrom(p_i32Sockfd, buffer, size, 0, (struct sockaddr*)&sender, &sendsize);

	if(p_i32Result==-1)
		printf( "errno: %d, Error receiving Udp packet \n",errno);
	else
		printf("Cliente.[%d] \n",p_i32Result);


	return p_i32Result;

}

/*******************************/
