#include <inttypes.h>
#include <signal.h>
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
#include "utils.h"
#include <errno.h>


int main(void) {
  setbuf(stdout, NULL);
  char user_input[1024];

  char** args;
  char* which_res;
  char cwd[1024];
  
  int dispatch;
  char* input_status;
  int p_status;
  int last_status;

  cls();
  set_sigs();
 while(1) {
     args = NULL;

    if(getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
    }
    printf("[ %s ] > ", cwd);
    fflush(stdout);

    input_status = fgets(user_input, sizeof(user_input), stdin);

    if(input_status == NULL) {
        if(feof(stdin)) break;
        user_input[0] = '\0';
        clearerr(stdin);
        continue;
        
     }

     if(input_status){
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


