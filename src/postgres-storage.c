#include "storage.h"
#include "utils.h"
#include <libpq-fe.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef enum pq_result_type { TEXT, BINARY } PGResultType;

static const char *get_connect_url() {
  char *url = getenv("DATABASE_URL");
  if (url == nullptr) {
    url = "postgres://dev:dev@localhost:5432/sistema_estoque_c";
  }

  return url;
}

static bool check_connection(PGconn *conn) {
  if (PQstatus(conn) != CONNECTION_OK) {
    fprintf(stderr, "Erro ao conectar ao banco de dados: %s\n",
            PQerrorMessage(conn));
    return false;
  }
  return true;
}

static void finish_query(PGresult *result, PGconn *conn) {
  PQclear(result);
  PQfinish(conn);
}

static bool regex_match(const char *string, const char *pattern) {
  bool match = false;

  if (strstr(string, pattern) != nullptr) {
    match = true;
  }

  return match;
}

bool stg_init() {
  PGconn *conn = PQconnectdb(get_connect_url());
  if (!check_connection(conn)) {
    PQfinish(conn);
    return false;
  }

  const char *create_table_sql =
      "CREATE TABLE IF NOT EXISTS products ( "
      "id SERIAL PRIMARY KEY,"
      "name VARCHAR(255) NOT NULL, "
      "unit VARCHAR(50) NOT NULL, "
      "address VARCHAR(255) NOT NULL, "
      "quantity DECIMAL(10, 2) NOT NULL, "
      "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP "
      ");";
  PGresult *result = PQexec(conn, create_table_sql);
  if (PQresultStatus(result) != PGRES_COMMAND_OK) {
    fprintf(stderr, "Erro ao criar tabela: %s\n", PQerrorMessage(conn));
    finish_query(result, conn);
    return false;
  }

  return true;
}

bool stg_save_product(Product *product) {
  PGconn *conn = PQconnectdb(get_connect_url());
  if (!check_connection(conn)) {
    PQfinish(conn);
    return false;
  }

  const char *query = "INSERT INTO products (name, unit, address, quantity) "
                      "VALUES ($1, $2, $3, $4) RETURNING id";

  char quantity_str[50];
  float_to_str(product->quantity, quantity_str, sizeof(quantity_str));

  const char *paramValues[4] = {product->name, product->unit, product->address,
                                quantity_str};

  PGresult *resultQuery =
      PQexecParams(conn, query, 4, nullptr, paramValues, nullptr, nullptr, TEXT);
  if (PQresultStatus(resultQuery) != PGRES_TUPLES_OK) {
    printf("Falha na query\n %s", PQerrorMessage(conn));
    printf("Detalhes: %s\n", PQresultErrorMessage(resultQuery));

    finish_query(resultQuery, conn);
    return false;
  }

  char *id_str = PQgetvalue(resultQuery, 0, 0);
  product->id = atoi(id_str);

  PQclear(resultQuery);
  PQfinish(conn);

  return true;
}

bool stg_load_products(ProductList *list) {
  PGconn *conn = PQconnectdb(get_connect_url());
  if (!check_connection(conn)) {
    PQfinish(conn);
    return false;
  }

  const char *query = "SELECT id, name, unit, address, quantity FROM products";
  PGresult *result = PQexec(conn, query);
  if (PQresultStatus(result) != PGRES_TUPLES_OK) {
    fprintf(stderr, "Erro ao carregar produtos: %s\n", PQerrorMessage(conn));
    finish_query(result, conn);
    return false;
  }

  int lines = PQntuples(result);
  for (int i = 0; i < lines; i++) {
    int id = atoi(PQgetvalue(result, i, 0));
    char *name = PQgetvalue(result, i, 1);
    char *unit = PQgetvalue(result, i, 2);
    char *address = PQgetvalue(result, i, 3);
    float quantity = atof(PQgetvalue(result, i, 4));

    Product product;
    create_product_with_id(&product, id, name, unit, address);
    product.quantity = quantity;

    add_product_to_list(list, &product);
  }

  finish_query(result, conn);
  return true;
}

bool stg_find_product(Product *product, uint64_t id) {
  PGconn *conn = PQconnectdb(get_connect_url());
  if (!check_connection(conn)) {
    PQfinish(conn);
    return false;
  }

  char id_str[20] = {};
  int_to_str(id, id_str, sizeof(id_str));

  const char *query =
      "SELECT id, name, unit, address, quantity FROM products WHERE id = $1";
  const char *paramValues[1] = {id_str};

  PGresult *result =
      PQexecParams(conn, query, 1, nullptr, paramValues, nullptr, nullptr, TEXT);
  if (PQresultStatus(result) != PGRES_TUPLES_OK) {
    fprintf(stderr, "Erro ao buscar produto: %s\n", PQerrorMessage(conn));
    finish_query(result, conn);
    return false;
  }

  int n = PQntuples(result);
  if (n == 0) {
    printf("Produto não encontrado\n");
    finish_query(result, conn);
    return false;
  }

  product->id = atoi(PQgetvalue(result, 0, 0));
  strcpy(product->name, PQgetvalue(result, 0, 1));
  strcpy(product->unit, PQgetvalue(result, 0, 2));
  strcpy(product->address, PQgetvalue(result, 0, 3));
  product->quantity = atof(PQgetvalue(result, 0, 4));

  finish_query(result, conn);
  return true;
}

bool stg_update_product_quantity(Product *product) {
  PGconn *conn = PQconnectdb(get_connect_url());
  if (!check_connection(conn)) {
    PQfinish(conn);
    return false;
  }

  char id_str[20] = {};
  int_to_str(product->id, id_str, sizeof(id_str));

  char quantity_str[50];
  float_to_str(product->quantity, quantity_str, sizeof(quantity_str));

  const char *query = "UPDATE products SET quantity = $1 WHERE id = $2";
  const char *paramValues[2] = {quantity_str, id_str};

  PGresult *result =
      PQexecParams(conn, query, 2, nullptr, paramValues, nullptr, nullptr, TEXT);
  if (PQresultStatus(result) != PGRES_COMMAND_OK) {
    fprintf(stderr, "Erro ao atualizar produto: %s\n", PQerrorMessage(conn));
    finish_query(result, conn);
    return false;
  }

  finish_query(result, conn);
  return true;
}

bool stg_find_products_by_regex(ProductList *list, const char *regex) {
  stg_load_products(list);

  ProductList filtered_list = {0};
  create_product_list(&filtered_list);

  char id_str[12];
  char quantity_str[50];
  char *regex_normalized = to_lower(regex);
  bool match = false;

  for (size_t i = 0; i < list->size; i++) {
    Product *product = &list->items[i];

    int_to_str(product->id, id_str, sizeof(id_str));
    float_to_str(product->quantity, quantity_str, sizeof(quantity_str));

    char *name_normalized = to_lower(product->name);

    bool name_match = regex_match(name_normalized, regex_normalized);
    bool unit_match = regex_match(product->unit, regex_normalized);
    bool address_match = regex_match(product->address, regex_normalized);
    bool id_match = regex_match(id_str, regex_normalized);
    bool quantity_match = regex_match(quantity_str, regex_normalized);

    match =
        name_match || unit_match || address_match || id_match || quantity_match;

    if (match) {
      add_product_to_list(&filtered_list, product);
    }
  }

  free_product_list(list);

  *list = filtered_list;
  return match;
}

bool stg_find_product_by_name(Product *product, const char *name) {
  ProductList list = {0};
  create_product_list(&list);

  stg_load_products(&list);

  for (size_t i = 0; i < list.size; i++) {
    Product *current_product = &list.items[i];
    if (strcmp(current_product->name, name) == 0) {
      *product = *current_product;
      free_product_list(&list);
      return true;
    }
  }

  free_product_list(&list);
  return false;
}