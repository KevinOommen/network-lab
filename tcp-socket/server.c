#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int serverfd, clientfd;
	char buffer[1024];
	struct sockaddr_in serverAddr, clientAddr;
	socklen_t clientAddrSize;
	
	//create server socket and its address
	serverfd = socket(AF_INET,SOCK_STREAM,0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(6265);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//bind socket
	bind(serverfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
	
	//listen for connections
	if(listen(serverfd,5)==0)
		printf("Listening at port:6265\n");
	else
		printf("Unable to listen!!!!Try Again");
	
	//accept a connection
	clientfd = accept(serverfd,(struct sockaddr *)&clientAddr,&clientAddrSize);

	//receive data from client
	recv(clientfd, buffer, 1024,0);
	printf("Data Received from client: %s",buffer);
	
	close(clientfd);
	close(serverfd);
	
	return 0;

}
