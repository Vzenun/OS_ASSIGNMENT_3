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

int main(int argc,char * argv[]){
    //fifo is really a named pipe
    //abc is the name of thwe file we are going to create in the directory
    int k=mkfifo("abc",0777);
    if(k==-1){
        if(errno!=EEXIST){
            printf("Could not create the abc file\n");
        }
    }
    // 0777 is permission
    //Now file will be created in the directory
    int file_descryptor=open("abc",O_WRONLY);//O_WRONLY
    // I t will stop at above if another point is not opened at all
    int x='V';
    if(write(file_descryptor,&x,sizeof(int))==-1){
        printf("X is not written on the abc");
        return 0;
    }
    close(file_descryptor);
    return 0;
}
// The disadvantage of the above kind of the file is that no way of communication between the processses that are not at all related