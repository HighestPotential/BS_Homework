#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>



int main(){
    int i =0;
    pid_t curPid = fork();

    if (curPid==0){
        for(i;i<5; i++){
            
            printf("Hallo, ich bin das Kind von: %i \n", getppid());
            sleep(3);
        }
    }else if( curPid==-1){
       fprintf( stderr, "Erstellen des Kindes fehlgeschlagen.\n");
    }else{
        for(i;i<5; i++){
        printf("Das Kind hat die PID %d \n", curPid);
        sleep(2);
        }
    }

    return 0;
}
