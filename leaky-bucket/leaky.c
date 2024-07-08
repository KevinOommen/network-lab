#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

struct Packet{
	int id;
	int size;
};
typedef struct Packet Packet;
int main(){
	int i, packetCount,leakrate,bucketSize,remainSize,bytesInBucket,transmitSize;
	int incomingPacketID,incomingPacketSize;
	Packet packet[SIZE];
	printf("Enter number of packets to arrive:");
	scanf("%d",&packetCount);
	
	//intialising random packet sizes in range[10 to 50]
	for(int i=0;i<packetCount;i++){
		packet[i].id = i+1;
		packet[i].size = (rand()%5+1)*10;
	}
	
	printf("Enter leak rate and bucket size:");
	scanf("%d %d",&leakrate,&bucketSize);
	
	//printing packets in order of arrival
	printf("Incoming pkts in order of arrival\n");
	for(int i=0;i<packetCount;i++){
		printf("Packet ID: %d , size = %d\n",packet[i].id,packet[i].size);
	}
	
	i=0;
	remainSize = bucketSize;
	bytesInBucket = 0;
	printf("Initial Bucket Size= %d\n",bucketSize);
	while(i<packetCount || bytesInBucket>0){
		if(i<packetCount){
		incomingPacketID = packet[i].id;
		incomingPacketSize = packet[i].size;
		if(incomingPacketSize <= remainSize){
			remainSize = remainSize - incomingPacketSize;
			bytesInBucket = bucketSize - remainSize;
			printf("\nIncoming Packet ID:%d of size %d -> Into Bucket\n",packet[i].id,packet[i].size);
			printf("Remaining Bucket Size = %d\n",remainSize);
			i++;
		}
		else{
			printf("Incoming Packet ID:%d of size %d -> DISCARDED \n",packet[i].id,packet[i].size);
			printf("Remaining Bucket Size = %d \n",remainSize);
			bytesInBucket = bucketSize - remainSize;
			i++;
		}
		}//if i < packetcount
		//Transmit the bytes present in bucket at output rate
		
		if(bytesInBucket > 0){
			transmitSize = (bytesInBucket<=leakrate)? bytesInBucket : leakrate;
			printf("----Transmitting %d bytes \n",transmitSize);
			remainSize = remainSize + transmitSize; 
			bytesInBucket = bytesInBucket - transmitSize;
			printf("----Remaining Bytes in Bucket = %d\n",bytesInBucket);
			printf("Remaining Bucket Size = %d\n",remainSize);
		}  
		else{
			printf("No bytes in bucket to transmit \n");
			printf("Remaining Bucket Size = %d\n",remainSize);
		}
		
	}//while loop
	
	return 0;
}
