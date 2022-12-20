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
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <signal.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <time.h>

# define ll int

ll NUM_STRINGS=50;
ll STRING_LEN=10;

int timediff;
#define BILLION  1000000000L;
// considering 01234566789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ

char * String_Generator(ll length){
    char * string_generated=malloc(sizeof(char)*10);
    for(ll i=0;i<length;i++){
        char * m;
        ll k=rand();
        if(k%62>=0 && k%62<=9){
            string_generated[i]='0'+k%62;
        }
        else if(k%62>=10 && k%62<=35){
            string_generated[i]='a'+(k%62)-10;
        }
        else{
            string_generated[i]='A'+k%62-36;
        }
    }
    return string_generated;
}

void string_printing(char * a){
    ll i=0;
    for(ll i=0;i<STRING_LEN;i++){
        printf("%c",a[i]);
    }
    printf("%c",'\n');
    return;
}

void copy_arr(char ** a,char ** b,ll i1,ll length){
    for(ll i=0;i<length;i++){
        char * m=malloc((sizeof(char)*STRING_LEN));
        for(ll j=0;j<STRING_LEN;j++){
            m[j]=b[5*i1+i][j];
            printf("%c",b[5*i1+i][j]);
        }
        a[i]=m;
        printf("\n");
    }
}

void copy_arr2(ll * a,ll i1,ll length){
    for(ll i=0;i<length;i++){
        a[i]=i1+i;
    }
    return;
}

int main(int argc,char * argv[]){
    ll k1=mkfifo("testfile1",0777);
    if(k1==-1){
        if(errno!=EEXIST){
            printf("Could not create the abc file\n");
        }
    }
    ll k2=mkfifo("testfile2",0777);
    if(k2==-1){
        if(errno!=EEXIST){
            printf("Could not create the abc file\n");
        }
    }
    ll k3=mkfifo("testfile3",0777);
    if(k3==-1){
        if(errno!=EEXIST){
            printf("Could not create the abc file\n");
        }
    }
    char ** string_arr=malloc(NUM_STRINGS*(sizeof(char)*STRING_LEN));
    srand(time(NULL));
    for(ll i=0;i<NUM_STRINGS;i++){
        char * m=malloc(sizeof(char)*STRING_LEN);
        string_arr[i]=String_Generator(STRING_LEN);
    }
    for(ll i=0;i<NUM_STRINGS;i++){
        printf("%d ",i+1);
        string_printing(string_arr[i]);
    }
    printf("\n");
    char ** b=malloc(5*(sizeof(char)*STRING_LEN));
    ll * b1=malloc(5*(sizeof(ll)));
    ll i=0;

    struct timespec start, stop;
    clock_gettime( CLOCK_REALTIME, &start);
    while(i<=49){
        int file_descryptor1=open("testfile1",O_WRONLY);
        ll krr=i/5;
        copy_arr(b,string_arr,krr,5);
        sleep(2);
        write(file_descryptor1, b, 5*(sizeof(char)*STRING_LEN));
        close(file_descryptor1);
        int file_descryptor2 = open("testfile2", O_WRONLY);
        copy_arr2(b1,i,5);
        sleep(2);
        write(file_descryptor2, b1, 5*sizeof(ll));
        close(file_descryptor2);
        int file_descryptor3 = open("testfile3", O_RDONLY);
        ll * index_recceived=malloc(sizeof(ll));
        read(file_descryptor3, index_recceived, sizeof(ll));
        printf("HighestIndex received from P2 is %d\n\n", *index_recceived);
        close(file_descryptor3);
        i=*index_recceived+1;
    }
    clock_gettime( CLOCK_REALTIME, &stop);
    timediff=( stop.tv_sec - start.tv_sec );
    int timediffn_s=( stop.tv_nsec - start.tv_nsec );
    printf("%d\n",timediff);
    return 0;
}
