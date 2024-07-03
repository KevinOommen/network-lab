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
	
	FILE* fp;
	//create client socket and serverAddr struct
	clientfd = socket(AF_INET,SOCK_STREAM,0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5600);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//connect to server
	connect(clientfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
	printf("Connected to server at port:5600\n");
	
	//send filename to server
	printf("Enter filename:");
	scanf("%s",buffer);
	send(clientfd,buffer,sizeof(buffer),0);
	
	//receive file from server
	printf("File received from server:\n");
	while(1){
	recv(clientfd,buffer,sizeof(buffer),0);
	if(strncmp(buffer,"EOF",3)==0){
		printf("Got: EOF");
		break;
		}
	else if(strncmp(buffer,"NOF",3)==0){
		printf("FILE NOT FOUND on server!!!\n");
		break;
		}
	printf("%s",buffer);
	}
	
	close(clientfd);
	return 0;
}
