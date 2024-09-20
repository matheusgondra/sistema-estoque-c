#ifndef STORAGE_H
#define STORAGE_H

#include "product.h"

int stg_save_product(Product *product);
Product **stg_load_products();
Product *stg_find_product(int id);

#endif