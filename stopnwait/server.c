#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
	int serverfd,clientfd;
	int frameno,ackno,nextframeno; int recvstatus;
	struct sockaddr_in serverAddr,clientAddr;
	socklen_t clientAddrSize;
	char buffer[1024];
	
	//create socket and addr struct
	serverfd = socket(AF_INET,SOCK_STREAM,0);
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(5600);
	serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	//bind socket to address
	bind(serverfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
	
	//listen for incoming connections
	if(listen(serverfd,5)==0){
		printf("Listening at port 5600...\n");
	}
	else{
		perror("Listen failed:\n");
		return 1;
	}
	
	//accept incoming connection from client
	clientfd = accept(serverfd, (struct sockaddr*)&clientAddr,&clientAddrSize);
	printf("Connected to client\n");
	
	nextframeno=0;
	while(1){
		//receive frame from client
		//memset(buffer,0,sizeof(buffer));
		recvstatus = recv(clientfd,buffer,sizeof(buffer),0);
		frameno = atoi(buffer);
		srand(time(0));
		sleep(1);
		if(frameno == nextframeno){
			//simulating loss
			if(rand()%50<10){
				printf("Lost frame %d \n",frameno);
				continue;
			}
			nextframeno++;
			ackno = nextframeno;
			printf("Received: Frame %d \n",frameno);
			sprintf(buffer,"%d",ackno);
			send(clientfd,buffer,sizeof(buffer),0);
			printf("Sent: ACK %d \n",ackno);
			
		}
		else if(frameno==-1){
			printf("Received: Total of %d frames",nextframeno);
			break;
		}
		else{
			printf("Received: Invalid Frame %d, out of order\n",frameno);
			continue;
		}
	}//while loop
	close(clientfd);
	close(serverfd);
	
	return 0;
}

