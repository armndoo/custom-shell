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
#include "execute.h"
#include "builtins.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

static inline void cls() {
  printf("\033[H\033[2J");
}


int main(void) {
  setbuf(stdout, NULL);
  char user_input[1024];

  char** args;
  char* which_res;
  int dispatch;
  int p_status;
  int last_status;

  pid_t pid = fork();

  cls();
  
  while(1){
      printf("> ");
      if(fgets(user_input, sizeof(user_input), stdin)) {
        user_input[strcspn(user_input, "\n")] = '\0';
        args = parse_input(user_input);
        if(!args || !args[0]) continue;
        dispatch = dispatcher(args);
        if (dispatch == 0) {
          which_res = which(args[0]);
          execute_command(which_res, args);
          if(which_res == 0) {
            fprintf(stderr,"%s: command not found \n", user_input);
          }
        } else {
          execute_command(which_res, args);
          free(which_res);
        }
    }
    free(args);
  }   
  return 0;    
}


