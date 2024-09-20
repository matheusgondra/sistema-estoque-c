#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <locale.h>
#include "utils.h"

void config_output() {
	setlocale(LC_ALL, "pt_BR.UTF-8");
}

void timeout(int miliseconds) {
	Sleep(miliseconds);
}

void get_input(char *input, int size) {
	fgets(input, size, stdin);
	fflush(stdin);

	size_t len = strlen(input);

	if (len > 0 && input[len - 1] == '\n') {
			input[len - 1] = '\0';
	}
}