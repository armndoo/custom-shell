#include <complex.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "path_utils.h"

int exec_echo(char** argv) {
  if(!argv || !argv[0]){
    printf("\n");
    return 1;
  } else {
    for(int i = 1; argv[i] != NULL; i++) {
      printf("%s ", argv[i]);
    }
    printf("\n");
    return 1;
  }
  return 0;
}

int exec_type(char** argv) {
    int found = 0;
    int found_builtins = 0;
    char* builtins[] = {"cd", "type", "echo", "exit", "pwd", NULL};
    char* after_command = argv[1];

    if (argv[1] == NULL) {
        printf("type: missing operand\n");
        return 1;
    }

    char* path_command = which(after_command);

    for (int i = 0; builtins[i] != NULL; i++) {
        if (!strcmp(after_command, builtins[i])) {
            printf("%s is a builtin command\n", after_command);
            found_builtins = 1;
            found = 1;
            break; 
        }
    }

    if (found_builtins == 0) {
        if (path_command) {
            printf("%s is %s \n", after_command, path_command);
            found = 1;
        }
    }

    if (found == 0) {
        printf("%s: command not found\n", after_command);
    }

    free(path_command);
    return 0;
}

int exec_exit() {
  exit(1);
}

int dispatcher(char** argv) {
   if(!strcmp(argv[0],"echo")){
     exec_echo(argv);
     return 1;
  }
  if(!strcmp(argv[0],"type")){
       exec_type(argv);
       return 1;
  }
  if(!strcmp(argv[0],"exit")) {
    exec_exit();
    return 1;
  }
  return 0;
}
