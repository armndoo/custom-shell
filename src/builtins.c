#include <asm-generic/errno-base.h>
#include <ctype.h>
#include <asm-generic/errno.h>
#include <complex.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "path_utils.h"

int exec_echo(char** argv) {
  if(!argv || !argv[0]){
    printf("\n");
    return 1;
  } else {
    for(int i = 1; argv[i] != NULL; i++) {
      char* to_print = argv[i];
      if(strchr(argv[i], '$')) {
        char* env_value = getenv(argv[i] +1);
        if(env_value == NULL) to_print = "";
        if(env_value != NULL) {
          to_print = env_value;
        }
      } 
        printf("%s ", to_print);
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

int exec_exit(char** argv) {
  if(!argv[1]) exit(0);
  char* err_code = argv[1];
  bool is_numeric = true;
  int status = 0;
  for(int i = 0; err_code[i] != '\0' ; i++) {
    if(i == 0 && err_code[i] == '-') {
      continue;
    } 
    if(!isdigit(err_code[i])) {
      is_numeric = false;
      break;
    }    
  }
  if(!is_numeric) {
   fprintf(stderr, "exit: %s numeric argument required\n", err_code);
   return 1;
  }
  if(argv[2] != NULL) {
    fprintf(stderr,"exit: too many arguments\n");
    return 1;
  }
  status = atoi(err_code);
  exit(status);
}

int exec_cd(char* dir) {
  char* HOME = strdup(getenv("HOME"));
  if(!dir) {
    chdir(HOME);
    return 1;
  }
  if (chdir(dir) != 0) {
    perror("cd");
  }
  free(HOME);
  return 0;
}

int dispatcher(char** argv) {
  if(!strcmp(argv[0],"echo")){
    return exec_echo(argv);
  }
  if(!strcmp(argv[0],"type")){
    return exec_type(argv);
  }
  if(!strcmp(argv[0],"exit")) {
    return exec_exit(argv);
  }
  if(!strcmp(argv[0], "cd")) {
    return exec_cd(argv[1]);
  }
  return -1;
}
