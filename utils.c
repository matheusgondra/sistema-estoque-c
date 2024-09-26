#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <locale.h>
#include "utils.h"

#ifdef _WIN32
#include <windows.h>

void timeout(int milliseconds) {
  Sleep(milliseconds);
}
#else
#include <unistd.h>

void timeout(int milliseconds) {
	sleep(milliseconds * 1000);
}
#endif

void config_output() {
	// setlocale(LC_ALL, "Portuguese");
}

void get_input(char *input, int size) {
	fgets(input, size, stdin);
	fflush(stdin);

	size_t len = strlen(input);

	if (len > 0 && input[len - 1] == '\n') {
			input[len - 1] = '\0';
	}
}