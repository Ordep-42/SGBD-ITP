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
    int existe_colunaUi = 0;
    int aux = table.num_colunas;
    do{
        for (int p = 0; p < table.num_colunas;p++){
            if (table.colunas[p].tipo == UNSIGNED_INT){
                existe_colunaUi = 1;
            }
        }
        if(existe_colunaUi == 1){
            break;
        }
        else{
            printf("Erro!,sua tabela deve conter uma coluna de inteiro sem sinal\nEscreva uma coluna de tipo UNSIGNED_INT\n");
            printf("Digite o nome da %dª coluna: ", aux + 1);
            scanf(" %[^\n]", table.colunas[aux].nome);
            table.colunas[aux].tipo = UNSIGNED_INT; 
            table.num_colunas++;
        }
    }while(existe_colunaUi == 0);
    printf("%s", separador);
    printf("Digite o nome da coluna que contem a chave primária: ");
    scanf(" %[^\n]", table.coluna_PK);
    checar_nome_PK(&table);
    printf("%s", separador);
    printf("Tabela %s adicionada com sucesso!\n", table.nome);
    FILE *arquivoTitulo = fopen("nomestabelas.txt", "at");
    if (arquivoTitulo != NULL) {
        fprintf(arquivoTitulo, "%s\n", table.nome);
        fclose(arquivoTitulo);
    } else {
        printf("Nao foi possivel abrir arquivo.\n");
    }
    //criar o arquivo da tabela
    //salvar a estrutura da tabela no arquivo da tabela
    return table;
}

void checarNomePK(Tabela* table) {
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

void checarTipoPK(Tabela* table) {
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

void listarTabelas() {
    FILE *arquivoTitulo = fopen("nomestabelas.txt", "rt");

    if (arquivoTitulo != NULL) {
        char nome_tabela[100];
        printf("Nomes das tabelas existentes:\n");
        while (fscanf(arquivoTitulo, " %[^\n]", nome_tabela) == 1) {
            printf("%s\n", nome_tabela);
        }
        fclose(arquivoTitulo);
    } else {
        printf("Nao foi possivel abrir arquivo.\n");
    }
}