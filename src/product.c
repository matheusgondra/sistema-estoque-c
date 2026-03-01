#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "product.h"
#include "utils.h"

void create_product(Product *product, char *name, char *unit, char *address)
{
	product->id = 0;
	strcpy(product->name, name);
	strcpy(product->unit, unit);
	strcpy(product->address, address);
	product->quantity = 0;
}

void create_product_with_id(Product *product, int id, char *name, char *unit, char *address)
{
	product->id = id;
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

void create_product_list(ProductList *list) {
	const int initial_capacity = 20;
	list->items = (Product *) malloc(initial_capacity * sizeof(Product));
	if (list->items == NULL) {
		fprintf(stderr, "Failed to allocate memory for product list.\n");
		exit(EXIT_FAILURE);
	}

	list->size = 0;
	list->capacity = initial_capacity;
}

void free_product_list(ProductList *list) {
	if (list != NULL) {
		if (list->items != NULL) {
			free(list->items);
		}
	}

	list->size = 0;
	list->capacity = 0;
}

bool add_product_to_list(ProductList *list, Product *product) {
	if (list->size >= list->capacity) {
		size_t new_capacity = list->capacity * 2;
		Product *new_items = (Product *) realloc(list->items, new_capacity * sizeof(Product));
		if (new_items == NULL) {
			fprintf(stderr, "Failed to reallocate memory for product list.\n");
			return false;
		}

		list->items = new_items;
		list->capacity = new_capacity;
	}

	list->items[list->size++] = *product;
	return true;
}