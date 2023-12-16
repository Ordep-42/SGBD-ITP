#include "../include/dataOperations.h"

/**
 * @brief Salva o nome da tabela no arquivo de cabeçalho do banco de dados.
 *
 * @param nomeTabela O nome da tabela a ser salvo no cabeçalho.
 */
void salvarNoHeader(char *nomeTabela) {
    char *header = (char *)malloc(sizeof(char) * (MAX_NAME_SIZE + 2));
    strcpy(header, nomeTabela);
    strcat(header, "\n");
    salvarEmArquivo("./data/header.txt", header, "a");
    free(header);
}

/**
 * @brief Salva os metadados da tabela em no seu arquivo do banco de dados.
 *
 * @param table Ponteiro para a tabela que os metadados serão salvos.
 */
void salvarMetadados(Tabela *table) {
    char *caminho = gerarCaminhoDeArquivo(table->nome);
    char separator[] = ",";
    char nameBuffer[512] = "";
    char typeBuffer[512] = "";
    char pkBuffer[512] = "";
    for (int i = 0; i < table->numColunas; i++) {
        strcat(nameBuffer, table->colunas[i].nome);
        strcat(nameBuffer, separator);
        switch (table->colunas[i].tipo) {
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

/**
 * @brief Apaga a tabela do arquivo de cabeçalho com o nome especificado.
 *
 * @param nomeTabela O nome da tabela a ser apagada do cabeçalho.
 */
void apagarTabelaDoHeader(char *nomeTabela) {
    apagarLinhaPorConteudo("./data/header.txt", nomeTabela);
}