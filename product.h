#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct product {
	int id;
	char name[100];
	char unit[10];
	char address[50];
} Product;

Product* create_product(int id, char *name, char *unit, char *address);

#endif