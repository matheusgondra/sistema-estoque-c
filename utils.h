#ifndef UTILS_H
#define UTILS_H

#define TRUE 1
#define FALSE 0
#define SECOND 1000

typedef int BOOL;

void config_output();
void timeout(int miliseconds);
void get_input(char *input, int size);
BOOL is_blank(const char *input);
char *to_lower(const char *str);

#endif