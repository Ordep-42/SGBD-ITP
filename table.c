#include "table.h"
#include <string.h>
#include <stdio.h>

#define separador "====================================\n"

Tabela criar_tabela() {
    Tabela table;
    printf("%s", separador);
    printf("Digite o nome da tabela: ");
    scanf(" %[^\n]", table.nome);
    printf("Digite o número de colunas para a tabela: ");
    scanf("%u", &table.num_colunas);
    for (int i = 0; i < table.num_colunas; i++) {
        printf("%s", separador);
        printf("Digite o nome da %dª coluna: ", i+1);
        scanf(" %[^\n]", table.colunas[i].nome);
        printf("O tipo da coluna pode ser:\n"); // (escrito embaixo)
        printf("INT, UNSIGNED_INT, FLOAT, DOUBLE, CHAR ou STRING\n"); //adicionei as escolhas - bee

        char tipo[50];
        while(1){ //enquanto o usuario não digitar algo válido ele vai repetir :P - bee
            printf("Digite o tipo desejado da %dª coluna: ", i+1);
            scanf(" %[^\n]", tipo);
            if (strcmp(tipo, "INT") == 0) {table.colunas[i].tipo = INT; break;} //ficou feio ik but foi o único jeito que eu achei de brekar
            else if (strcmp(tipo, "UNSIGNED_INT") == 0) {table.colunas[i].tipo = UNSIGNED_INT; break;}
            else if (strcmp(tipo, "FLOAT") == 0) {table.colunas[i].tipo = FLOAT; break;}
            else if (strcmp(tipo, "DOUBLE") == 0) {table.colunas[i].tipo = DOUBLE; break;}
            else if (strcmp(tipo, "CHAR") == 0) {table.colunas[i].tipo = CHAR; break;}
            else if (strcmp(tipo, "STRING") == 0) {table.colunas[i].tipo = STRING; break;}
            else{printf("Erro!, tipo não encontrado\nTente Novamente\n");} //erro adicionado - bee
        }
    }
    printf("%s", separador);
    printf("Digite o nome da coluna que contem a chave primária: ");
    scanf(" %[^\n]", table.coluna_PK);
    checar_nome_PK(&table);
    printf("%s", separador);
    printf("Tabela %s adicionada com sucesso!\n", table.nome);
    return table;
}

void checar_nome_PK(Tabela* table) {
    //função que checa se o nome da coluna escolhida para ser PK existe
    for (int i = 0; i < table->num_colunas; i++) {
        if (strcmp(table->colunas[i].nome, table->coluna_PK) == 0) {
            checar_tipo_PK(table);
            return;
        }
    }
    int achou = 0;
    do {
        printf("%s", separador);
        printf("A coluna escolhida não existe.\n");
        printf("Digite o nome da coluna que contém a chave primária: ");
        scanf(" %[^\n]", table->coluna_PK);
        for (int i = 0; i < table->num_colunas; i++) {
            if (strcmp(table->colunas[i].nome, table->coluna_PK) == 0) {
                achou = 1;
                checar_tipo_PK(table);
                return;
            }
        } 
    } while(!achou);
}

void checar_tipo_PK(Tabela* table) {
    //função que checa se o tipo da coluna escolhida para ser PK é unsigned int
    for (int i = 0; i < table->num_colunas; i++) {
        if (strcmp(table->colunas[i].nome, table->coluna_PK) == 0) {
            if (table->colunas[i].tipo != UNSIGNED_INT) {
                printf("%s", separador);
                printf("A coluna da chave primária deve ser do tipo UNSIGNED_INT.\n");
                printf("Digite o nome da coluna que contem a chave primária: ");
                scanf(" %[^\n]", table->coluna_PK);
                checar_nome_PK(table);
            } else {
                return;
            }
        }
    }
}

void listar_dados(Tabela *table) {
    /* falta melhorar e mostrar os dados mesmo em vez de só mostrar o nome das colunas
    printf("%s", separador);
    for (int i = 0; i < table->num_colunas; i++) {
        printf("%s\n", table->colunas[i].nome);
    }
    printf("%s", separador);
    */
}

void adicionar_linha(Tabela *table) {
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