#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> //linux specific library
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

# define ll long long int

sem_t semaphore;

void * routine(void * args){
    sem_wait(&semaphore);
    printf("%s%d"," Hello ",*(int *)args);
    sem_post(&semaphore);
    return NULL;
}

int main(int argc,char * argv[]){
    sem_open((char)&semaphore,0,2);
    pthread_t p[5];
    for(int i=0;i<5;i++){
        int * ar=malloc(sizeof(int));
        *ar=i;
        if(pthread_create(&p[i],NULL,&routine,ar)!=0){
            perror("we have failed to create thread");
        }
    }
    for(int i=0;i<5;i++){
        if(pthread_join(p[i],NULL)!=0){
            perror("we have failed to make the thread join");
        }
    }
    sem_close(&semaphore);
    return 0;
}
