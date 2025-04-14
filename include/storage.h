#ifndef STORAGE_H
#define STORAGE_H

#include <stdbool.h>
#include "product.h"
#include "utils.h"

bool stg_save_product(Product *product);
Product **stg_load_products();
bool stg_find_product(Product *product, int id);
bool stg_update_product_quantity(Product *product);
Product **stg_find_products_by_regex(char *regex);
bool stg_find_product_by_name(Product *product, const char *name);

#endif