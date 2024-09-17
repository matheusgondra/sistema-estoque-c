#include <stdio.h>
#include <windows.h>
#include "utils.h"

void config_output_windows() {
	SetConsoleOutputCP(CP_UTF8);
}

void timeout(int miliseconds) {
	Sleep(miliseconds);
}

void get_input(char *input) {
	fgets(input, sizeof(input), stdin);
	fflush(stdin);
}