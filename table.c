#include "table.h"
#include <string.h>
#include <stdio.h>

#define separador "====================================\n"

Tabela criar_tabela() {
    Tabela table;
    printf("Digite o nome da tabela: ");
    scanf(" %[^\n]", table.nome);
    printf("\nDigite o número de colunas para a tabela: ");
    scanf("%u", &table.num_colunas);
    for (int i = 0; i < table.num_colunas; i++) {
        printf("\n%s", separador);
        printf("Digite o nome da %dª coluna: ", i);
        scanf(" %[^\n]", table.colunas[i].nome);
        printf("\nO tipo da coluna pode ser:"); // (escrito embaixo)
        printf("\nINT, UNSIGNED_INT, FLOAT, DOUBLE, CHAR ou STRING"); //adicionei as escolhas - bee

        char tipo[50];
        while(1){ //enquanto o usuario não digitar algo válido ele vai repetir :P - bee
            printf("\nDigite o tipo desejado da %dª coluna: ", i);
            scanf(" %[^\n]", tipo);
            if (strcmp(tipo, "INT") == 0) {table.colunas[i].tipo = INT; break;} //ficou feio ik but foi o único jeito que eu achei de brekar
            else if (strcmp(tipo, "UNSIGNED_INT") == 0) {table.colunas[i].tipo = UNSIGNED_INT; break;}
            else if (strcmp(tipo, "FLOAT") == 0) {table.colunas[i].tipo = FLOAT; break;}
            else if (strcmp(tipo, "DOUBLE") == 0) {table.colunas[i].tipo = DOUBLE; break;}
            else if (strcmp(tipo, "CHAR") == 0) {table.colunas[i].tipo = CHAR; break;}
            else if (strcmp(tipo, "STRING") == 0) {table.colunas[i].tipo = STRING; break;}
            else{printf("Erro!, tipo não encontrado\nTente Novamente:");} //erro adicionado - bee
        }
        }
    printf("\n%s", separador);
    printf("Digite o nome da coluna que contem a chave primária: ");
    scanf(" %[^\n]", table.coluna_PK);
    return table;
}

void listar_dados(Tabela *table) {
    printf("%s", separador);
    for (int i = 0; i < table->num_colunas; i++) {
        printf("%s\n", table->colunas[i].nome);
    }
    printf("%s", separador);
}
