#ifndef PATH_UTILS_H
#define PATH_UTILS_H

char** tokenize_PATH();
char* which(char* command);
void free_PATH(char **dirs);

#endif
