#include "../include/rowOperations.h"

void listarDados(Tabela* table) {
    /* falta melhorar e mostrar os dados mesmo em vez de só mostrar o nome das colunas
    printf("%s", separador);
    for (int i = 0; i < table->num_colunas; i++) {
        printf("%s\n", table->colunas[i].nome);
    }
    printf("%s", separador);
    */
}

void adicionarLinha(Tabela* table) {
    /*
    for (int i = 0; i < table->num_colunas; i++) {
        printf("Digite o valor da %dª coluna: ", i);
        switch (table->colunas[i].tipo) {
            case UNSIGNED_INT:
                scanf("%u", &table->linhas[table->num_linhas].celulas[i].valor.unsigned_int);
                break;
            case INT:
                scanf("%d", &table->linhas[table->num_linhas].celulas[i].valor.int_);
                break;
            case FLOAT:
                scanf("%f", &table->linhas[table->num_linhas].celulas[i].valor.float_);
                break;
            case DOUBLE:
                scanf("%lf", &table->linhas[table->num_linhas].celulas[i].valor.double_);
                break;
            case CHAR:
                scanf(" %c", &table->linhas[table->num_linhas].celulas[i].valor.char_);
                break;
            case STRING:
                scanf(" %[^\n]", table->linhas[table->num_linhas].celulas[i].valor.string);
                break;
        }
    }
    table->num_linhas++;
    */
}