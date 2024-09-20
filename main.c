#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "product.h"
#include "storage.h"
#include "ui.h"

#define REGISTER_PRODUCT 1
#define PRODUCT_ENTRY 2
#define LOAD_PRODUCTS 3
#define SEARCH_PRODUCT 4

int main() {
	config_output();

	int option = -1;

	showMenu();
	scanf("%d", &option);
	fflush(stdin);

	Product *product;
	Product **product_list;

	while (option != 0) {
		switch (option) {
			case REGISTER_PRODUCT:
				printf("Cadastrar Novo Item\n");
				char name[256], unit[10], address[50];

				printf("Digite o nome do produto \n");
				get_input(name, sizeof(name));
				printf("Nome do produto recebido: %s\n", name);

				printf("Digite a unidade do produto \n");
				get_input(unit, sizeof(unit));

				printf("Digite o endereço onde será armazenado o produto: \n");
				get_input(address, sizeof(address));

				product = create_product(name, unit, address);
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
			case PRODUCT_ENTRY:
				printf("Entrada de itens\n");
				timeout(2000);
				break;
			case LOAD_PRODUCTS:
				product_list = stg_load_products();
				if (product_list == NULL) {
					printf("Nenhum produto cadastrado\n");
					timeout(2000);
					break;
				}

				showProducts(product_list);

				timeout(2000);
				system("pause");
				break;
			case SEARCH_PRODUCT:
				printf("Digite o id do produto:\n");
				int id;
				scanf("%d", &id);
				fflush(stdin);

				product = stg_find_product(id);
				if (product == NULL) {
					printf("Produto não encontrado\n");
					timeout(2000);
					break;
				}

				showProduct(product);

				timeout(2000);
				system("pause");
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