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

void free_memory(char** args) {
    if(!args) return;
    for(int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
    free(args);
}


int main(void) {
  setbuf(stdout, NULL);
  char user_input[1024];

  char** args;
  char* which_res;
  char cwd[1024];
  
  int dispatch;
  int p_status;
  int last_status;


  cls();
  
  while(1) {

    if(getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
    }
    printf("[ %s ] > ", cwd);

    if(fgets(user_input, sizeof(user_input), stdin)) {
        user_input[strcspn(user_input, "\n")] = '\0';
        args = parse_input(user_input);

        if(!args || !args[0]) { 
            free(args); 
            continue; 
        }

        dispatch = dispatcher(args);

        if (dispatch == 0) {
            which_res = which(args[0]);
            if (which_res != NULL) {
                execute_command(which_res, args);
                free(which_res); 
            } else {
                fprintf(stderr, "%s: command not found\n", args[0]);
            }
        } 
    }
    free_memory(args);
}
 return 0;    
}


