#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
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

char *to_lower(const char *str) {
	size_t len = strlen(str);
	char *lower_str = (char *) malloc((len + 1) * sizeof(char));
	if (lower_str == NULL) {
		fprintf(stderr, "Erro ao alocar memória\n");
		exit(EXIT_FAILURE);
	}

	for (size_t i = 0; i < len; i++) {
		lower_str[i] = tolower((unsigned char) str[i]);
	}
	lower_str[len] = '\0';

	return lower_str;
}

BOOL is_blank(const char *input) {
	if (strlen(input) == 0 || isblank(input[0])) {
		return TRUE;
	}
	
	return FALSE;
}