#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int clientfd;
	struct sockaddr_in serverAddr,clientAddr;
	char msg[1024];
	socklen_t serverAddrSize;
	
	//create client socker
	clientfd = socket(AF_INET,SOCK_DGRAM,0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(2002);
	serverAddr.sin_addr.s_addr =inet_addr("127.0.0.1");
	serverAddrSize = sizeof(serverAddr);
	//send message to server
	strcpy(msg,"Hi server this is client\n");
	printf("Sending message to server...\n");
	sendto(clientfd,msg,strlen(msg),0,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
	
	//receive message from server
	recvfrom(clientfd,msg,sizeof(msg),0,(struct sockaddr*)&serverAddr,&serverAddrSize);
	printf("Received Message from server:%s\n",msg);
	
	close(clientfd);
	return 0;
}
