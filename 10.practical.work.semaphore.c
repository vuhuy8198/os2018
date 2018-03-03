#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<unistd.h>
#define BUFFER_SIZE 10


typedef struct{
        int type; // O = chicken,       1=Fries
        int amount; 
        int unit; // O=piece, 1 = gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;
pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;


void *produce(void *param){
        item *i = (item *)param;
        if((first + 1) % BUFFER_SIZE == last){
                printf("the conveyor belt is full, cannot produce more");
                return;
        }
		pthread_mutex_lock(&myMutex);
        memcpy(&buffer[first], i, sizeof(item));
        first = (first+1) % BUFFER_SIZE;
        printf("Produce\n");
        printf("first = %d\tlast = %d\n", first, last);
        pthread_mutex_unlock(&myMutex);
        return NULL;
}
void *consume(){
        item *i = malloc(sizeof(item));
        if(first == last){
                printf("There are nothing to comsume\n");
                return NULL;
        }
        pthread_mutex_lock(&myMutex);
        memcpy(i, &buffer[last], sizeof(item));
        last = (last + 1) % BUFFER_SIZE;
        printf("consume\n");
        printf("first = %d\tlast = %d\n", first, last);
         pthread_mutex_unlock(&myMutex);
        return NULL;
}

bool CreateThreadSuccess(int error){
        if(error != 0){
                printf("Error creating thread\n");
                return false;
        }
        else{
                return true;
        }


}

int main(){
        pthread_t consumer;
        pthread_t producer;
        item *i1 = malloc(sizeof(item));
        item *i2 = malloc(sizeof(item));
        item *i3 = malloc(sizeof(item));

        i1->type = 0;
        i1->amount = 10;
        i1->unit = 0;

      i2->type = 1;
        i2->amount = 100;
        i2->unit = 1;

        i3->type = 1;
        i3->amount = 100;
        i3->unit = 1;
        //pthread_mutex_lock(&myMutex);

        int error = -1;

        error = pthread_create(&producer, NULL, produce, &i1);

        if(!CreateThreadSuccess(error)){
                return 1;
        }

        error = pthread_create(&producer, NULL, produce, &i2);
        
        if(!CreateThreadSuccess(error)){
                return 1;
        }
   error = pthread_create(&producer, NULL, produce, &i3);
   //pthread_mutex_unlock(&myMutex);
        
        if(!CreateThreadSuccess(error)){
                return 1;
        }
		//pthread_mutex_lock(&myMutex);
        error = pthread_create(&consumer, NULL, consume, NULL);
        if(!CreateThreadSuccess(error)){
                return 1;
        }


        error = pthread_create(&consumer, NULL, consume, NULL);
        if(!CreateThreadSuccess(error)){
                return 1;
        }
	
        pthread_join(producer, NULL);
        pthread_join(consumer, NULL);   
        printf("Finally, first = %d\tlast = %d\n", first, last);
        	pthread_mutex_destroy(&myMutex);
        return 0;
}
