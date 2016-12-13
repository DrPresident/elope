#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

FILE *ngtest;
unsigned int ret = -1;
char *str;

void sigint(int sig){
    ret = pclose(ngtest);
    free(str);
    exit(0);
}

int main(int arg, char **argv) {

    str = malloc(sizeof(char) * 100);
    signal(SIGINT, sigint);

    while(ret != 0) {

        ngtest = popen("ng test 2>&1", "r");
        printf("%i", ngtest);

        while(!feof(ngtest)){
            fgets(str, 100, ngtest);
            printf("%s", str);
        }

        ret = pclose(ngtest);
    }

    free(str);

    return 0;
}

