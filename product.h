#ifndef PRODUCT_H
#define PRODUCT_H

#include "utils.h"

typedef struct product {
	int id;
	char name[100];
	char unit[10];
	char address[50];
	float quantity;
} Product;

Product* create_product(char *name, char *unit, char *address);
void free_product(Product *product);
void free_products(Product **products);
BOOL put_product_quantity(Product *product, float quantity);
BOOL products_is_empty(Product **products);

#endif