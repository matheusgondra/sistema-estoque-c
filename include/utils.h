#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

#define SECOND 1000

void config_output();
void timeout(int miliseconds);
void get_input(char *input, int size);
bool is_blank(const char *input);
char *to_lower(const char *str);
void clear_input_buffer();
void int_to_str(int value, char *str, size_t size);
void float_to_str(float value, char *str, size_t size);

#endif