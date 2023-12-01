#include "fileOperations.h"

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
    char *conteudo = (char*) malloc(sizeof(char));
    char c;
    int i = 0;
    while ((c = fgetc(arquivo)) != EOF) {
        conteudo[i] = c;
        i++;
        conteudo = (char*) realloc(conteudo, (i+1)*sizeof(char));
    }
    conteudo[i] = '\0';
    fclose(arquivo);
    return conteudo;
}