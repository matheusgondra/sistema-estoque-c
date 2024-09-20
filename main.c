#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "product.h"
#include "storage.h"
#include "ui.h"

int main() {
	config_output();

	int option = -1;

	showMenu();
	scanf("%d", &option);
	fflush(stdin);

	while (option != 0) {
		switch (option) {
			case 1:
				printf("Cadastrar Novo Item\n");
				char name[256], unit[10], address[50];

				printf("Digite o nome do produto \n");
				get_input(name, sizeof(name));
				printf("Nome do produto recebido: %s\n", name);

				printf("Digite a unidade do produto \n");
				get_input(unit, sizeof(unit));

				printf("Digite o endereço onde será armazenado o produto: \n");
				get_input(address, sizeof(address));

				Product *product = create_product(name, unit, address);
				if (product == NULL) {
					printf("Erro ao cadastrar produto\n");
					exit(1);
				}

				int result = stg_save_product(product);
				if (!result) {
					printf("Erro ao salvar produto\n");
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
				printf("Saída de itens\n");

				Product **products = stg_load_products();
				if (products == NULL) {
					printf("Nenhum produto cadastrado\n");
					timeout(2000);
					break;
				}

				showProducts(products);

				timeout(2000);
				system("pause");
				break;
			case 4:
				printf("Buscar Item\n");
				timeout(2000);
				break;
			default:
				printf("Opção inválida\n");
				timeout(2000);
		}

		showMenu();
		scanf("%d", &option);
		fflush(stdin);
	}
	return 0;
}