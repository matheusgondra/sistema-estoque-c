#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "product.h"

Product* create_product(int id, char *name, char *unit, char *address) {
	Product *product = (Product*) malloc(sizeof(Product));
	if (product == NULL) {
		printf("Erro ao criar produto\n");
		return NULL;
	}

	product->id = id;
	strcpy(product->name, name);
	strcpy(product->unit, unit);
	strcpy(product->address, address);

	return product;
}