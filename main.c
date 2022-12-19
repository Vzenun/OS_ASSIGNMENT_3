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
    if (pid>0)
    {
        execl("./p1","./p1",NULL);
    }
    else{
        execl("./p2","./p2",NULL);
    }
    
    return 0;
}