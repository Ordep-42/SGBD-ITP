#include "../include/fileOperations.h"

/**
 * @brief Salva o conteúdo em um arquivo.
 * 
 * @param nomeArquivo O nome do arquivo a ser salvo.
 * @param conteudo O conteúdo a ser salvo no arquivo.
 * @param modo O modo de abertura do arquivo (ex: "w" para escrita, "a" para anexar).
 * @return 1 se o arquivo foi salvo com sucesso, 0 caso contrário.
 */
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

/**
 * @brief Função responsável por ler o conteúdo de um arquivo.
 * 
 * @param nomeArquivo O nome do arquivo a ser lido.
 * @return Um ponteiro para o conteúdo do arquivo lido. Retorna NULL em caso de erro.
 */
char *lerArquivo(char *nomeArquivo) {
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

/**
 * @brief Função responsável por gerar o caminho de arquivo para um determinado nome.
 * 
 * Esta função recebe um nome de um arquivo no banco de dados e gera o caminho de arquivo para ele.
 * 
 * @param nome O nome do arquivo.
 * @return O caminho de arquivo gerado.
 */
char *gerarCaminhoDeArquivo(char *nome) {
    char *caminho = malloc(sizeof(char) * 64);
    strcpy(caminho, "./data/");
    strcat(caminho, nome);
    strcat(caminho, ".txt");
    return caminho;
}


/**
 * @brief Separa uma string em um array de substrings com base em um delimitador.
 * 
 * Esta função recebe uma string e a divide em várias substrings usando um delimitador.
 * As substrings são armazenadas em um array de strings alocado dinamicamente.
 * 
 * @param string A string a ser separada.
 * @return char** Um array de strings contendo as substrings separadas.
 */
char **separarString(char *string) {
    char *stringCopy = strdup(string); // Create a copy of the original string
    char **resultado = NULL;
    char *token = strtok(stringCopy, ",");
    int tamanho = 0;

    while (token != NULL) {
        resultado = realloc(resultado, sizeof(char *) * (tamanho + 1));
        if (resultado == NULL) {
            printf("Erro ao alocar memória\n");
            exit(1);
        }
        resultado[tamanho] = strdup(token); // Make a copy of the token
        tamanho++;
        token = strtok(NULL, ",");
    }

    resultado = realloc(resultado, sizeof(char *) * (tamanho + 1));
    resultado[tamanho] = NULL;
    free(stringCopy); // Free the copied string
    return resultado;
}

/**
 * @brief Apaga todas as linhas de um arquivo que correspondem a um determinado conteúdo.
 *
 * @param nomeArquivo O nome do arquivo a ser modificado.
 * @param conteudoLinha O conteúdo da linha a ser removida.
 */
void apagarLinhaPorConteudo(char *nomeArquivo, char *conteudoLinha) {
    char *conteudo = lerArquivo(nomeArquivo);
    char *linhaAtual = strtok(conteudo, "\n");
    char *novoConteudo = malloc(sizeof(char) * 512);
    novoConteudo[0] = '\0'; // Inicializa a string para evitar lixo de memória

    while (linhaAtual != NULL) {
        // Se a linha não corresponder ao conteudoLinha, adicione ao novoConteudo
        if (strcmp(linhaAtual, conteudoLinha) != 0) {
            strcat(novoConteudo, linhaAtual);
            strcat(novoConteudo, "\n");
        }
        linhaAtual = strtok(NULL, "\n");
    }
    salvarEmArquivo(nomeArquivo, novoConteudo, "w");
    free(conteudo);
    free(novoConteudo);
}

/**
 * @brief Função que conta o número de linhas em uma string.
 * 
 * @param conteudo A string contendo o conteúdo a ser contado.
 * @return O número de linhas na string.
 */
int contarLinhas(char *conteudo) {
    int linhas = 0;
    for (int i = 0; i < strlen(conteudo); i++) {
        if (conteudo[i] == '\n') {
            linhas++;
        }
    }
    return linhas;
}

/**
 * @brief Conta o número de vírgulas em uma string.
 * 
 * @param conteudo A string na qual as vírgulas serão contadas.
 * @return O número de vírgulas encontradas na string.
 */
int contarVirgulas(char *conteudo) {
    int virgulas = 0;
    for (int i = 0; i < strlen(conteudo); i++) {
        if (conteudo[i] == ',') {
            virgulas++;
        }
    }
    return virgulas;
}