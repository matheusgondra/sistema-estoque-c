#ifndef UI_H
#define UI_H

#include "product.h"

void showMenu();
void showProducts(Product **products);
void showProduct(Product *product);
void showError(char *message);

#endif