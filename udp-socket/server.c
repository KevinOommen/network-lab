#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int serverfd;
	struct sockaddr_in serverAddr,clientAddr;
	char msg[1024];
	socklen_t clientAddrSize;
	
	//create server socket and its address
	serverfd = socket(AF_INET,SOCK_DGRAM,0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port =htons(2002);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientAddrSize = sizeof(clientAddr);
	//bind socket
	bind(serverfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));

	//listen to receive from clients
	recvfrom(serverfd,msg,sizeof(msg),0,(struct sockaddr*)&clientAddr,&clientAddrSize);
	printf("Listening at port:2002...\n");
	printf("Received Message from client:%s\n",msg);
	
	//send message to the above client
	strcpy(msg,"Hello client, this is server");
	sendto(serverfd,msg,strlen(msg),0,(struct sockaddr*)&clientAddr,sizeof(clientAddr));
	
	//close socket
	close(serverfd);
	return 0;	
}
