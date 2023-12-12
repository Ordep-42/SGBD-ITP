#include "../include/rowOperations.h"

void adicionarLinha() {
    char* nomeTabela = (char*) malloc(sizeof(char) * MAX_NAME_SIZE);
    printf("%s", separador);
    printf("Digite o nome da tabela que deseja adicionar uma linha: ");
    scanf(" %[^\n]", nomeTabela);
    while(!checarTabelaExiste(nomeTabela)) {
        printf("Tabela não existe. Digite novamente: ");
        scanf(" %[^\n]", nomeTabela);
    }
    char* caminhoTabela = gerarCaminhoDeArquivo(nomeTabela);
    char* conteudoTabela = lerArquivo(caminhoTabela);
    char* linhaAtual = strtok(conteudoTabela, "\n");
    int numColunas = contarVirgulas(linhaAtual);

    char* linhaNomes = (char*) malloc(sizeof(char) * MAX_NAME_SIZE * numColunas);
    char* linhaTipos = (char*) malloc(sizeof(char) * MAX_NAME_SIZE * numColunas);
    char* linhaPK = (char*) malloc(sizeof(char) * MAX_NAME_SIZE * numColunas);

    for (int i = 0; i < 3; i++) {
        switch (i) {
            case 0:
                strcpy(linhaNomes, linhaAtual);
                break;
            case 1:
                strcpy(linhaTipos, linhaAtual);
                break;
            case 2:
                strcpy(linhaPK, linhaAtual);
                break;
        }
        linhaAtual = strtok(NULL, "\n");
    }
    
    free(conteudoTabela);
    char** nomes = separarString(linhaNomes);
    char** tipos = separarString(linhaTipos);
    char** pks = separarString(linhaPK);
    free(linhaNomes);
    free(linhaTipos);
    free(linhaPK);
    
    char *novoValor = (char*) malloc(sizeof(char) * MAX_NAME_SIZE);
    novoValor[0] = '\0';
    char *novaLinha = (char*) malloc(sizeof(char) * MAX_NAME_SIZE * numColunas);
    novaLinha[0] = '\0';

    int debug = 0;
    for (unsigned int i = 0; i < numColunas; i++) {
        printf("%s", separador);
        printf("Digite o valor da coluna %s de tipo %s: ", nomes[i], tipos[i]);
        if (strcmp(tipos[i], "UNSIGNED_INT") == 0) {
            unsigned int valor;
            scanf("%u", &valor);
            if (strcmp(pks[i], "1") == 0) {
                while(1) {
                    if (checarPKExiste(nomeTabela, valor, i)) {
                        printf("Erro! Essa chave primária já existe! Tente novamente\n");
                        scanf("%u", &valor);
                    } else {
                        break;
                    }
                }
            }
            sprintf(novoValor, "%u", valor);
        } else if (strcmp(tipos[i], "INT") == 0) {
            int valor;
            scanf("%d", &valor);
            sprintf(novoValor, "%d", valor);
        } else if (strcmp(tipos[i], "FLOAT") == 0) {
            float valor;
            scanf("%f", &valor);
            sprintf(novoValor, "%f", valor);
        } else if (strcmp(tipos[i], "DOUBLE") == 0) {
            double valor;
            scanf("%lf", &valor);
            sprintf(novoValor, "%lf", valor);
        } else if (strcmp(tipos[i], "CHAR") == 0) {
            scanf("%c", novoValor);
        } else if (strcmp(tipos[i], "STRING") == 0) {
            scanf(" %[^\n]", novoValor);
        }

        strcat(novaLinha, novoValor);
        strcat(novaLinha, ",");
    }


    free(nomes);
    free(tipos);
    free(pks);
    free(novoValor);
    strcat(novaLinha, "\n");
    salvarEmArquivo(caminhoTabela, novaLinha, "a");
    free(novaLinha);
    free(caminhoTabela);
    free(nomeTabela);
}

void apagarLinha() {
    // pedir nome da tabela que deseja apagar uma linha
    // pedir a chave primária da linha que deseja apagar
}