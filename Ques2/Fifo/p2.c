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

# define ll int

ll NUM_STRINGS=50;
ll STRING_LEN=10;

void string_arr_printing(char ** a,ll len){
    for(ll i=0;i<len;i++){
        printf("%s",a[i]);
        printf("%s","\n");
    }
    return;
}

int main(int argc,char * argv[]){
    ll i=0;
    while(i<=49){
        int file_descryptor1=open("testfile1",O_RDONLY);
        char ** b=malloc(5*sizeof(char)*STRING_LEN);
        read(file_descryptor1,b,5*(sizeof(char)*STRING_LEN));
        close(file_descryptor1);
        //string_arr_printing(b,5);
        printf("%s ",b[0]);
        printf("%s ",b[1]);
        printf("%s ",b[2]);
        printf("%s ",b[3]);
        printf("%s",b[4]);
        int file_descryptor2 = open("testfile2", O_RDONLY);
        ll * a=malloc(5*(sizeof(ll)));
        read(file_descryptor2,a,5*sizeof(ll));
        close(file_descryptor2);
        printf("\n%d ",a[0]);
        printf("%d ",a[1]);
        printf("%d ",a[2]);
        printf("%d ",a[3]);
        printf("%d\n",a[4]);
        int file_descryptor3 = open("testfile3", O_WRONLY);
        write(file_descryptor3, &a[4], sizeof(ll));
        close(file_descryptor3);
        i=a[4]+1;
    }
}