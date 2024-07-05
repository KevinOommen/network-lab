#include <sys/socket.h>
#include <sys/time.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "color.h"

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
	while(1){
		recv(clientfd,buffer,sizeof(buffer),0);
		frameno = atoi(buffer);
		srand(time(0));
		sleep(2);
		
		if(frameno==nextframeno){
			
			if(rand()%50<10){
				printf("Lost Frame:%d\n",frameno);
				continue;
			}
			nextframeno++;
			//printf("Received: Frame %d\n",frameno);
			LOG_GREEN("Received: Frame ");
			printf("%d\n",frameno);
			printf("Sent: ACK %d\n",nextframeno);
			sprintf(buffer,"%d",nextframeno);
			send(clientfd,buffer,sizeof(buffer),0);
		}
		//exit server
		else if(frameno==-1){
			printf("Received %d Frames\n",nextframeno);
			break;
		}//
		else{
			printf("Received: Frame %d\n",frameno);
			printf("Discarded frame %d ,out of order\n",frameno);	
		}
		
			
	}//while	
	close(clientfd);
	close(serverfd);
	return 0;
}//main
