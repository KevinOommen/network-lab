#include <stdio.h>
#include <stdlib.h>
#define limit 10

int main(){
	for(int i=1;i<=limit;i++){
		printf("%d. Random number = %d \n",i,(rand()%10 +1)*10);
	}
	return 0;
}
