#ifndef PRODUCT_H
#define PRODUCT_H

#include <stdbool.h>
#include "utils.h"

typedef struct product
{
	int id;
	char name[100];
	char unit[10];
	char address[50];
	float quantity;
} Product;

typedef struct product_list 
{
	Product *items;
	size_t size;
	size_t capacity;
} ProductList;

void create_product(Product *product, char *name, char *unit, char *address);
void create_product_with_id(Product *product, int id, char *name, char *unit, char *address);
bool check_product(Product *product);
void free_product(Product *product);
void free_products(Product **products);
bool put_product_quantity(Product *product, float quantity);
bool products_is_empty(Product **products);
void create_product_list(ProductList *list);
void free_product_list(ProductList *list);

#endif