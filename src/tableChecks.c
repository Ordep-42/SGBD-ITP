#include "../include/tableChecks.h"

void checarNomePK(Tabela *table) {
    //função que checa se o nome da coluna escolhida para ser PK existe
    if (checarColunaExiste(table->colunaPK, table)) {
        checarTipoPK(table);
        return;
    }
    int achou = 0;
    do {
        printf("%s", separador);
        printf("A coluna escolhida não existe.\n");
        printf("Digite o nome da coluna que contém a chave primária: ");
        scanf(" %[^\n]", table->colunaPK);
        for (int i = 0; i < table->numColunas; i++) {
            if (strcmp(table->colunas[i].nome, table->colunaPK) == 0) {
                achou = 1;
                checarTipoPK(table);
                return;
            }
        } 
    } while(!achou);
}

void checarTipoPK(Tabela *table) {
    //função que checa se o tipo da coluna escolhida para ser PK é unsigned int
    for (int i = 0; i < table->numColunas; i++) {
        if (strcmp(table->colunas[i].nome, table->colunaPK) == 0) {
            if (table->colunas[i].tipo != UNSIGNED_INT) {
                printf("%s", separador);
                printf("A coluna da chave primária deve ser do tipo UNSIGNED_INT.\n");
                printf("Digite o nome da coluna que contem a chave primária: ");
                scanf(" %[^\n]", table->colunaPK);
                checarNomePK(table);
            } else {
                return;
            }
        }
    }
}

int checarTabelaExiste(char *nome, Tabela *table) {
    //função que checa se o nome da tabela já existe
}

int checarColunaExiste(char *nome, Tabela *table) {
    //função que checa se o nome da coluna já existe
    for (int i = 0; i < table->numColunas; i++) {
        if (strcmp(table->colunas[i].nome, nome) == 0) {
            return 1;
        }
    }
    return 0;
}

int checarColunaUIntExiste(Tabela *table) {
    //função que checa se existe uma coluna de tipo UNSIGNED_INT
    for (int p = 0; p < table->numColunas;p++) {
        if (table->colunas[p].tipo == UNSIGNED_INT){
            return 1;
        }
    }
    return 0;
}