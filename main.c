#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "ui.h"
#include "product.h"

static int g_product_id = 0;

int main() {
	config_output_windows();

	int option;

	showMenu();
	scanf("%d", &option);

	while (option != 0) {
		switch (option) {
			case 1:
				printf("Cadastrar Novo Item\n");
				char name[100], unit[10], address[50];

				printf("Digite o nome do produto: \n");
				get_input(name);

				printf("Digite a unidade do produto: \n");
				get_input(unit);

				printf("Digite o endereço do produto: \n");
				get_input(address);

				Product *product = create_product(g_product_id++, name, unit, address);
				if (product == NULL) {
					printf("Erro ao cadastrar produto\n");
					exit(1);
				} 

				printf("Produto cadastrado com sucesso\n");

				timeout(2000);
				break;
			case 2:
				printf("Entrada de itens\n");
				timeout(2000);
				break;
			case 3:
				printf("Exibir Itens\n");
				timeout(2000);
				break;
			case 4:
				printf("Buscar Item\n");
				timeout(2000);
				break;
			default:
				printf("Opção inválida\n");
		}

		showMenu();
		scanf("%d", &option);
	}
	return 0;
}