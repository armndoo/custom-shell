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
  char* HOME = getenv("HOME");
  char cwd[1024];
  char* input_status;
  char prompt[1024];

  int p_status;
  int dispatch_res;
  int last_status = 0;


  cls();
  set_sigs();
  chdir(HOME);
  while(1) {
     args = NULL;
     char *home = getenv("HOME");
     int home_len = (home != NULL) ? strlen(home) : 0;

     if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
        strcpy(cwd, "?");
     }

     if (home != NULL && strncmp(cwd, home, home_len) == 0) {
        snprintf(prompt, sizeof(prompt), "[ ~%s ] > ", cwd + home_len);
     } else {
        snprintf(prompt, sizeof(prompt), "[ %s ] > ", cwd);
    }

    printf("%s", prompt);
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

        dispatch_res = dispatcher(args);

        if(dispatch_res != -1) {
            last_status = dispatch_res;
        }
        else{
            which_res = which(args[0]);
            if (which_res != NULL) {
                last_status = execute_command(which_res, args);
                free(which_res); 
            } else {
                fprintf(stderr, "%s: command not found\n", args[0]);
                last_status = 127;
            }
        } 
    }
        free_memory(args);
}
 return 0;    
}


