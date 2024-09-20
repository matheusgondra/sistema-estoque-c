#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct product {
	int id;
	char name[100];
	char unit[10];
	char address[50];
	int quantity;
} Product;

Product* create_product(char *name, char *unit, char *address);
void free_product(Product *product);
void free_products(Product **products);

int put_product_quantity(Product *product, int quantity);

#endif