#include <sys/socket.h>
#include <sys/time.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
	int clientfd;
	int recvstatus, ackno, flag=1;
	int win_size, framenum,winstart,winend, i;
	struct sockaddr_in serverAddr;
	char buffer[1024];
	struct timeval timeout;
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	
	//create client socket and serverAddr struct
	clientfd = socket(AF_INET,SOCK_STREAM,0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5600);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//connect to server
	connect(clientfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
	printf("Connected to server:\n");
	
	//set socket recv() timeout
	setsockopt(clientfd,SOL_SOCKET, SO_RCVTIMEO,&timeout,sizeof(timeout));
	
	//Ask user for inputs
	printf("Enter the window size, no of frames:");
	scanf("%d %d",&win_size,&framenum);
	printf("Sender Window (N==%d) Frames to be sent:%d\n",win_size,framenum);
	
	
	winstart = 0;
	winend = winstart + (win_size-1);
	i=winstart;
	
	while(winstart<winend){	
		//send frames in window
		while(i<=winend){
			sprintf(buffer,"%d",i);
			printf("Sent: Frame %d\n",i);
			send(clientfd,buffer,sizeof(buffer),0);
			i++;
		}
		
		//wait to receive Ack
		recvstatus = recv(clientfd,buffer,sizeof(buffer),0);
		
		//if timeout resend frame
		if(recvstatus<0){
			printf("Timeout Error!! Resending frames %d to %d\n",winstart,winend);
			i=winstart;
			continue; 
		}
		
		//else Ack is received
		else
		{		
			ackno = atoi(buffer);
			printf("Received: ACK %d\n",ackno);
			//check if ack is valid
			if(ackno==winstart+1){
				winstart++;
				winend = (winend<framenum)?  ++winend: winend;				
			}//if valid ack
		}//else	received ack
	}//while
	close(clientfd);
	return 0;
}
