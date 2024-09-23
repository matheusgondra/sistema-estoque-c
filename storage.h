#ifndef STORAGE_H
#define STORAGE_H

#include "product.h"
#include "utils.h"

BOOL stg_save_product(Product *product);
Product **stg_load_products();
Product *stg_find_product(int id);
BOOL stg_update_product_quantity(Product *product);
Product **stg_find_products_by_regex(const char *regex);

#endif