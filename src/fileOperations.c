#include "../include/fileOperations.h"

int salvarEmArquivo(char *nomeArquivo, char *conteudo, char *modo) {
    FILE *arquivo = fopen(nomeArquivo, modo);
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return 0;
    }
    fprintf(arquivo, "%s", conteudo);
    fclose(arquivo);
    return 1;
}

char* lerArquivo(char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return NULL;
    }
    char *conteudo = NULL;
    size_t tamanhoConteudo = 0;

    char *linha = NULL;
    size_t tamanhoLinha = 0;
    size_t tamanhoLeitura;

    while ((tamanhoLeitura = getline(&linha, &tamanhoLinha, arquivo)) != -1) {
        conteudo = realloc(conteudo, tamanhoConteudo + tamanhoLeitura + 1);
        if (conteudo == NULL) {
            printf("Erro ao alocar memoria\n");
            free(linha);
            fclose(arquivo);
            return NULL;
        }
        strncpy(conteudo + tamanhoConteudo, linha, tamanhoLeitura);
        tamanhoConteudo += tamanhoLeitura;
    }

    conteudo[tamanhoConteudo] = '\0';
    free(linha);
    fclose(arquivo);
    return conteudo;
}

char* gerarCaminhoDeArquivo(char* nome) {
    char *caminho = malloc(sizeof(char) * 64);
    strcpy(caminho, "./data/");
    strcat(caminho, nome);
    strcat(caminho, ".txt");
    return caminho;
}

void salvarNoHeader(char* tableNome) {
    char header[sizeof(tableNome) + 2];
    strncpy(header, tableNome, sizeof(tableNome));
    strcat(header, "\n");
    salvarEmArquivo("./data/header.txt", header, "a");
}

void salvarMetadados(Tabela* table) {
    char *caminho = gerarCaminhoDeArquivo(table->nome);
    char separator[] = ",";
    char nameBuffer[512] = "";
    char typeBuffer[512] = "";
    char pkBuffer[512] = "";
    for (int i = 0; i < table->numColunas; i++) {
        strcat(nameBuffer, table->colunas[i].nome);
        strcat(nameBuffer, separator);
        switch (table->colunas[i].tipo)
        {
            case UNSIGNED_INT:
                strcat(typeBuffer, "UNSIGNED_INT");
                break;
            case INT:
                strcat(typeBuffer, "INT");
                break;
            case FLOAT:
                strcat(typeBuffer, "FLOAT");
                break;
            case DOUBLE:
                strcat(typeBuffer, "DOUBLE");
                break;
            case CHAR:
                strcat(typeBuffer, "CHAR");
                break;
            case STRING:
                strcat(typeBuffer, "STRING");
                break;
        }
        strcat(typeBuffer, separator);
        if (strcmp(table->colunas[i].nome, table->colunaPK) == 0) {
            strcat(pkBuffer, "1");
        } else {
            strcat(pkBuffer, "0");
        }
        strcat(pkBuffer, separator);
    }
    strcat(nameBuffer, "\n");
    strcat(typeBuffer, "\n");
    strcat(pkBuffer, "\n");
    salvarEmArquivo(caminho, nameBuffer, "a");
    salvarEmArquivo(caminho, typeBuffer, "a");
    salvarEmArquivo(caminho, pkBuffer, "a");
    free(caminho);
}