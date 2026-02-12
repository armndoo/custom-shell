#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
  setbuf(stdout, NULL);
  char user_input[1024];
  printf("\e[1;1H\e[2J");
  while(1) {
    printf("$ ");

    fgets(user_input, sizeof(user_input), stdin);
    user_input[strcspn(user_input, "\n")] = '\0';

    if(!strcmp("exit", user_input)) {
      break;
    } else {
      printf("%s: command not found \n", user_input);
      continue;
    }
    if(!strcmp("echo %s", user_input))
      printf("%s", user_input);
  }
  return 0;
}
