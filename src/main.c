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

void register_product();
void load_products();
void search_product();
void product_entry();
void product_exit();

int main()
{
	config_output();

	int option = -1;

	showMenu();
	scanf("%d", &option);
	clear_input_buffer();

	while (option != 0)
	{
		switch (option)
		{
		case REGISTER_PRODUCT:
			register_product();
			break;
		case PRODUCT_ENTRY:
			product_entry();
			break;
		case PRODUCT_EXIT:
			product_exit();
			break;
		case LOAD_PRODUCTS:
			load_products();
			break;
		case SEARCH_PRODUCT:
			search_product();
			break;
		default:
			showError("Opção inválida");
			timeout(TIMEOUT);
		}

		showMenu();
		option = -1;
		scanf("%d", &option);
		clear_input_buffer();
	}
	return 0;
}

void register_product()
{
	Product product;
	bool result = false;
	char name[256], unit[10], address[50];

	printf("Digite o nome do produto \n");
	get_input(name, sizeof(name));
	if (is_blank(name))
	{
		showError("Nome do produto não pode ser vazio");
		timeout(TIMEOUT);
		return;
	}

	printf("Digite a unidade do produto. Ex: m (metro), un (unidade) \n");
	get_input(unit, sizeof(unit));
	if (is_blank(unit))
	{
		showError("Unidade do produto não pode ser vazia");
		timeout(TIMEOUT);
		return;
	}

	printf("Digite o endereço onde será armazenado o produto: \n");
	get_input(address, sizeof(address));
	if (is_blank(address))
	{
		showError("Endereço do produto não pode ser vazio");
		timeout(TIMEOUT);
		return;
	}

	create_product(&product, name, unit, address);
	if (!check_product(&product))
	{
		showError("Erro ao cadastrar produto");
		return;
	}

	result = stg_find_product_by_name(&product, product.name);
	if (result)
	{
		printf("Produto já cadastrado\n");
		timeout(TIMEOUT);
		return;
	}

	result = stg_save_product(&product);
	if (!result)
	{
		showError("Erro ao salvar produto");
		return;
	}

	printf("Produto cadastrado com sucesso\n");
	showProduct(&product);
	system("pause");
}

void product_entry()
{
	Product product;
	bool result = false;
	int id = -1;
	float qtd = -1;

	printf("Digite o id do produto:\n");
	scanf("%d", &id);
	clear_input_buffer();

	result = stg_find_product(&product, id);
	if (!result)
	{
		showError("Produto não encontrado");
		timeout(TIMEOUT);
		return;
	}

	printf("Digite a quantidade de entrada do produto:\n");
	scanf("%f", &qtd);
	clear_input_buffer();

	printf("Quantidade: %.2f\n", qtd);
	timeout(TIMEOUT);

	if (qtd <= 0.00)
	{
		showError("Quantidade inválida");
		timeout(TIMEOUT);
		return;
	}

	result = put_product_quantity(&product, qtd);
	if (!result)
	{
		showError("Erro ao dar entrada no produto");
		timeout(TIMEOUT);
		return;
	}

	result = stg_update_product_quantity(&product);
	if (!result)
	{
		showError("Erro ao atualizar quantidade do produto");
		timeout(TIMEOUT);
		return;
	}

	showProduct(&product);
	printf("Entrada de produto realizada com sucesso\n");

	free_product(&product);
	timeout(TIMEOUT);
	system("pause");
}

void product_exit()
{
	Product product;
	bool result = false;
	int id = -1;
	float qtd = -1;

	printf("Digite o id do produto:\n");
	scanf("%d", &id);
	clear_input_buffer();

	result = stg_find_product(&product, id);
	if (!result)
	{
		showError("Produto não encontrado");
		timeout(TIMEOUT);
		return;
	}

	printf("Digite a quantidade de saída do produto (use ponto em vez de vírgula em números com casas decimais):\n");
	scanf("%f", &qtd);
	clear_input_buffer();

	if (product.quantity < qtd)
	{
		showError("Quantidade insuficiente no estoque");
		timeout(TIMEOUT);
		return;
	}

	product.quantity -= qtd;
	result = stg_update_product_quantity(&product);
	if (!result)
	{
		showError("Erro ao atualizar quantidade do produto");
		timeout(TIMEOUT);
		return;
	}

	showProduct(&product);
	printf("Saída de produto realizada com sucesso\n");

	timeout(TIMEOUT);
	system("pause");
}

void load_products()
{
	Product **product_list = stg_load_products();
	if (product_list == NULL || products_is_empty(product_list))
	{
		showError("Nenhum produto cadastrado");
		timeout(TIMEOUT);
		free_products(product_list);
		return;
	}

	showProducts(product_list);

	timeout(TIMEOUT);
	free_products(product_list);
	system("pause");
}

void search_product()
{
	char name[256];
	Product **product_list = NULL;

	printf("Digite o produto que deseja buscar:\n");
	get_input(name, sizeof(name));
	if (is_blank(name))
	{
		showError("Você deve informar algo para buscar");
		timeout(TIMEOUT);
		return;
	}

	product_list = stg_find_products_by_regex(name);
	if (product_list == NULL || products_is_empty(product_list))
	{
		showError("Nenhum produto encontrado");
		timeout(TIMEOUT);
		free_products(product_list);
		return;
	}

	showProducts(product_list);

	timeout(TIMEOUT);
	free_products(product_list);
	system("pause");
}