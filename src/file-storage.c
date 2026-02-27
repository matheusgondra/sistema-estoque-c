#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "storage.h"
#include "utils.h"
#include "product.h"

bool stg_save_product(Product *product)
{
	FILE *file = fopen("products.csv", "a+");
	if (file == NULL)
	{
		return false;
	}

	fprintf(file, "%d,%s,%s,%s,%.2f\n", product->id, product->name, product->unit, product->address, 0.0);
	fclose(file);
	return true;
}

bool stg_load_products(ProductList *list) 
{
	FILE *file = fopen("products.csv", "r");
	if (file == NULL) {
		fprintf(stderr, "Failed to open products.csv");
		return false;
	}

	char line[256];
	bool result = false;

	while (fgets(line, sizeof(line), file)) {
		Product *product = (Product *) malloc(sizeof(Product));
		if (product == NULL) {
			fprintf(stderr, "Failed to alloc product. Error code: %d, Message: %s", errno, strerror(errno));
			fclose(file);
			return false;
		}

		sscanf(
			line, 
			"%d,%49[^,],%49[^,],%49[^,],%f\n", 
			&product->id, 
			product->name, 
			product->unit, 
			product->address, 
			&product->quantity
		);

		result = add_product_to_list(list, product);
		if (!result) {
			fprintf(stderr, "Failed to add product in ProductList");
			free(product);
			fclose(file);
			return false;
		}
	}

	fclose(file);
	return true;
}

bool stg_find_product(Product *product, int id)
{
	ProductList list = {0};
	create_product_list(&list);
	bool result = stg_load_products(&list);
	if (!result)
	{
		return false;
	}

	for (size_t i = 0; i < list.size; i++)
	{
		if (list.items[i].id == id)
		{
			create_product_with_id(product, list.items[i].id, list.items[i].name, list.items[i].unit, list.items[i].address);
			product->quantity = list.items[i].quantity;

			return true;
		}
	}

	free_product_list(&list);
	return false;
}

bool stg_find_product_by_name(Product *product, const char *name)
{
	ProductList list = {0};
	create_product_list(&list);
	bool result = stg_load_products(&list);
	if (!result)
	{
		return false;
	}

	for (size_t i = 0; i < list.size; i++)
	{
		if (strcmp(list.items[i].name, name) == 0)
		{
			product->id = list.items[i].id;
			create_product(product, list.items[i].name, list.items[i].unit, list.items[i].address);
			product->quantity = list.items[i].quantity;

			free_product_list(&list);
			return true;
		}
	}

	free_product_list(&list);
	return false;
}

bool stg_update_product_quantity(Product *product)
{
	FILE *file = fopen("products.csv", "r");
	if (file == NULL)
	{
		return false;
	}

	FILE *temp = fopen("temp.csv", "w");
	if (temp == NULL)
	{
		fclose(file);
		return false;
	}

	char line[256];
	int current_id;
	bool found = false;

	while (fgets(line, sizeof(line), file))
	{
		if (sscanf(line, "%d,", &current_id) != 1) {
			fputs(line, temp);
			continue;
		}

		if (current_id == product->id)
		{
			fprintf(temp, "%d,%s,%s,%s,%.2f\n", product->id, product->name, product->unit, product->address, product->quantity);
			found = true;
		}
		else
		{
			fputs(line, temp);
		}
	}

	fclose(file);
	fclose(temp);

	if (found)
	{
		remove("products.csv");
		rename("temp.csv", "products.csv");
	}
	else
	{
		remove("temp.csv");
	}

	return found;
}

bool stg_find_products_by_regex(ProductList *list, const char *regex)
{
	bool result = stg_load_products(list);
	if (!result)
	{
		return false;
	}

	ProductList filtered_list = {0};
	create_product_list(&filtered_list);
	char id[100];
	char *name, *unit, *address, *regex_lower;

	for (size_t i = 0; i < list->size; i++)
	{
		Product *product = &list->items[i];

		name = to_lower(product->name);
		unit = to_lower(product->unit);
		address = to_lower(product->address);
		regex_lower = to_lower(regex);
		sprintf(id, "%d", product->id);


		bool name_matched = strstr(name, regex_lower) != NULL;
		bool unit_matched = strstr(unit, regex_lower) != NULL;
		bool address_matched = strstr(address, regex_lower) != NULL;
		bool id_matched = strstr(id, regex_lower) != NULL;

		bool matched = name_matched || unit_matched || address_matched || id_matched;

		if (matched)
		{
			add_product_to_list(&filtered_list, product);
		}
	}
	
	*list = filtered_list;

	return true;
}