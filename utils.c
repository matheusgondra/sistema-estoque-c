#include <stdio.h>
#include <windows.h>
#include "utils.h"

void config_output_windows() {
	SetConsoleOutputCP(CP_UTF8);
}

void timeout(int miliseconds) {
	Sleep(miliseconds);
}

void get_input(char *input, int size) {
	fgets(input, size, stdin);
	fflush(stdin);

	size_t len = strlen(input);

	int is_not_blank = len > 0;
	int is_new_line = input[len - 1] == '\n';

	if (is_not_blank && is_new_line) {
		input[len - 1] = '\0';
	}
}