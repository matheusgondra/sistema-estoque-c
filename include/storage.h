#ifndef STORAGE_H
#define STORAGE_H

#include <stdbool.h>
#include "product.h"

bool stg_init();
bool stg_save_product(Product *product);
bool stg_load_products(ProductList *list);
bool stg_find_product(Product *product, int id);
bool stg_update_product_quantity(Product *product);
bool stg_find_products_by_regex(ProductList *list, const char *regex);
bool stg_find_product_by_name(Product *product, const char *name);

#endif