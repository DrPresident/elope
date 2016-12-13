#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

unsigned int ret = -1;
char *args = NULL;
char *command = NULL;

void sigint(int sig){
    if(args)
        free(args);
    exit(0);
}

int main(int argc, char **argv) {

    signal(SIGINT, sigint);

    if(argc <= 1){
        fprintf(stderr, "No arguments\n");
        return 1; 
    }
    command = malloc(sizeof(char) * 100);
    command = "/bin/sh";
    strcat(command, argv[1]);
    printf("command: %s", command);

    if(argc > 2){
        args = malloc(sizeof(char) * 100);
        for(int i = 2; i < argc; i++){
            strcat(args, argv[i]);
            strcat(args, " ");
        }
    }
     
    printf("args: %s", args);

    while(execl(argv[1], args) == -1){
        perror("error: ");
    }

    if(args)
        free(args);

    return 0;
}

