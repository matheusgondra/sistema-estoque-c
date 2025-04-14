#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "product.h"
#include "utils.h"

int get_id()
{
	FILE *file;
	int id = 1;

	file = fopen("id.txt", "a+");
	if (file == NULL)
	{
		perror("Erro ao abrir o arquivo");
		exit(EXIT_FAILURE);
	}

	if (fscanf(file, "%d", &id) == 1)
	{
		id++;
	}
	fclose(file);

	file = fopen("id.txt", "w");
	if (file == NULL)
	{
		perror("Erro ao abrir o arquivo");
		exit(EXIT_FAILURE);
	}

	fprintf(file, "%d", id);
	fclose(file);

	return id;
}

void create_product(Product *product, char *name, char *unit, char *address)
{
	product->id = get_id();
	strcpy(product->name, name);
	strcpy(product->unit, unit);
	strcpy(product->address, address);
	product->quantity = 0;
}

bool check_product(Product *product)
{
	if (product == NULL)
	{
		return false;
	}

	bool is_valid_name = strlen(product->name) > 0;
	bool is_valid_unit = strlen(product->unit) > 0;
	bool is_valid_address = strlen(product->address) > 0;

	bool is_valid_product = is_valid_name && is_valid_unit && is_valid_address;

	return is_valid_product;
}

void free_product(Product *product)
{
	free(product);
}

void free_products(Product **products)
{
	if (products == NULL)
	{
		return;
	}

	for (int i = 0; products[i] != NULL; i++)
	{
		free(products[i]);
	}
	free(products);
}

bool products_is_empty(Product **products)
{
	return products[0] == NULL;
}

bool put_product_quantity(Product *product, float quantity)
{
	if (quantity <= 0)
	{
		printf("Quantidade inválida\n");
		return false;
	}

	product->quantity += quantity;

	return true;
}