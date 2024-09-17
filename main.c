#include <stdio.h>
#include <windows.h>
#include "ui.h"

int main() {
	SetConsoleOutputCP(CP_UTF8);
	int option;

	showMenu();
	scanf("%d", &option);

	while (option != 0) {
		switch (option) {
			case 1:
				printf("Cadastrar Novo Item\n");
				Sleep(2000);
				break;
			case 2:
				printf("Entrada de itens\n");
				Sleep(2000);
				break;
			case 3:
				printf("Exibir Itens\n");
				Sleep(2000);
				break;
			case 4:
				printf("Buscar Item\n");
				Sleep(2000);
				break;
			default:
				printf("Opção inválida\n");
		}

		showMenu();
		scanf("%d", &option);
	}
	return 0;
}