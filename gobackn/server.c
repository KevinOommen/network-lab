#include <sys/socket.h>
#include <sys/time.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
	int serverfd,clientfd;
	int frameno,nextframeno=0;
	struct sockaddr_in serverAddr,clientAddr;
	socklen_t clientAddrSize = sizeof(clientAddr);
	char buffer[1024];
	
	//create server socket and serverAddr struct
	serverfd = socket(AF_INET,SOCK_STREAM,0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5600);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//bind socket
	bind(serverfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
	
	//listen for connections
	if(listen(serverfd,5)==0)
		printf("Listening at port:5600\n");
	else{
		perror("Listen failed");
		return 1;
	}
	
	
	//accept client connection
	clientfd = accept(serverfd,(struct sockaddr*)&clientAddr,&clientAddrSize);
	printf("Connected to client\n");
	
	//receive frames from sender client
	while(nextframeno!=8){
		recv(clientfd,buffer,sizeof(buffer),0);
		frameno = atoi(buffer);
		printf("Received: Frame %d\n",frameno);
		if(frameno==nextframeno){
			nextframeno++;
			printf("Sent: ACK %d\n",nextframeno);
			sprintf(buffer,"%d",nextframeno);
			send(clientfd,buffer,sizeof(buffer),0);
		}
		else
			printf("Discarded frame %d , out of order",frameno);	
	}//while	
	close(clientfd);
	close(serverfd);
	return 0;
}//main
