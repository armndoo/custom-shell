#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <strings.h>

// Function that clears the terminal screen via an Escape Sequence.
void cls() {
  printf("\e[1;1H\e[2J");
}

int main(int argc, char *argv[]) {

  bool found = false;
  char *builtins[] = {"echo", "type", "exit", NULL};
  setbuf(stdout, NULL);
  char user_input[1024];

  cls();

   do{
      printf("$ > ");
      fgets(user_input, sizeof(user_input), stdin);
      user_input[strcspn(user_input, "\n")] = '\0';

      if(!strcmp("exit", user_input)) break;
    
      if(!strncmp(user_input, "echo ", sizeof("echo ") - 1)) {
        printf("%s \n", user_input + 5);
      }
             
      if (!strncmp(user_input,"type ", sizeof("type ")-1)) {
        for(int i = 0; builtins[i] != NULL; i++) {
          if(!strcmp(user_input +5, builtins[i])) {
            found = true;
            printf("%s is a builtin command\n", builtins[i]);
            break;
          }
        }
        if(!found) printf("%s: command not found\n", user_input + 5);
      }  
    }while(strcmp(user_input, "exit"));
  return 0;    
}
