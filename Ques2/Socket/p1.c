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
#include <sys/ipc.h>
#include <signal.h>
#include <semaphore.h>
#include <stdio.h>
#include <netinet/in.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/un.h>


# define ll int
#define ADDRESS "MYSOCKETFILE"

ll NUM_STRINGS=50;

struct Data_Packet{
    char arr_of_string[5][10];
    ll arr_of_index[5];
    ll high_index;
};

int timediff;
#define BILLION 1000000000L;
// considering 01234566789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ

struct Data_Packet packet_generator(char arr[5][10],ll indexarr[5],ll high_index){
    struct Data_Packet * pack= (struct Data_Packet *)malloc(sizeof(struct Data_Packet));
    memcpy(pack->arr_of_index, indexarr, sizeof(int) * 5);
    memcpy(pack->arr_of_string, arr, sizeof(char) * 5*10);
    pack->high_index=high_index;
}

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

void string_printing(char a[10]){
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
    char string_arr[50][10];
    srand(time(NULL));
    for(ll i=0;i<50;i++){
        strcpy(string_arr[i], String_Generator(10));
    }
    for(ll i=0;i<50;i++){
        printf("%d ",i+1);
        string_printing(string_arr[i]);
    }
    
    int sockfd, msgsock;
    int opting=1;

    struct sockaddr_un host_add;
    struct sockaddr_un client_add;

    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        printf("Server socket creation error arsed");
    }

    host_add.sun_family = AF_UNIX;
    strcpy(host_add.sun_path, ADDRESS);

    if (bind(sockfd, (struct sockaddr *)&host_add, sizeof(struct sockaddr_un))){
        perror("binding stream socket");
        unlink(ADDRESS);
        exit(1);
    }

    exit(0);
}
