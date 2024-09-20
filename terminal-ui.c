#include <stdio.h>
#include <stdlib.h>
#include "ui.h"

void clear_terminal() {
	system("cls");
}

void showMenu() {
	clear_terminal();

	printf("*******************************\n");
  printf("*        MENU PRINCIPAL       *\n");
  printf("*******************************\n");
  printf("* 1. Cadastrar Novo Item      *\n");
  printf("* 2. Entrada de itens         *\n");
  printf("* 3. Exibir Itens             *\n");
  printf("* 4. Buscar Item              *\n");
  printf("* 0. Sair                     *\n");
  printf("*******************************\n");
	printf("Digite a opção desejada: ");
}

