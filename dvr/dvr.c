#include <stdio.h>
#define SIZE 10

int costmat[SIZE][SIZE];
struct{
	int distance[SIZE];
	int adj[SIZE];
}node[SIZE];
int n;


void readCostMatrix(){
	int i,j;
	printf("Enter cost matrix(n=%d):- \n",n);
	for(i=0;i<n;i++){
		printf("Router %d: ",(i+1));
		for(j=0;j<n;j++){
				scanf("%d",&costmat[i][j]);
				costmat[i][i]=0;
				node[i].distance[j] = costmat[i][j];
				node[i].adj[j] = j;
		}
		printf("\n");
	}
}

void calcRoutingTable(){
	//bellman-ford algorithm
	int i,j,k;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			for(k=0;k<n;k++){
				if(node[i].distance[j] > costmat[i][k] + node[k].distance[j]){
					node[i].distance[j] = costmat[i][k] + node[k].distance[j];
					node[i].adj[j] = k; 
				}
			}
		}
	}

} 
void displayShortestRoutes(){
	int i,j;
	//print heading and columns
	printf("Shortest Path - Routing Table\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("From Node %d to node %d = %d via node %d\n",i,j,node[i].distance[j],node[i].adj[j]);
		}
		printf("\n");
	}
	

}

int main(){
	
	printf("Enter no of routers:");
	scanf("%d",&n);
	readCostMatrix();
	calcRoutingTable();
	displayShortestRoutes();
	return 0;

}
