#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"

#ifdef _WIN32
#include <windows.h>
void timeout(int milliseconds)
{
	Sleep(milliseconds);
}

void pause_ui()
{
	system("pause");
}

void config_output()
{
	SetConsoleOutputCP(CP_UTF8);
}
#else
#include <unistd.h>

void timeout(int miliseconds)
{
	sleep(miliseconds / 1000);
}

void pause_ui() {
	printf("Pressione Enter para continuar...");
	getchar();
}

void config_output() {}
#endif



void get_input(char *input, int size)
{
	fgets(input, size, stdin);
	
	size_t len = strlen(input);
	
	if (len > 0 && input[len - 1] == '\n')
	{
		input[len - 1] = '\0';
	}
}

char *to_lower(const char *str)
{
	size_t len = strlen(str);
	char *lower_str = (char *)malloc((len + 1) * sizeof(char));
	if (lower_str == NULL)
	{
		fprintf(stderr, "Erro ao alocar memória\n");
		exit(EXIT_FAILURE);
	}

	for (size_t i = 0; i < len; i++)
	{
		lower_str[i] = tolower((unsigned char)str[i]);
	}
	lower_str[len] = '\0';

	return lower_str;
}

bool is_blank(const char *input)
{
	return strlen(input) == 0 || isblank(input[0]);
}

void clear_input_buffer() 
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}

void int_to_str(int value, char *str, size_t size) {
	snprintf(str, size, "%d", value);
}

void float_to_str(float value, char *str, size_t size) {
	snprintf(str, size, "%.2f", value);
}