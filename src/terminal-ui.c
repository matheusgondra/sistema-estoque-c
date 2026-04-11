#include "product.h"
#include "ui.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
void clear_terminal() { system("cls"); }
#else
void clear_terminal() { system("clear"); }
#endif

void showMenu() {
	clear_terminal();

	printf("┌───────────────────────────────┐\n");
	printf("│        MENU PRINCIPAL         │\n");
	printf("├───────────────────────────────┤\n");
	printf("│ 1. Cadastrar Novo Item        │\n");
	printf("│ 2. Exibir Itens               │\n");
	printf("│ 3. Buscar Item                │\n");
	printf("│ 4. Entrada de itens           │\n");
	printf("│ 5. Baixa de itens             │\n");
	printf("│ 0. Sair                       │\n");
	printf("└───────────────────────────────┘ \n");
	printf("Digite a opção desejada: ");
}

void showProducts(const ProductList *list) {
    clear_terminal();

    printf("┌──────┬──────────────────────┬──────────┬──────────┬────────────┐\n");
    printf("│ %-4s │ %-20s │ %-8s │ %-8s │ %-10s │\n", "ID", "NOME", "UNID", "END.", "QTD");
    printf("├──────┼──────────────────────┼──────────┼──────────┼────────────┤\n");

    for (size_t i = 0; i < list->size; i++) {
        Product *p = &list->items[i];
        
        printf("│ %-4" PRIu64 " │ %-20.20s │ %-8.8s │ %-8.8s │ %10.2f │\n", 
               p->id, 
               p->name, 
               p->unit, 
               p->address, 
               p->quantity);
    }
	printf("└──────┴──────────────────────┴──────────┴──────────┴────────────┘\n");
}
void showProduct(const Product *product) {
	clear_terminal();

	printf("┌──────────────────────────────┐\n");
	printf("│      DETALHES DO PRODUTO     │\n");
	printf("├──────────────────────────────┤\n");
	printf("│ ID:         %-16" PRIu64 " │\n", product->id);
	printf("│ NOME:       %-16.16s │\n", product->name);
	printf("│ UNIDADE:    %-16.16s │\n", product->unit);
	printf("│ ENDEREÇO:   %-16.16s │\n", product->address);
	printf("│ QUANTIDADE: %-16.2f │\n", product->quantity);
	printf("└──────────────────────────────┘\n");
}

void showError(const char *message) {
	clear_terminal();

	printf("┌──────────────────────────────┐\n");
	printf("│            ERRO              │\n");
	printf("├──────────────────────────────┤\n");
	printf("│ %-28s    │\n", message);
	printf("└──────────────────────────────┘\n");
}