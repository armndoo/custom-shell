#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char** parse_input(char* str) {
    if (!str) return NULL;

    char* delim = " \t\n\r";
    char* w_ptr = str; 
    char* token;
    char** argv;

    int num_words = 0;
    int in_word = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i])) {
            if (!in_word) {
                num_words++;
                in_word = 1;
            }
        } else {
            in_word = 0;
        }
    }

    argv = malloc((num_words + 1) * sizeof(char*));
    if (!argv) return NULL;

    int i = 0;
    while ((token = strsep(&w_ptr, delim)) != NULL) {
        if (token[0] != '\0') { 
            argv[i] = strdup(token); 
            i++;
        }
    }

    argv[i] = NULL; 
    return argv;
}
