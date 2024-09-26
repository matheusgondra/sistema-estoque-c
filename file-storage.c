#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "storage.h"
#include "utils.h"

BOOL stg_save_product(Product *product) {
	FILE *file = fopen("products.csv", "a+");
	if (file == NULL) {
		return FALSE;
	}

	fprintf(file, "%d,%s,%s,%s,%.2f\n", product->id, product->name, product->unit, product->address, 0.0);
	fclose(file);
	return TRUE;
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
		sscanf(line, "%d,%[^,],%[^,],%[^,],%f\n", &product->id, product->name, product->unit, product->address, &product->quantity);
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

BOOL stg_update_product_quantity(Product *product) {
	FILE *file = fopen("products.csv", "r");
	if (file == NULL) {
		return FALSE;
	}

	FILE *temp = fopen("temp.csv", "w");
	if (temp == NULL) {
		fclose(file);
		return FALSE;
	}

	char line[256];
	int current_id;
	BOOL found = FALSE;

	while (fgets(line, sizeof(line), file)) {
		sscanf(line, "%d", &current_id);
		
		if (current_id == product->id) {
			fprintf(temp, "%d,%s,%s,%s,%.2f\n", product->id, product->name, product->unit, product->address, product->quantity);
			found = TRUE;
		} else {
			fputs(line, temp);
		}
	}

	fclose(file);
	fclose(temp);

	if (found) {
		remove("products.csv");
		rename("temp.csv", "products.csv");
	} else {
		remove("temp.csv");
	}

	return found;
}

Product **stg_find_products_by_regex(const char *regex) {
	Product **products = stg_load_products();
	if (products == NULL) {
		return NULL;
	}

	Product **filtered = (Product **) malloc(sizeof(Product *));
	int count = 0;
	char buffer[256], id[100];

	for (int i = 0; products[i] != NULL; i++) {
		if (strstr(products[i]->name, regex) != NULL) {
			filtered = (Product **) realloc(filtered, sizeof(Product *) * (count + 1));
			filtered[count] = products[i];
			count++;
			continue;
		}

		if (strstr(products[i]->unit, regex) != NULL) {
			filtered = (Product **) realloc(filtered, sizeof(Product *) * (count + 1));
			filtered[count] = products[i];
			count++;
			continue;
		}

		if (strstr(products[i]->address, regex) != NULL) {
			filtered = (Product **) realloc(filtered, sizeof(Product *) * (count + 1));
			filtered[count] = products[i];
			count++;
			continue;
		}

		sprintf(id, "%d", products[i]->id);
		if (strstr(id, regex) != NULL) {
			filtered = (Product **) realloc(filtered, sizeof(Product *) * (count + 1));
			filtered[count] = products[i];
			count++;
			continue;
		}
	}

	filtered = (Product **) realloc(filtered, sizeof(Product *) * (count + 1));
	filtered[count] = NULL;

	return filtered;
}