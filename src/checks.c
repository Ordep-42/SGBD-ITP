#include "../include/checks.h"

/**
 * @brief Função que verifica se o nome da coluna escolhida para ser chave primária existe na tabela.
 * Se a coluna existir, chama a função checarTipoPK para verificar o tipo da chave primária.
 * Caso contrário, solicita ao usuário que digite o nome da coluna que contém a chave primária até que uma coluna válida seja informada.
 * 
 * @param table Ponteiro para a estrutura Tabela que contém as informações da tabela.
 */
void checarNomePK(Tabela *table) {
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
    } while (!achou);
}


/**
 * @brief Função que verifica se o tipo da coluna escolhida para ser chave primária (PK) é unsigned int.
 * 
 * @param table Ponteiro para a estrutura Tabela que contém as informações da tabela.
 */
void checarTipoPK(Tabela *table) {
    for (int i = 0; i < table->numColunas; i++) {
        if (strcmp(table->colunas[i].nome, table->colunaPK) == 0) {
            if (table->colunas[i].tipo != UNSIGNED_INT) {
                printf("%s", separador);
                printf("A coluna da chave primária deve ser do tipo UNSIGNED_INT.\n");
                printf("Digite o nome da coluna que contém a chave primária: ");
                scanf(" %[^\n]", table->colunaPK);
                checarNomePK(table);
            } else {
                return;
            }
        }
    }
}

/**
 * @brief Funcção que verifica se o nome da tabela já existe.
 * 
 * @param nome O nome da tabela a ser verificada.
 * @return 1 se o nome da tabela existe, 0 caso contrário.
 */
int checarTabelaExiste(char *nome) {
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

/**
 * @brief Função que verifica se o nome da coluna já existe na tabela.
 * 
 * @param nome O nome da coluna a ser verificada.
 * @param table A tabela onde será feita a verificação.
 * @return 1 se o nome da coluna existe na tabela, 0 caso contrário.
 */
int checarColunaExiste(char *nome, Tabela *table) {
    for (int i = 0; i < table->numColunas; i++) {
        if (strcmp(table->colunas[i].nome, nome) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Função que verifica se existe uma coluna do tipo UNSIGNED_INT na tabela.
 * 
 * @param table Ponteiro para a tabela a ser verificada.
 * @return 1 se existe uma coluna do tipo UNSIGNED_INT, 0 caso contrário.
 */
int checarColunaUIntExiste(Tabela *table) {
    for (int p = 0; p < table->numColunas; p++) {
        if (table->colunas[p].tipo == UNSIGNED_INT) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Função que verifica se já existe algum registro na tabela com a chave primária desejada.
 *
 * @param nome O nome da tabela.
 * @param valor O valor da chave primária a ser verificada.
 * @param colunaPK O número da coluna da tabela onde a chave primária está localizada.
 * @return Retorna 1 se a chave primária existir, 0 se não existir e -1 se o arquivo não puder ser aberto.
 */
int checarPKExiste(char *nome, unsigned int valor, unsigned int colunaPK) {
    char *caminho = gerarCaminhoDeArquivo(nome); // Assume que o nome do arquivo é o nome da tabela com a extensão .txt

    FILE *arquivo = fopen(caminho, "r");
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo %s\n", caminho);
        return -1; // Retorna -1 se o arquivo não puder ser aberto
    }

    char *linha = malloc(sizeof(char) * MAX_NAME_SIZE * 10);
    while (fgets(linha, sizeof(linha), arquivo)) {
        char *coluna = strtok(linha, ","); // Assume que as colunas são separadas por vírgulas
        for (unsigned int i = 0; i < colunaPK; i++) {
            coluna = strtok(NULL, ",");
            if (coluna == NULL) {
                break;
            }
        }
        if (coluna != NULL && atoi(coluna) == valor) {
            fclose(arquivo);
            return 1; // Retorna 1 se a chave primária existir
        }
    }
    free(linha);
    fclose(arquivo);
    return 0; // Retorna 0 se a chave primária não existir
}