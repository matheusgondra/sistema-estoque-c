#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "utils.h"
#include "product.h"
#include "storage.h"
#include "ui.h"

#define TIMEOUT SECOND * 2

typedef enum menu_option {
	REGISTER_PRODUCT = 1,
	LOAD_PRODUCTS,
	SEARCH_PRODUCT,
	PRODUCT_ENTRY,
	PRODUCT_EXIT
} MenuOption;

void register_product();
void load_products();
void search_product();
void product_entry();
void product_exit();
void say_bye();

void handle_signal(int);

int main()
{
	int atexit_result = atexit(say_bye);
	if (atexit_result != 0) {
		fprintf(stderr, "Erro ao registrar função de saída\n");
		return EXIT_FAILURE;
	}

	signal(SIGINT, handle_signal);
	signal(SIGTERM, handle_signal);

	config_output();
	bool result = stg_init();
	if (!result) {
		return EXIT_FAILURE;
	}

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
		case LOAD_PRODUCTS:
			load_products();
			break;
		case SEARCH_PRODUCT:
			search_product();
			break;
		case PRODUCT_ENTRY:
			product_entry();
			break;
		case PRODUCT_EXIT:
			product_exit();
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
	
	return EXIT_SUCCESS;
}

void say_bye() 
{
	printf("\nBye!\n");
}

void handle_signal(int signal) 
{
	if (signal == SIGINT || signal == SIGTERM) {
		exit(EXIT_SUCCESS);
	}
}

void register_product()
{
	Product product = {0};
	bool result = false;
	char name[256], unit[10], address[50];

	printf("Digite o nome do produto: ");
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
		timeout(TIMEOUT);
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
		timeout(TIMEOUT);
		return;
	}

	printf("Produto cadastrado com sucesso\n");
	showProduct(&product);
	pause_ui();
}

void product_entry()
{
	Product product = {0};
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

	showProduct(&product);

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

	timeout(TIMEOUT);
	pause_ui();
}

void product_exit()
{
	Product product = {0};
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
	pause_ui();
}

void load_products()
{
	ProductList list = {0};
	create_product_list(&list);

	bool result = stg_load_products(&list);
	if (!result)
	{
		showError("Nenhum produto cadastrado");
		timeout(TIMEOUT);
		free_product_list(&list);
		return;
	}

	showProducts(&list);

	timeout(TIMEOUT);
	free_product_list(&list);
	pause_ui();
}

void search_product()
{
	char name[256];
	ProductList product_list = {0};
	create_product_list(&product_list);

	printf("Digite o produto que deseja buscar:\n");
	get_input(name, sizeof(name));
	if (is_blank(name))
	{
		showError("Você deve informar algo para buscar");
		timeout(TIMEOUT);
		return;
	}

	bool result = stg_find_products_by_regex(&product_list, name);
	if (!result)
	{
		showError("Erro ao buscar produtos");
		timeout(TIMEOUT);
		free_product_list(&product_list);
		return;
	}

	if (product_list.size == 0)
	{
		showError("Nenhum produto encontrado");
		timeout(TIMEOUT);
		free_product_list(&product_list);
		return;
	}

	showProducts(&product_list);

	timeout(TIMEOUT);
	free_product_list(&product_list);
	pause_ui();
}