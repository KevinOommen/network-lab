#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(){
	int clientfd;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t clientAddrSize;
	
	//create client socket and serverAddr struct
	clientfd = socket(AF_INET,SOCK_STREAM,0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(6265);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//connect to server
	connect(clientfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
	printf("Sending data to server at port:6265\n");
	
	//send message to server
	strcpy(buffer, "Hello there, I am client\n");
	send(clientfd,buffer,sizeof(buffer),0);
	close(clientfd);


	return 0;
}
