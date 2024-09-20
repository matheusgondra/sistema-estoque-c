#include <stdio.h>
#include <locale.h>
#include <string.h>
// #include <windows.h>

int main() {
    // Configurar a localidade para aceitar UTF-8
    setlocale(LC_ALL, "pt_BR.UTF-8");
	// SetConsoleOutputCP(CP_UTF8);


    // Buffer para armazenar o nome
    char nome[100];

    // Solicitar o nome ao usuário
		printf("Digite a opção desejada para o seu nome:");
    
    // Ler o nome da entrada padrão
		fflush(stdin);
    fgets(nome, sizeof(nome), stdin);
		fflush(stdin);
    // Remover o caractere de nova linha, se presente
    size_t len = strlen(nome);
    if (len > 0 && nome[len - 1] == '\n') {
        nome[len - 1] = '\0';
    }

    // Imprimir o nome
    printf("O nome digitado foi: %s\n", nome);

    return 0;
}
