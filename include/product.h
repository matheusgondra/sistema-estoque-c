#ifndef PRODUCT_H
#define PRODUCT_H

#include <stddef.h>
#include <stdint.h>

typedef struct product
{
	uint64_t id;
	char name[101];
	char unit[11];
	char address[51];
	float quantity;
} Product;

typedef struct product_list 
{
	Product *items;
	size_t size;
	size_t capacity;
} ProductList;

void create_product(Product *product, char *name, char *unit, char *address);
void create_product_with_id(Product *product, uint64_t id, char *name, char *unit, char *address);
bool check_product(Product *product);
bool put_product_quantity(Product *product, float quantity);

void create_product_list(ProductList *list);
void free_product_list(ProductList *list);
bool add_product_to_list(ProductList *list, Product *product);

#endif