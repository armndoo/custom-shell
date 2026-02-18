#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <strings.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h> 
#include "path_utils.h"

char** tokenize_PATH() { 
  char *PATH_env = strdup(getenv("PATH"));
  
  if(!PATH_env) return NULL;
  char *PATH_temp = strdup(PATH_env);
  int num_folders = 1;


  for (int i = 0; PATH_temp[i] != '\0' ;i++) {
    if(PATH_temp[i] == ':') num_folders++;
  }
  free(PATH_temp);
  
  char *PATH_tok = strtok(PATH_env, ":");
  
  char **PATH_dirs = malloc((num_folders + 1) * sizeof(char*));

  if(!PATH_dirs){
    free(PATH_dirs);  
    return NULL ;
  } 

  
  int i = 0;
  while(PATH_tok != NULL) {
    PATH_dirs[i] = strdup(PATH_tok);
    i++;
    PATH_tok = strtok(NULL, ":");
  }
  PATH_dirs[i] = NULL;
  free(PATH_env);
  return PATH_dirs;
}


void free_PATH (char **dirs) {
  if(dirs == NULL) return;
  for (int i = 0; dirs[i] != NULL; i++) {
    free(dirs[i]);
  }
  free(dirs);
}
char* which(char* command) {
    if (!command) return NULL;
    if(strchr(command, '/') != NULL) {
      if(access(command, X_OK) == 0) {
        return strdup(command);
      }    

      return NULL;
    }
    char **PATH_dirs = tokenize_PATH();
    char *found = NULL;
    char PATH_command[1024];
    if(!PATH_dirs) return NULL;
    for(int i = 0; PATH_dirs[i] != NULL; i++) {
      snprintf(PATH_command,sizeof(PATH_command),"%s/%s",PATH_dirs[i],command);
      if(access(PATH_command, X_OK) == 0) {
        found = strdup(PATH_command);
        break;
      }
    }
    free_PATH(PATH_dirs);
    return found;
}
