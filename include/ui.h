#ifndef UI_H
#define UI_H

#include "product.h"

void showMenu();
void showProducts(const ProductList *list);
void showProduct(const Product *product);
void showError(const char *message);
void pause_ui();

#endif