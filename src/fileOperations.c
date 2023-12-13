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

char *gerarCaminhoDeArquivo(char *nome) {
    char *caminho = malloc(sizeof(char) * 64);
    strcpy(caminho, "./data/");
    strcat(caminho, nome);
    strcat(caminho, ".txt");
    return caminho;
}

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

int contarLinhas(char *conteudo) {
    int linhas = 0;
    for (int i = 0; i < strlen(conteudo); i++) {
        if (conteudo[i] == '\n') {
            linhas++;
        }
    }
    return linhas;
}

int contarVirgulas(char *conteudo) {
    int virgulas = 0;
    for (int i = 0; i < strlen(conteudo); i++) {
        if (conteudo[i] == ',') {
            virgulas++;
        }
    }
    return virgulas;
}