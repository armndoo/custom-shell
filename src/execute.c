#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <strings.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h> 
#include "path_utils.h"
#include "parser.h"
#include "builtins.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

int execute_command(char* path, char** args){
  int status;
  pid_t pid = fork();

  if(pid < 0) {
    perror("fork");
    return 1;
  }

  if(pid == 0) {
    execv(path,args);
    perror("execv");
    _exit(1);
  }
  
  waitpid(pid, &status, 0);

  if(WIFEXITED(status)) {
    printf("The command terminated with code (%d)\n",WEXITSTATUS(status));
    return WEXITSTATUS(status);
  }

  if(WIFSIGNALED(status)) {
    printf("The command was killed by signal (%d) \n", WTERMSIG(status));
    return 128 + WTERMSIG(status);
  }
  return 0;
}
