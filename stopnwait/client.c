#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
	int clientfd;
	int framenum,i,recvstatus,ackno,ack_received;
	struct sockaddr_in serverAddr;
	char buffer[1024];
	struct timeval timeout;
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	
	
	//create socket and serverAddr structure
	clientfd = socket(AF_INET,SOCK_STREAM,0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5600);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//connect to server
	connect(clientfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
	printf("Connected to server\n");
	
	//setsockopt for recv timeout
	setsockopt(clientfd,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));
	
	//Input number of frames to be sent
	printf("Enter no of frames to be sent:");
	scanf("%d",&framenum);
	
	//i is the current frame number to be sent
	i=0;
	ack_received =1;//initially true
	while(i<framenum){
		//send frame i
		sprintf(buffer,"%d", i);
		send(clientfd,buffer,sizeof(buffer),0);
		printf("Sent: Frame %d\n",i);
		
		//wait for ack i+1
		recvstatus = recv(clientfd,buffer,sizeof(buffer),0);
		//timed out
		if(recvstatus < 0){
			printf("Timeout!!! Resending frame %d\n",i);
			continue;
		}
	
		//received Ack
		else{
			//check if ack is valid: ackno = i+1
			ackno = atoi(buffer);
			if(ackno == i+1){
				printf("Received: ACK %d\n",ackno);
				i++;
				continue;
			}
			else{
				printf("Received: INVALID ACK %d!!! \n",ackno);
				printf("Resending frame %d ....\n",i);
				continue;		
			}
		}
	}//while
	
	sprintf(buffer,"%d",-1);
	send(clientfd,buffer,sizeof(buffer),0);
	printf("Sent: Total of %d frames",framenum);
	close(clientfd);
	return 0;
}
