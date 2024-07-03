#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	int clientfd;
	struct sockaddr_in serverAddr;
	socklen_t clientaddrSize;
	char buffer[1024];
	int frameno=0;
	int i=0;
	int ack_received=1;

	//create client socket
	clientfd = socket(AF_INET,SOCK_STREAM,0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5600);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//connect to server 
	connect(clientfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
	
	//send frames and receive acknowldgement
	while(frameno<5){
		//send frame
		if(ack_received){
			printf("Sent: Frame %d\n",frameno);
			if(i==4){
				sprintf(buffer,"Lost Frame %d",frameno);
				send(clientfd,buffer,sizeof(buffer),0);
			}
			else{
			sprintf(buffer,"Frame %d",frameno);
			send(clientfd,buffer,sizeof(buffer),0);	
			}
		}
		//wait for Ack
		recv(clientfd,buffer,sizeof(buffer),0);
		if(strncmp(buffer,"ACK",3)==0){
			printf("Received: %s\n",buffer);
			ack_received=1;
			frameno++;
		}
		else if(strncmp(buffer,"NACK",4)==0){
			printf("Received: %s\n",buffer);
			ack_received=1;
			printf("Resending Frame %d\n",frameno);
			
		}
		else{
			printf("NOT received:ACK %d\n",frameno+1);
			ack_received=0;
		}	
		i++;	
	}	
	close(clientfd);
	return 0;
}
