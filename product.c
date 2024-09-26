#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "product.h"
#include "utils.h"

int get_id() {
	FILE *file;
	int id = 1; 

	file = fopen("id.txt", "a+");
	if (file == NULL) {
		perror("Erro ao abrir o arquivo");
		exit(EXIT_FAILURE);
	}

	if (fscanf(file, "%d", &id) == 1) {
		id++;
	}
	fclose(file);

	file = fopen("id.txt", "w");
	if (file == NULL) {
		perror("Erro ao abrir o arquivo");
		exit(EXIT_FAILURE);
	}

	fprintf(file, "%d", id);
	fclose(file);

	return id;
}

Product* create_product(char *name, char *unit, char *address) {
	Product *product = (Product*) malloc(sizeof(Product));
	if (product == NULL) {
		printf("Erro ao criar produto\n");
		return NULL;
	}

	product->id = get_id();
	strcpy(product->name, name);
	strcpy(product->unit, unit);
	strcpy(product->address, address);
	product->quantity = 0;

	return product;
}

void free_product(Product *product) {
	free(product);
}

void free_products(Product **products) {
	for (int i = 0; products[i] != NULL; i++) {
		free(products[i]);
	}
	free(products);
}

BOOL put_product_quantity(Product *product, float quantity) {
	if (quantity <= 0) {
		printf("Quantidade inv lida\n");
		return FALSE;
	}

	product->quantity += quantity;

	return TRUE;
}