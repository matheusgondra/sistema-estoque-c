#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
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

Product **stg_load_products(int *count)
{
	FILE *file = fopen("products.csv", "r");
	if (file == NULL)
	{
		return NULL;
	}

	Product **products = (Product **)malloc(sizeof(Product *));
	*count = 0;
	char line[256];

	while (fgets(line, sizeof(line), file))
	{
		Product *product = (Product *)malloc(sizeof(Product));
		sscanf(line, "%d,%[^,],%[^,],%[^,],%f\n", &product->id, product->name, product->unit, product->address, &product->quantity);
		products = (Product **)realloc(products, sizeof(Product *) * (*count + 1));
		products[*count] = product;
		(*count)++;
	}

	products = (Product **)realloc(products, sizeof(Product *) * (*count + 1));
	products[*count] = NULL;

	fclose(file);
	return products;
}

bool stg_find_product(Product *product, int id)
{
	int count = 0;
	Product **products = stg_load_products(&count);

	for (int i = 0; i < count; i++)
	{
		if (products[i]->id == id)
		{
			product->id = products[i]->id;
			create_product(product, products[i]->name, products[i]->unit, products[i]->address);
			product->quantity = products[i]->quantity;
			free(products[i]);

			return true;
		}
	}

	free(products);
	return false;
}

bool stg_find_product_by_name(Product *product, const char *name)
{
	int count = 0;
	Product **products = stg_load_products(&count);
	if (products == NULL)
	{
		return false;
	}

	for (int i = 0; i < count; i++)
	{
		if (strcmp(products[i]->name, name) == 0)
		{
			product->id = products[i]->id;
			create_product(product, products[i]->name, products[i]->unit, products[i]->address);
			product->quantity = products[i]->quantity;

			free(products[i]);
			return true;
		}
	}

	free_products(products);
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

Product **stg_find_products_by_regex(char *regex, int *count)
{
	*count = 0;
	Product **products = stg_load_products(count);
	if (products == NULL)
	{
		return NULL;
	}

	Product **filtered = (Product **)malloc(sizeof(Product *));
	int filtered_count = 0;
	char id[100];
	char *name, *unit, *address;

	for (int i = 0; i < *count; i++)
	{
		name = to_lower(products[i]->name);
		unit = to_lower(products[i]->unit);
		address = to_lower(products[i]->address);
		regex = to_lower(regex);

		if (strstr(name, regex) != NULL)
		{
			filtered = (Product **)realloc(filtered, sizeof(Product *) * (filtered_count + 1));
			filtered[filtered_count] = products[i];
			filtered_count++;
			continue;
		}

		if (strstr(unit, regex) != NULL)
		{
			filtered = (Product **)realloc(filtered, sizeof(Product *) * (filtered_count + 1));
			filtered[filtered_count] = products[i];
			filtered_count++;
			continue;
		}

		if (strstr(address, regex) != NULL)
		{
			filtered = (Product **)realloc(filtered, sizeof(Product *) * (filtered_count + 1));
			filtered[filtered_count] = products[i];
			filtered_count++;
			continue;
		}

		sprintf(id, "%d", products[i]->id);
		if (strstr(id, regex) != NULL)
		{
			filtered = (Product **)realloc(filtered, sizeof(Product *) * (filtered_count + 1));
			filtered[filtered_count] = products[i];
			filtered_count++;
			continue;
		}
	}

	filtered = (Product **)realloc(filtered, sizeof(Product *) * (filtered_count + 1));
	filtered[filtered_count] = NULL;

	return filtered;
}