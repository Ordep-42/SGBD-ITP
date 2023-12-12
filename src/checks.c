#include "../include/checks.h"

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

int checarTabelaExiste(char *nome) {
    //função que checa se o nome da tabela já existe
    FILE *arquivo = fopen("./data/header.txt", "r");
    if (arquivo != NULL) {
        char nomeTabela[MAX_NAME_SIZE];
        while (fscanf(arquivo, " %[^\n]\n", nomeTabela) != EOF) {
            if (strcmp(nomeTabela, nome) == 0) {
                fclose(arquivo);
                return 1;
            }
        }
        fclose(arquivo);
    }
    return 0;
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

int checarPKExiste(char *nome, unsigned int valor, unsigned int colunaPK) {
    //função que checa se a chave primária já existe
    char *conteudoOriginal = lerArquivo(gerarCaminhoDeArquivo(nome));
    char *conteudo = strdup(conteudoOriginal);
    char *linhaAtual = strtok(conteudo, "\n");
    linhaAtual = strtok(NULL, "\n");
    linhaAtual = strtok(NULL, "\n");
    linhaAtual = strtok(NULL, "\n");
    
    while (linhaAtual != NULL) {
        char **valores = separarString(linhaAtual);
        if (atoi(valores[colunaPK]) == valor) {
            return 1;
        }
        linhaAtual = strtok(NULL, "\n");
        free(valores); // Free the array of strings
    }
    free(conteudo); // Free the copied string
    free(conteudoOriginal); // Free the original string
    return 0;
}