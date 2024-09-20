#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "storage.h"

int stg_save_product(Product *product) {
	FILE *file = fopen("products.csv", "a+");
	if (file == NULL) {
		return 0;
	}

	fprintf(file, "%d,%s,%s,%s,%d\n", product->id, product->name, product->unit, product->address, 0);
	fclose(file);
	return 1;
}

Product **stg_load_products() {
	FILE *file = fopen("products.csv", "r");
	if (file == NULL) {
		return NULL;
	}

	Product **products = (Product **) malloc(sizeof(Product *));
	int count = 0;
	char line[256];
	
	while (fgets(line, sizeof(line), file)) {
		Product *product = (Product *)malloc(sizeof(Product));
		sscanf(line, "%d,%[^,],%[^,],%[^,],%d\n", &product->id, product->name, product->unit, product->address, &product->quantity);
		products = (Product **) realloc(products, sizeof(Product *) * (count + 1));
		products[count] = product;
		count++;
	}

	products = (Product **) realloc(products, sizeof(Product *) * (count + 1));
	products[count] = NULL;

	fclose(file);
	return products;
}

Product *stg_find_product(int id) {
	Product **product = stg_load_products();
	for (int i = 0; product[i] != NULL; i++) {
		if (product[i]->id == id) {
			return product[i];
		}
	}
	return NULL;
}