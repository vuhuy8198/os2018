#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE (10)

typedef struct { 
	char type;
	int amount;
	char unit;
}item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void produce(item *i){
	while ((first + 1) % BUFFER_SIZE == last){
		return;
}
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
}


item *consume() {
	item *i = malloc(sizeof(item));
	while (first == last) {
		return;
	}
	memcpy(i, &buffer[last], sizeof(item));
	last = (last + 1) % BUFFER_SIZE;
	return i;
}

void *produceThread(){	
	item n1,n2,n3;
	n1.type = 0;
        n1.amount = 10;
        n1.unit = 0;
 
 	n2.type = 1;
        n2.amount = 5;
        n2.unit = 1;
 
 	n3.type = 1;
 	n3.amount = 10;
 	n3.unit = 0;

	produce(&n1);
	printf("\nItem1: type: %c, amount: %d, unit: %c, first=%d,last=%d\n",n1.type,n1.amount,n1.unit,first,last);
 	produce(&n2);
	printf("\nItem2: type: %c, amount: %d, unit: %c, first=%d,last=%d\n",n2.type,n2.amount,n2.unit,first,last);
 	produce(&n3);
	printf("\nItem3: type: %c, amount: %d, unit: %c, first=%d,last=%d\n",n3.type,n3.amount,n3.unit,first,last);
}

void *consumeThread(){
	consume();
	printf("\nConsumed item: first = %d, last = %d\n",first, last);
	consume();
	printf("\nConsumed item: first = %d, last = %d\n",first, last);
}

int main(){
	pthread_t tid1,tid2;
 	pthread_create(&tid1,NULL,produceThread,NULL);
 	pthread_join(tid1,NULL);
 
 	pthread_create(&tid2,NULL,consumeThread,NULL);
 	pthread_join(tid2,NULL);
 	return 0;
}
