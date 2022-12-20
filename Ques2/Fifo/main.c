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
    char * argv1[]={"/Users/vidurgoel/Exam/p1",NULL};
    char * argv[]={"/Users/vidurgoel/Exam/p2",NULL};
    if (pid==0){
        execv("/Users/vidurgoel/Exam/p1",argv);
    }
    else{
        execv("/Users/vidurgoel/Exam/p2",argv);
    }
    
    return 0;
}