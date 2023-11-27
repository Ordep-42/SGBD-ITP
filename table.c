#include "table.h"
#include <string.h>

#define separador "====================================\n"

Tabela criar_tabela() {
    Tabela table;
    printf("Digite o nome da tabela: ");
    scanf(" %[^\n]", &table.nome);
    printf("\nDigite o número de colunas para a tabela: ");
    scanf("%u", &table.num_colunas);
    for (int i = 0; i < table.num_colunas; i++) {
        printf("\n%s", separador);
        printf("Digite o nome da %dª coluna: ", i);
        scanf(" %[^\n]", table.colunas[i].nome);
        printf("\nDigite o tipo da %dª coluna: ", i);

        char tipo[50];
        scanf(" %[^\n]", tipo);
        if (strcmp(tipo, "INT") == 0) table.colunas[i].tipo = INT;
        else if (strcmp(tipo, "UNSIGNED_INT") == 0) table.colunas[i].tipo = UNSIGNED_INT;
        else if (strcmp(tipo, "FLOAT") == 0) table.colunas[i].tipo = FLOAT;
        else if (strcmp(tipo, "DOUBLE") == 0) table.colunas[i].tipo = DOUBLE;
        else if (strcmp(tipo, "CHAR") == 0) table.colunas[i].tipo = CHAR;
        else if (strcmp(tipo, "STRING") == 0) table.colunas[i].tipo = STRING;
    }
    printf("\n%s", separador);
    printf("Digite o nome da coluna que contem a chave primária: ");
    scanf(" %[^\n]", table.coluna_PK);
    return table;
}

void listar_tabelas() {

}

void listar_dados(Tabela *table) {
    printf("%s", separador);
    for (int i = 0; i < table->num_colunas; i++) {
        printf("%s -> %s\n", table->colunas[i].nome, table->colunas[i].tipo);
    }
    printf("%s", separador);
}

void apagar_tabela();