#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


void cls() {
  printf("\033[H\033[2J");
}


void free_memory(char** args) {
    if(!args) return;
    for(int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
    free(args);
}

void sig_handler(int sig) {
    write(STDOUT_FILENO, "\33[2K\r", 5);    
}

void set_sigs() {
    struct sigaction sa_struct;
    sa_struct.sa_handler = sig_handler;
    sa_struct.sa_flags = 0;
    sigemptyset(&sa_struct.sa_mask);
    if(sigaction(SIGINT,&sa_struct,NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}
