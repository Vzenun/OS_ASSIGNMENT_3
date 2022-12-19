//Vidur Goel Question Number 2.b

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> //linux specific library
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h> //Used for handling directory files
#include <errno.h> //For EXIT codes and error handling
#include <stddef.h>
#include <fcntl.h>
#include <time.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <signal.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
# define ll int

pthread_mutex_t forks[5];

//There are fork 1 and fork 2 and fork 3 and fork 4 and fork 5

//Here philosopher 1 have the fork 1 in it's left and fork 2 in its right
//Here philosopher 2 have the fork 2 in it's left and fork 3 in its right
//Here philosopher 3 have the fork 3 in it's left and fork 4 in its right
//Here philosopher 4 have the fork 4 in it's left and fork 5 in its right
//Here philosopher 5 have the fork 5 in it's left and fork 1 in its right

pthread_mutex_t lock;

//this locks works in such a way that if the one person is in process of picking 
//up its fork then no other person can start their process of picking up their fork

void process_of_picking_initiated(int n){
    pthread_mutex_lock(&lock);
    printf("Philosopher %d has initiated the process of picking up the fork %d and fork %d and thus locked the lock\n", n,(n)%5,(n+1)%5);
}

void process_of_picking_finished(int n){
    pthread_mutex_unlock(&lock);
    printf("Philosopher %d has finished the process of picking up the fork %d and fork %d and thus unlocked the lock\n", n,(n)%5,(n+1)%5);
}

void postingforks(int n){
    sem_post(&forks[n]);
    sem_post(&forks[(n+1)%5]);
    printf("Philosopher %d has released fork %d and fork %d resources\n", n,(n)%5,(n+1)%5);
}

void eat(int n){
    printf("Philosopher %d has started eating with forks %d and fork %d\n", n,(n)%5,(n+1)%5);
    sleep(5);
    printf("Philosopher %d has finished eating with fork %d and fork %d\n", n,(n)%5,(n+1)%5);
}

void waitingforks(int n){
    sem_wait(&forks[n]);
    sem_wait(&forks[(n+1)%5]);
    printf("Philosopher %d has locked forks %d and fork %d resources for eating\n", n,(n)%5,(n+1)%5);
}

void think(int n){
    printf("Philosopher %d is thinking\n", n);
}

void * dine(void * num){
    while(1){
        think(*(int *)num);
        process_of_picking_initiated(*(int *)num);
        waitingforks(*(int *)num);
        process_of_picking_finished(*(int *)num);
        eat(*(int *)num);
        postingforks(*(int *)num);
    }
} 

int main(int argc,char * argv[]){
	int philosophers[5];

	pthread_t threadID[5];

    pthread_mutex_init(&lock,NULL);

	for(ll i=0;i<5;i++){
		pthread_mutex_init(&forks[i],NULL);
	}
	
	for(ll i=0;i<5;i++){
		philosophers[i] = i;
		if (pthread_create(&threadID[i], NULL, dine, (void *)&philosophers[i]) == -1){
            printf("error in creating pthread %d \n",i);
        }
	}

	for(ll i=0;i<5;i++){
		pthread_join(threadID[i],NULL);
	}
    
    return 0;
}
