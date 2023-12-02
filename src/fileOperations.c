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