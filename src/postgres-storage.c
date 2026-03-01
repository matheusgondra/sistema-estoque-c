#include "storage.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <libpq-fe.h>

static const char *get_connect_url() {
    char *user = getenv("DB_USER");
    if (!user) {
        user = "dev";
    }
    
    char *password = getenv("DB_PASSWORD");
    if (!password) {
        password = "dev";
    }

    char *dbname = getenv("DB_NAME");
    if (!dbname) {
        dbname = "sistema_estoque_c";
    }

    char *host = getenv("DB_HOST");
    if (!host) {
        host = "localhost";
    }

    char *port = getenv("DB_PORT");
    if (!port) {
        port = "5432";
    }

    static char conninfo[256];
    strcpy(conninfo, "postgres://");
    strcat(conninfo, user);
    strcat(conninfo, ":");
    strcat(conninfo, password);
    strcat(conninfo, "@");
    strcat(conninfo, host);
    strcat(conninfo, ":");
    strcat(conninfo, port);
    strcat(conninfo, "/");
    strcat(conninfo, dbname);

    return conninfo;
}

static bool check_connection(PGconn *conn) {
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Erro ao conectar ao banco de dados: %s\n", PQerrorMessage(conn));
        return false;
    }
    return true;
}

static void finish_query(PGresult *result, PGconn *conn) {
    PQclear(result);
    PQfinish(conn);
}

bool stg_save_product(Product *product) {
    PGconn *conn = PQconnectdb(get_connect_url());
    if (!check_connection(conn)) {
        PQfinish(conn);
        return false;
    }

    const char *query = "INSERT INTO products (name, unit, address, quantity) VALUES ($1, $2, $3, $4) RETURNING id";
    
    char quantity_str[50];
    snprintf(quantity_str, sizeof(quantity_str), "%.2f", product->quantity);
    
    const char *paramValues[4] = {
        product->name,
        product->unit,
        product->address,
        quantity_str
    };

    PGresult *resultQuery = PQexecParams(conn, query, 4, NULL, paramValues, NULL, NULL, 0);
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

void stg_load_products(ProductList *list) {
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

bool stg_find_product(Product *product, int id) {
    PGconn *conn = PQconnectdb(get_connect_url());
    if (!check_connection(conn)) {
        PQfinish(conn);
        return false;
    }

    char id_str[12];
    snprintf(id_str, sizeof(id_str), "%d", id);

    const char *query = "SELECT id, name, unit, address, quantity FROM products WHERE id = $1";
    const char paramValues[1] = { id_str };


    PGresult *result = PQexecParams(conn, query, 1, NULL, paramValues, NULL, NULL, 0);
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
    product->quantity = atof(PQgetvalue(result, 0, 3));

    finish_query(result, conn);
    return true;
}

bool stg_update_product_quantity(Product *product) {

}

Product **stg_find_products_by_regex(char *regex) {

}

bool stg_find_product_by_name(Product *product, const char *name) {

}