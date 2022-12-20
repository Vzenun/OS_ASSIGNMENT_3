#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t forkStore[5];

void * philosopher(void * num)
{
	int phil=*(int *)num;
	while (1){
		if (phil == 4){
			philosopherIsThinking(phil);
			philosopherIsGoingtoPickUpHisNextIndexFork(phil);
			sem_wait(&forkStore[(phil+1)%5]);
			philosopherIsGoingtoPickUpHisCurrentIndexFork(phil);
			philosopherPickedUpHisNextIndexFork(phil);
			sem_wait(&forkStore[phil]);
			philosopherPickedUpHisCurrentIndexFork(phil);
			philosopherIsEating(phil);
			philosopherHasFinishedEating(phil);
			philosopherIsGoingtoPutDownHisCurrentIndexFork(phil);
			sem_post(&forkStore[phil]);
			philosopherPutDownHisCurrentIndexFork(phil);
			philosopherIsGoingtoPutDownHisNextIndexFork(phil);
			sem_post(&forkStore[(phil+1)%5]);
			philosopherPutDownHisNextIndexFork(phil);
		}
		else{
			philosopherIsThinking(phil);
			philosopherIsGoingtoPickUpHisCurrentIndexFork(phil);
			sem_wait(&forkStore[phil]);
			philosopherPickedUpHisCurrentIndexFork(phil);
			philosopherIsGoingtoPickUpHisNextIndexFork(phil);
			sem_wait(&forkStore[(phil+1)%5]);
			philosopherPickedUpHisNextIndexFork(phil);
			philosopherIsEating(phil);
			philosopherHasFinishedEating(phil);
			philosopherIsGoingtoPutDownHisNextIndexFork(phil);
			sem_post(&forkStore[(phil+1)%5]);
			philosopherPutDownHisNextIndexFork(phil);
			philosopherIsGoingtoPutDownHisCurrentIndexFork(phil);
			sem_post(&forkStore[phil]);
			philosopherPutDownHisCurrentIndexFork(phil);
		}
	}
}

int main()
{
	int i;
	int a[5];
	pthread_t threadIDStore[5];

	i = 0;
	while (i < 5){
		sem_init(&forkStore[i],0,1);
		i++;
	}
	
	i = 0;
	while (i < 5){
		a[i] = i;
		pthread_create(&threadIDStore[i],NULL,philosopher,(void *)&a[i]);
		i++;
	}

	i = 0;
	while (i < 5){
		pthread_join(threadIDStore[i],NULL);
		i++;
	}
}