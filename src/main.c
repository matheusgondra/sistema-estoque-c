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
	fflush(stdin);

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
			showError("Op��o inv�lida");
			timeout(TIMEOUT);
		}

		showMenu();
		option = -1;
		scanf("%d", &option);
		fflush(stdin);
	}
	return 0;
}

void register_product()
{
	char name[256], unit[10], address[50];
	Product *product = NULL;

	printf("Digite o nome do produto \n");
	get_input(name, sizeof(name));
	if (is_blank(name))
	{
		showError("Nome do produto n�o pode ser vazio");
		timeout(TIMEOUT);
		return;
	}

	printf("Digite a unidade do produto. Ex: m (metro), un (unidade) \n");
	get_input(unit, sizeof(unit));
	if (is_blank(unit))
	{
		showError("Unidade do produto n�o pode ser vazia");
		timeout(TIMEOUT);
		return;
	}

	printf("Digite o endere�o onde ser� armazenado o produto: \n");
	get_input(address, sizeof(address));
	if (is_blank(address))
	{
		showError("Endere�o do produto n�o pode ser vazio");
		timeout(TIMEOUT);
		return;
	}

	product = create_product(name, unit, address);
	if (product == NULL)
	{
		showError("Erro ao cadastrar produto");
		exit(EXIT_FAILURE);
	}

	Product *product_created = stg_find_product_by_name(product->name);
	if (product_created != NULL)
	{
		printf("Produto j� cadastrado\n");
		free_product(product_created);
		timeout(TIMEOUT);
		return;
	}

	int result = stg_save_product(product);
	if (!result)
	{
		showError("Erro ao salvar produto");
		exit(EXIT_FAILURE);
	}

	printf("Produto cadastrado com sucesso\n");
	showProduct(product);
	system("pause");
	free_product(product);
}

void product_entry()
{
	Product *product = NULL;
	bool result = false;
	int id = -1;
	float qtd = -1;

	printf("Digite o id do produto:\n");
	scanf("%d", &id);
	fflush(stdin);

	product = stg_find_product(id);
	if (product == NULL)
	{
		showError("Produto n�o encontrado");
		timeout(TIMEOUT);
		return;
	}

	printf("Digite a quantidade de entrada do produto:\n");
	scanf("%f", &qtd);
	fflush(stdin);

	printf("Quantidade: %.2f\n", qtd);
	timeout(TIMEOUT);

	if (qtd <= 0.00)
	{
		showError("Quantidade inv�lida");
		free_product(product);
		timeout(TIMEOUT);
		return;
	}

	result = put_product_quantity(product, qtd);
	if (!result)
	{
		showError("Erro ao dar entrada no produto");
		free_product(product);
		timeout(TIMEOUT);
		return;
	}

	result = stg_update_product_quantity(product);
	if (!result)
	{
		showError("Erro ao atualizar quantidade do produto");
		free_product(product);
		timeout(TIMEOUT);
		return;
	}

	showProduct(product);
	printf("Entrada de produto realizada com sucesso\n");

	free_product(product);
	timeout(TIMEOUT);
	system("pause");
}

void product_exit()
{
	Product *product = NULL;
	bool result = false;
	int id = -1;
	float qtd = -1;

	printf("Digite o id do produto:\n");
	scanf("%d", &id);
	fflush(stdin);

	product = stg_find_product(id);
	if (product == NULL)
	{
		showError("Produto n�o encontrado");
		timeout(TIMEOUT);
		return;
	}

	printf("Digite a quantidade de sa�da do produto (use ponto em vez de v�rgula em n�meros com casas decimais):\n");
	scanf("%f", &qtd);
	fflush(stdin);

	if (product->quantity < qtd)
	{
		showError("Quantidade insuficiente no estoque");
		free_product(product);
		timeout(TIMEOUT);
		return;
	}

	product->quantity -= qtd;
	result = stg_update_product_quantity(product);
	if (!result)
	{
		showError("Erro ao atualizar quantidade do produto");
		free_product(product);
		timeout(TIMEOUT);
		return;
	}

	showProduct(product);
	printf("Sa�da de produto realizada com sucesso\n");

	free_product(product);
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
		showError("Voc� deve informar algo para buscar");
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