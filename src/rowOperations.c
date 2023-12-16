#include "../include/rowOperations.h"

/**
 * Função responsável por adicionar uma nova linha em uma tabela existente.
 * Abre o arquivo da tabela, lê as informações das colunas e pede para o usuário
 * digitar os valores de cada coluna.
 *
 */
void adicionarLinha() {
    char *nomeTabela = (char *)malloc(sizeof(char) * MAX_NAME_SIZE);
    printf("%s", separador);
    printf("Digite o nome da tabela que deseja adicionar uma linha: ");
    scanf(" %[^\n]", nomeTabela);
    while (!checarTabelaExiste(nomeTabela)) {
        printf("%sErro, essa tabela não existe. Digite novamente:%s ", RED, RESET);
        scanf(" %[^\n]", nomeTabela);
    }
    char *caminhoTabela = gerarCaminhoDeArquivo(nomeTabela);
    char *conteudoTabela = lerArquivo(caminhoTabela);
    char *linhaAtual = strtok(conteudoTabela, "\n");
    int numColunas = contarVirgulas(linhaAtual);

    char *linhaNomes = (char *)malloc(sizeof(char) * MAX_NAME_SIZE * numColunas);
    char *linhaTipos = (char *)malloc(sizeof(char) * MAX_NAME_SIZE * numColunas);
    char *linhaPK = (char *)malloc(sizeof(char) * MAX_NAME_SIZE * numColunas);

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
    char **nomes = separarString(linhaNomes);
    char **tipos = separarString(linhaTipos);
    char **pks = separarString(linhaPK);
    free(linhaNomes);
    free(linhaTipos);
    free(linhaPK);

    char *novoValor = (char *)malloc(sizeof(char) * MAX_NAME_SIZE);
    novoValor[0] = '\0';
    char *novaLinha = (char *)malloc(sizeof(char) * MAX_NAME_SIZE * numColunas);
    novaLinha[0] = '\0';

    for (unsigned int i = 0; i < numColunas; i++) {
        printf("%s", separador);
        printf("Digite o valor da coluna %s de tipo %s: ", nomes[i], tipos[i]);
        if (strcmp(tipos[i], "UNSIGNED_INT") == 0) {
            unsigned int valor;
            scanf("%u", &valor);
            if (strcmp(pks[i], "1") == 0) {
                while (1) {
                    if (checarPKExiste(nomeTabela, valor, i)) {
                        printf("%sErro! Essa chave primária já existe! Tente novamente: %s", RED, RESET);
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

/**
 * @brief Função responsável por apagar uma linha de uma tabela.
 *
 * A função solicita o nome da tabela em que deseja apagar uma linha
 * e a chave primária da linha que deseja apagar.
 */
void apagarLinha() {
    char tabelaApagarLinha[MAX_NAME_SIZE];
    unsigned int chaveApagarLinha;

    printf("%s", separador);
    printf("Digite o nome da tabela da qual deseja apagar uma linha: \n");
    scanf(" %[^\n]", tabelaApagarLinha);
    while (!checarTabelaExiste(tabelaApagarLinha)) {
        printf("%sErro! Essa tabela não existe! Tente novamente.%s\n", RED, RESET);
        printf("Digite o nome da tabela da qual deseja apagar uma linha: ");
        scanf(" %[^\n]", tabelaApagarLinha);
    }

    IntermediarioPrintarTabela(tabelaApagarLinha);
    printf("Digite a %schave primária%s da linha que gostaria de apagar: ", CYN, RESET);
    scanf("%u", &chaveApagarLinha);

    char *caminhoTabela = gerarCaminhoDeArquivo(tabelaApagarLinha);
    FILE *arquivo = fopen(caminhoTabela, "r");
    int linhas = contarLinhas(lerArquivo(caminhoTabela));
    int colunaPKApagar = 0;
    printf("%s", separador);
    char buffer[400]; // Tamanho máximo da linha

    // Pular a 1 e 2
    fgets(buffer, sizeof(buffer), arquivo);               // Lê a 1
    fgets(buffer, sizeof(buffer), arquivo);               // Lê a 2
    if (fgets(buffer, sizeof(buffer), arquivo) != NULL) { // pega a 3 (que é a de 0 e 1s)
        char *token = strtok(buffer, ",");
        while (token != NULL) {
            if (strcmp(token, "1") == 0) {
                break;
            } else {
                colunaPKApagar++;
                token = strtok(NULL, ",");
            }
        }
    }

    while (!checarPKExiste(tabelaApagarLinha, chaveApagarLinha, colunaPKApagar)) {
        printf("%sErro! Essa chave não existe! Tente novamente.%s\n", RED, RESET);
        printf("Digite o nome da chave da qual deseja apagar uma linha: ");
        scanf("%u", &chaveApagarLinha);
        printf("%s", separador);
    }
    char chaveString[10];
    sprintf(chaveString, "%u", chaveApagarLinha);
    while (1) {
        char confirmacao[MAX_NAME_SIZE];
        printf("Essa é uma ação %sDESTRUTIVA%s e não pode ser revertida!\nSe quiser continuar digite o nome da tabela %s%s%s novamente: ", RED, RESET, BRED, tabelaApagarLinha, RESET);
        scanf(" %[^\n]", confirmacao);
        if (strcmp(tabelaApagarLinha, confirmacao) == 0) {
            char linhaArquivo[200];
            char novaString[200];
            while (fgets(linhaArquivo, sizeof(linhaArquivo), arquivo) != NULL) {
                // Verifica se a chave está presente na linha
                if (strstr(linhaArquivo, chaveString) != NULL) {
                    // Se encontrou, salva a linha
                    strcpy(novaString, linhaArquivo);
                    break;
                }
            }
            char *linhaApagar = strtok(novaString, "\n");
            fclose(arquivo);
            apagarLinhaPorConteudo(caminhoTabela, linhaApagar);
            printf("Linha de %schave primária %u%s apagada com sucesso!\n", CYN, chaveApagarLinha, RESET);
            break;
        } else {
            printf("Ação cancelada!\n");
            break;
        }
    }
    free(caminhoTabela);
}
