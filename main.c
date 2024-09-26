#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "product.h"
#include "storage.h"
#include "ui.h"

#define REGISTER_PRODUCT 1
#define LOAD_PRODUCTS 2
#define SEARCH_PRODUCT 3
#define PRODUCT_ENTRY 4
#define PRODUCT_EXIT 5

#define TIMEOUT SECOND * 2

int main() {
	config_output();

	int option = -1;

	showMenu();
	scanf("%d", &option);
	fflush(stdin);

	Product *product, **product_list;
	int id;
	float qtd;
	char name[256], unit[10], address[50];

	while (option != 0) {
		switch (option) {
			case REGISTER_PRODUCT:
				printf("Digite o nome do produto \n");
				get_input(name, sizeof(name));
				if (is_blank(name)) {
					printf("Nome do produto n�o pode ser vazio\n");
					timeout(TIMEOUT);
					break;
				}

				printf("Digite a unidade do produto \n");
				get_input(unit, sizeof(unit));
				if (is_blank(unit)) {
					printf("Unidade do produto n�o pode ser vazia\n");
					timeout(TIMEOUT);
					break;
				}

				printf("Digite o endere�o onde ser� armazenado o produto: \n");
				get_input(address, sizeof(address));
				if (is_blank(address)) {
					printf("Endere�o do produto n�o pode ser vazio\n");
					timeout(TIMEOUT);
					break;
				}

				product = create_product(name, unit, address);
				if (product == NULL) {
					printf("Erro ao cadastrar produto\n");
					exit(EXIT_FAILURE);
				}

				int result = stg_save_product(product);
				if (!result) {
					printf("Erro ao salvar produto\n");
					exit(EXIT_FAILURE);
				}

				printf("Produto cadastrado com sucesso\n");
				free_product(product);
				timeout(TIMEOUT);
				break;
			case PRODUCT_ENTRY:
				printf("Digite o id do produto:\n");
				scanf("%d", &id);
				fflush(stdin);

				product = stg_find_product(id);
				if (product == NULL) {
					printf("Produto n�o encontrado\n");
					timeout(TIMEOUT);
					break;
				}
				
				printf("Digite a quantidade de entrada do produto:\n");
				scanf("%f", &qtd);
				fflush(stdin);

				result = put_product_quantity(product, qtd);
				if (!result) {
					printf("Erro dar entrada no produto\n");
					free_product(product);
					timeout(TIMEOUT);
					break;
				}

				result = stg_update_product_quantity(product);
				if (!result) {
					printf("Erro ao atualizar quantidade do produto\n");
					free_product(product);
					timeout(TIMEOUT);
					break;
				}
				
				showProduct(product);
				printf("Entrada de produto realizada com sucesso\n");

				free_product(product);
				timeout(TIMEOUT);
				system("pause");
				break;
			case PRODUCT_EXIT:
				printf("Digite o id do produto:\n");
				scanf("%d", &id);
				fflush(stdin);

				product = stg_find_product(id);
				if (product == NULL) {
					printf("Produto n�o encontrado\n");
					timeout(TIMEOUT);
					break;
				}

				printf("Digite a quantidade de sa�da do produto (use ponto em vez de v�rgula em n�meros com casas decimais):\n");
				scanf("%f", &qtd);
				fflush(stdin);

				if (product->quantity < qtd) {
					printf("Quantidade insuficiente\n");
					free_product(product);
					timeout(TIMEOUT);
					break;
				}

				product->quantity -= qtd;
				result = stg_update_product_quantity(product);
				if (!result) {
					printf("Erro ao atualizar quantidade do produto\n");
					free_product(product);
					timeout(TIMEOUT);
					break;
				}

				showProduct(product);
				printf("Sa�da de produto realizada com sucesso\n");

				free_product(product);
				timeout(TIMEOUT);
				system("pause");
				break;
			case LOAD_PRODUCTS:
				product_list = stg_load_products();
				if (product_list == NULL) {
					printf("Nenhum produto cadastrado\n");
					timeout(TIMEOUT);
					break;
				}

				showProducts(product_list);

				timeout(TIMEOUT);
				free_products(product_list);
				system("pause");
				break;
			case SEARCH_PRODUCT:
				printf("Digite o produto que deseja buscar:\n");
				get_input(name, sizeof(name));
				if (is_blank(name)) {
					printf("Voc� deve informar algo para buscar\n");
					timeout(TIMEOUT);
					break;
				}

				product_list = stg_find_products_by_regex(name);
				if (product_list == NULL) {
					printf("Nenhum produto encontrado\n");
					timeout(TIMEOUT);
					break;
				}

				showProducts(product_list);

				timeout(TIMEOUT);
				free_products(product_list);
				system("pause");
				break;
			default:
				printf("Op��o inv�lida\n");
				timeout(TIMEOUT);
		}

		showMenu();
		scanf("%d", &option);
		fflush(stdin);
	}
	return 0;
}