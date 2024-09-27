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

	Product *product, **product_list, *product_created;
	int id = -1;
	float qtd = -1;
	char name[256], unit[10], address[50];

	while (option != 0) {
		switch (option) {
			case REGISTER_PRODUCT:
				printf("Digite o nome do produto \n");
				get_input(name, sizeof(name));
				if (is_blank(name)) {
					showError("Nome do produto n∆o pode ser vazio");
					timeout(TIMEOUT);
					break;
				}

				printf("Digite a unidade do produto. Ex: m (metro), un (unidade) \n");
				get_input(unit, sizeof(unit));
				if (is_blank(unit)) {
					showError("Unidade do produto n∆o pode ser vazia");
					timeout(TIMEOUT);
					break;
				}

				printf("Digite o endereáo onde ser† armazenado o produto: \n");
				get_input(address, sizeof(address));
				if (is_blank(address)) {
					showError("Endereáo do produto n∆o pode ser vazio");
					timeout(TIMEOUT);
					break;
				}

				product = create_product(name, unit, address);
				if (product == NULL) {
					showError("Erro ao cadastrar produto");
					exit(EXIT_FAILURE);
				}

				product_created = stg_find_product_by_name(product->name);
				if (product_created != NULL) {
					printf("Produto j† cadastrado\n");
					free_product(product_created);
					timeout(TIMEOUT);
					break;
				}

				int result = stg_save_product(product);
				if (!result) {
					showError("Erro ao salvar produto");
					exit(EXIT_FAILURE);
				}

				printf("Produto cadastrado com sucesso\n");
				showProduct(product);
				system("pause");
				free_product(product);
				break;
			case PRODUCT_ENTRY:
				printf("Digite o id do produto:\n");
				scanf("%d", &id);
				fflush(stdin);

				product = stg_find_product(id);
				if (product == NULL) {
					showError("Produto n∆o encontrado");
					timeout(TIMEOUT);
					break;
				}
				
				printf("Digite a quantidade de entrada do produto:\n");
				scanf("%f", &qtd);
				fflush(stdin);

				if (qtd <= 0.00) {
					showError("Quantidade inv†lida");
					free_product(product);
					timeout(TIMEOUT);
					break;
				}

				result = put_product_quantity(product, qtd);
				if (!result) {
					showError("Erro ao dar entrada no produto");
					free_product(product);
					timeout(TIMEOUT);
					break;
				}

				result = stg_update_product_quantity(product);
				if (!result) {
					showError("Erro ao atualizar quantidade do produto");
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
					showError("Produto n∆o encontrado");
					timeout(TIMEOUT);
					break;
				}

				printf("Digite a quantidade de sa°da do produto (use ponto em vez de v°rgula em n£meros com casas decimais):\n");
				scanf("%f", &qtd);
				fflush(stdin);

				if (product->quantity < qtd) {
					showError("Quantidade insuficiente no estoque");
					free_product(product);
					timeout(TIMEOUT);
					break;
				}

				product->quantity -= qtd;
				result = stg_update_product_quantity(product);
				if (!result) {
					showError("Erro ao atualizar quantidade do produto");
					free_product(product);
					timeout(TIMEOUT);
					break;
				}

				showProduct(product);
				printf("Sa°da de produto realizada com sucesso\n");

				free_product(product);
				timeout(TIMEOUT);
				system("pause");
				break;
			case LOAD_PRODUCTS:
				product_list = stg_load_products();
				if (product_list == NULL || products_is_empty(product_list)) {
					showError("Nenhum produto cadastrado");
					timeout(TIMEOUT);
					free_products(product_list);
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
					showError("Vocà deve informar algo para buscar");
					timeout(TIMEOUT);
					break;
				}

				product_list = stg_find_products_by_regex(name);
				if (product_list == NULL || products_is_empty(product_list)) {
					showError("Nenhum produto encontrado");
					timeout(TIMEOUT);
					free_products(product_list);
					break;
				}

				showProducts(product_list);

				timeout(TIMEOUT);
				free_products(product_list);
				system("pause");
				break;
			default:
				showError("Opá∆o inv†lida");
				timeout(TIMEOUT);
		}

		showMenu();
		option = -1;
		id = -1;
		qtd = -1;
		scanf("%d", &option);
		fflush(stdin);
	}
	return 0;
}