#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(){
	int serverfd, clientfd;
	struct sockaddr_in serverAddr, clientAddr;
	socklen_t clientAddrSize = sizeof(clientAddr);
	int frameno=0;
	char buffer[1024];

	
	//create server socket and its address structure
	serverfd = socket(AF_INET,SOCK_STREAM,0);
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port = htons(5600);
	serverAddr.sin_addr.s_addr =inet_addr("127.0.0.1");
	
	//bind socket
	bind(serverfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
	
	//listen for connections
	if(listen(serverfd,5)==0)
		printf("Listening at port 5600...\n");
	else{
		printf("Unable to listen!!\n");
		exit(1);
	}
	
	//accept connection
	clientfd = accept(serverfd,(struct sockaddr*)&clientAddr,&clientAddrSize);	
	
	//receive frames and send acknowledgement
	while(frameno<5){
		recv(clientfd,buffer,sizeof(buffer),0);
		
		if(strncmp(buffer,"Frame",5)==0){
			printf("Received %s\n",buffer);
			printf("Sent: ACK %d\n",frameno+1);
			sprintf(buffer,"ACK %d",frameno+1);
			send(clientfd,buffer,sizeof(buffer),0);
			frameno++;
		}
		else{
			printf("NOT received: Frame %d corrupted\n",frameno);
			printf("Sent: NACK %d\n",frameno);
			sprintf(buffer,"NACK %d",frameno);
			send(clientfd,buffer,sizeof(buffer),0);
		}
	}
	close(clientfd);
	close(serverfd);

	return 0;
}

