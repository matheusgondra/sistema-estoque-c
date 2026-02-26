#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
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
#else
#include <unistd.h>

void timeout(int milliseconds)
{
	usleep(milliseconds * 1000);
}

void pause_ui()
{
	printf("Pressione Enter para continuar...");
	getchar();
}
#endif

void config_output()
{
	// setlocale(LC_ALL, "");
	// setlocale(LC_NUMERIC, "C");
}

void get_input(char *input, int size)
{
	fgets(input, size, stdin);
	clear_input_buffer();
	
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