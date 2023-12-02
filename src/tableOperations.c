#include "../include/tableOperations.h"

#define separador "====================================\n"

Tabela criarTabela() {
    Tabela table;
    printf("%s", separador);
    printf("Digite o nome da tabela: ");
    scanf(" %[^\n]", table.nome);
    //Verificar se o nome da tabela já existe
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
    checarNomePK(&table);
    printf("%s", separador);
    printf("Tabela %s adicionada com sucesso!\n", table.nome);
    //Salvar o nome da tabela no arquivo de cabeçalhos
    //criar o arquivo da tabela
    //salvar a estrutura da tabela no arquivo da tabela
    return table;
}

void checarNomePK(Tabela* table) {
    //função que checa se o nome da coluna escolhida para ser PK existe
    if (checarNomeColuna(table->coluna_PK, table)) {
        checarTipoPK(table);
        return;
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
                checarTipoPK(table);
                return;
            }
        } 
    } while(!achou);
}

void checarTipoPK(Tabela* table) {
    //função que checa se o tipo da coluna escolhida para ser PK é unsigned int
    for (int i = 0; i < table->num_colunas; i++) {
        if (strcmp(table->colunas[i].nome, table->coluna_PK) == 0) {
            if (table->colunas[i].tipo != UNSIGNED_INT) {
                printf("%s", separador);
                printf("A coluna da chave primária deve ser do tipo UNSIGNED_INT.\n");
                printf("Digite o nome da coluna que contem a chave primária: ");
                scanf(" %[^\n]", table->coluna_PK);
                checarNomePK(table);
            } else {
                return;
            }
        }
    }
}

int checarColunaExiste(char* nome, Tabela* table) {
    //função que checa se o nome da coluna já existe
    for (int i = 0; i < table->num_colunas; i++) {
        if (strcmp(table->colunas[i].nome, nome) == 0) {
            return 1;
        }
    }
    return 0;
}

void listarTabelas() {
    //função que lista todas as tabelas existentes
    //ler o arquivo de cabeçalhos
    //imprimir os nomes das tabelas
}