#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    pid_t pid = fork();
    char * argv1[]={"./p1",NULL};
    char * argv[]={"./p2",NULL};
    if (pid==0){
        execv("./p1",argv);
    }
    else{
        execv("./p2",argv);
    }
    
    return 0;
}