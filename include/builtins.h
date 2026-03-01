#ifndef BUILTINS_H
#define BUILTINS_H

int exec_echo(char* str);
int exec_type(char* command);
int exec_exit(char** argv);
int dispatcher(char** argv);
#endif
