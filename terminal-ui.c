#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "product.h"

void clear_terminal() {
	system("cls");
}

void showMenu() {
	clear_terminal();

	printf("*******************************\n");
  printf("*        MENU PRINCIPAL       *\n");
  printf("*******************************\n");
  printf("* 1. Cadastrar Novo Item      *\n");
  printf("* 2. Exibir Itens             *\n");
  printf("* 3. Buscar Item              *\n");
  printf("* 4. Entrada de itens         *\n");
  printf("* 5. Baixa de itens           *\n");
  printf("* 0. Sair                     *\n");
  printf("*******************************\n");
	printf("Digite a opção desejada: ");
}

void showProducts(Product **product) {
	clear_terminal();

	printf("*******************************\n");
	printf("*        LISTA DE ITENS       *\n");
	printf("*******************************\n");
	printf("* ID | NOME | UNIDADE | ENDEREÇO | QUANTIDADE\n");
	printf("*******************************\n");

	for (int i = 0; product[i] != NULL; i++) {
		printf("* %d | %s | %s | %s | %d\n", product[i]->id, product[i]->name, product[i]->unit, product[i]->address, product[i]->quantity);
	}

	printf("*******************************\n");
}

void showProduct(Product *product) {
	clear_terminal();

	printf("*******************************\n");
	printf("* ID: %d\n", product->id);
	printf("* NOME: %s\n", product->name);
	printf("* UNIDADE: %s\n", product->unit);
	printf("* ENDEREÇO: %s\n", product->address);
	printf("* QUANTIDADE: %d\n", product->quantity);
	printf("*******************************\n");
}