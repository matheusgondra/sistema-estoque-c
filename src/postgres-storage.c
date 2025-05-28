#include "storage.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <libpq-fe.h>

char *get_connect_url() {
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

bool stg_save_product(Product *product) {
    PGconn *conn = PQconnectdb(get_connect_url());
    if (PQstatus(conn) != CONNECTION_OK) {
        printf("Erro ao conectar ao banco\n");
        return false;
    }

    const char *query = "INSERT INTO products (name, unit, address, quantity) VALUES ($1, $2, $3, $4)";
    
    char quantity_str[50];
    snprintf(quantity_str, sizeof(quantity_str), "%.2f", product->quantity);
    
    const char *paramValues[4] = {
        product->name,
        product->unit,
        product->address,
        quantity_str
    };
    const int paramLengths[4] = {
        (int) strlen(paramValues[0]),
        (int) strlen(paramValues[1]),
        (int) strlen(paramValues[2]),
        (int) strlen(paramValues[3])
    };
    const int paramFormats[4] = { 0, 0, 0, 0 };

    PGresult *resultQuery = PQexecParams(conn, query, 4, NULL, paramValues, paramLengths, paramFormats, 0);
    if (PQresultStatus(resultQuery) != PGRES_COMMAND_OK) {
        
        printf("Falha na query\n %s", PQerrorMessage(conn));
        printf("Detalhes: %s\n", PQresultErrorMessage(resultQuery));
        return false;
    }

    PQclear(resultQuery);
    PQfinish(conn);

    return true;
}

Product **stg_load_products() {

}

bool stg_find_product(Product *product, int id) {
    PGconn *conn = PQconnectdb(get_connect_url());
    if (PQstatus(conn) != CONNECTION_OK) {
        printf("Erro ao conectar ao banco de dados\n");
        return false;
    }

    char id_str[12];
    snprintf(id_str, sizeof(id_str), "%d", id);

    const char *query = "SELECT id, name, unit, address, quantity FROM products WHERE id = $1";
    const char paramValues[1] = { id_str };
    const char paramLengths[1] = { (int) sizeof(id_str) };
    const char paramFormats[1] = { 0 };


    PGresult *result = PQexecParams(conn, query, 1, NULL, paramValues, paramLengths, paramFormats, 0);
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Erro ao buscar produto: %s\n", PQerrorMessage(conn));
        PQclear(result);
        return false;
    }

    int n = PQntuples(result);
    if (n == 0) {
        printf("Produto não encontrado\n");
        return false;
    }

    product->id = atoi(PQgetvalue(result, 0, 0));
    strcpy(product->name, PQgetvalue(result, 0, 1));
    strcpy(product->unit, PQgetvalue(result, 0, 2));
    product->quantity = atof(PQgetvalue(result, 0, 3));

    return true;
}
bool stg_update_product_quantity(Product *product) {

}
Product **stg_find_products_by_regex(char *regex) {

}
bool stg_find_product_by_name(Product *product, const char *name) {

}