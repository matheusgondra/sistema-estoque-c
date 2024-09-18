#include <stdio.h>
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