#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h> //for exit
int main()
{
	int serverfd, clientfd;
	char buffer[1024];
	struct sockaddr_in serverAddr, clientAddr;
	socklen_t clientAddrSize;
	FILE *fp;
	
	//create server socket and its address
	serverfd = socket(AF_INET,SOCK_STREAM,0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5600);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//bind socket
	bind(serverfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
	
	//listen for connections
	if(listen(serverfd,5)<0)
		printf("Unable to listen!!!!Try Again");
	else
		printf("Listening at port:5600\n");
		
	
	// Accept a connection
    clientfd = accept(serverfd, (struct sockaddr *)&clientAddr, &clientAddrSize);
	printf("Connection established with client\n");

	//receive filename from client
	recv(clientfd,buffer,sizeof(buffer),0);
	printf("Client REQUESTED for file: %s\n",buffer);
	fp=fopen(buffer,"r");
	if(fp==NULL){
		printf("FILE NOT FOUND!!!\n");
		exit(1);
	}
	
	//send file to client
	printf("Sending File to client....\n");
	while(fgets(buffer,sizeof(buffer),fp)){
	send(clientfd,buffer,sizeof(buffer),0);
	}
	send(clientfd,"EOF",sizeof("EOF"),0);
	printf("File sent\n");
	
	close(clientfd);
	close(serverfd);
	
	return 0;

}
