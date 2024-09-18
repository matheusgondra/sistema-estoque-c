#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "ui.h"
#include "product.h"
#include "storage.h"

int main() {
	config_output_windows();

	int option;

	showMenu();
	scanf("%d", &option);
	fflush(stdin);

	while (option != 0) {
		switch (option) {
			case 1:
				printf("Cadastrar Novo Item\n");
				char name[100], unit[10], address[50];

				printf("Digite o nome do produto: \n");
				get_input(name, sizeof(name));

				printf("Digite a unidade do produto: \n");
				get_input(unit, sizeof(unit));

				printf("Digite o endereço do produto: \n");
				get_input(address, sizeof(address));

				Product *product = create_product(name, unit, address);
				if (product == NULL) {
					printf("Erro ao cadastrar produto\n");
					exit(1);
				}
				printf("Produto criado com sucesso\n");
				int result = stg_save_product(product);
				if (!result) {
					printf("Erro ao salvar produto\n");
					exit(1);
				}

				printf("Produto cadastrado com sucesso\n");
				timeout(1000);
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
		fflush(stdin);
	}
	return 0;
}