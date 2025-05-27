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