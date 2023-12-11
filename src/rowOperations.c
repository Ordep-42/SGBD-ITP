#include "../include/rowOperations.h"

void listarDados(Tabela* table) {
    /* falta melhorar e mostrar os dados mesmo em vez de só mostrar o nome das colunas
    printf("%s", separador);
    for (int i = 0; i < table->num_colunas; i++) {
        printf("%s\n", table->colunas[i].nome);
    }
    printf("%s", separador);
    */
}

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
    char* linhaNomes;
    char* linhaTipos;
    char* linhaPK;

    for (int i = 0; i < 3; i++) {
        switch (i) {
            case 0:
                strncpy(linhaNomes, linhaAtual, strlen(linhaAtual));
                break;
            case 1:
                strncpy(linhaTipos, linhaAtual, strlen(linhaAtual));
                break;
            case 2:
                strncpy(linhaPK, linhaAtual, strlen(linhaAtual));
                break;
        }
        linhaAtual = strtok(NULL, "\n");
    }

    char** nomes = separarString(linhaNomes);
    char** tipos = separarString(linhaTipos);
    char** pks = separarString(linhaPK);

    int numColunas = contarVirgular(linhaNomes);
    
    char *novoValor = (char*) malloc(sizeof(char) * MAX_NAME_SIZE);
    char *novaLinha = (char*) malloc(sizeof(char) * MAX_NAME_SIZE * numColunas);

    for (int i = 0; i < numColunas; i++) {
        printf("%s", separador);
        printf("Digite o valor da coluna %s de tipo %s: ", nomes[i], tipos[i]);
        switch (tipos[i]) {
            case "UNSIGNED_INT":
                scanf("%u", novoValor);
                break;
            case "INT":
                scanf("%d", novoValor);
                break;
            case "FLOAT":
                scanf("%f", novoValor);
                break;
            case "DOUBLE":
                scanf("%lf", novoValor);
                break;
            case "CHAR":
                scanf("%c", novoValor);
                break;
            case "STRING":
                scanf(" %[^\n]", novoValor);
                break;
            case default:
                printf("Tipo não reconhecido\n");
                break;
        }

        strcat(novaLinha, novoValor);
        strcat(novaLinha, ",");
    }
}

