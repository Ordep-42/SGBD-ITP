#include "../include/tableOperations.h"

/**
 * @brief Cria uma nova tabela.
 *
 * Solicita ao usuário o nome da tabela e o número de colunas desejado.
 * Em seguida, solicita o nome e o tipo de cada coluna.
 * Verifica se já existe uma tabela com o mesmo nome e se a tabela possui pelo menos uma coluna do tipo UNSIGNED_INT.
 * Por fim, salva o nome da tabela no cabeçalho e os metadados da tabela em um arquivo.
 *
 * @return A tabela criada.
 */
Tabela criarTabela() {
    Tabela table;
    printf("%s", separador);
    printf("Digite o nome da tabela: ");
    char nomeTabela[MAX_NAME_SIZE];
    scanf(" %[^\n]", nomeTabela);
    while (checarTabelaExiste(nomeTabela)) {
        printf("%sErro, já existe uma tabela com o nome desejado.\nEscolha outro nome e tente novamente.%s\n", RED, RESET);
        printf("Digite o nome da tabela: ");
        scanf(" %[^\n]", nomeTabela);
    }
    strncpy(table.nome, nomeTabela, sizeof(nomeTabela));
    printf("Digite o número de colunas para a tabela: ");
    scanf("%u", &table.numColunas);
    for (int i = 0; i < table.numColunas; i++) {
        printf("%s", separador);
        char nomeColunaTemp[MAX_NAME_SIZE];
        while (1) { // verifica se já existe, mas n testei - bee
            printf("Digite o nome da %s%dª%s coluna: ",YEL, i + 1, RESET);
            scanf(" %[^\n]", nomeColunaTemp);
            if (checarColunaExiste(&nomeColunaTemp, &table)) {
                printf("%sErro, nome da coluna ja existe.\nTente Novamente.%s\n", RED, RESET);
            } else {
                strcpy(table.colunas[i].nome, nomeColunaTemp);
                break;
            }
        }
        printf("O tipo da coluna pode ser:\n");                       // (escrito embaixo)
        printf("INT, UNSIGNED_INT, FLOAT, DOUBLE, CHAR ou STRING\n"); // adicionei as escolhas - bee

        // Pensando em implementar um switch case com numeros aqui (n aguento mais digitar UNSIGNED_INT toda vez q vou fazer um teste, ou tlvz eu crie um script pra isso :thinking:) - Peppo
        char tipo[20];
        while (1) { // enquanto o usuario não digitar algo válido ele vai repetir :P - bee
            printf("Digite o tipo desejado da %s%dª%s coluna: ", YEL, i + 1, RESET);
            scanf(" %[^\n]", tipo);
            if (strcmp(tipo, "INT") == 0) {
                table.colunas[i].tipo = INT;
                break;
            } // ficou feio ik but foi o único jeito que eu achei de brekar
            else if (strcmp(tipo, "UNSIGNED_INT") == 0) {
                table.colunas[i].tipo = UNSIGNED_INT;
                break;
            } else if (strcmp(tipo, "FLOAT") == 0) {
                table.colunas[i].tipo = FLOAT;
                break;
            } else if (strcmp(tipo, "DOUBLE") == 0) {
                table.colunas[i].tipo = DOUBLE;
                break;
            } else if (strcmp(tipo, "CHAR") == 0) {
                table.colunas[i].tipo = CHAR;
                break;
            } else if (strcmp(tipo, "STRING") == 0) {
                table.colunas[i].tipo = STRING;
                break;
            } else {
                printf("%sErro!, tipo não encontrado.\nTente Novamente.%s\n", RED, RESET);
            } // erro adicionado - bee
        }
    }
    int aux = table.numColunas;
    do {
        if (checarColunaUIntExiste(&table)) {
            break;
        } else {
            printf("%sErro!,sua tabela deve conter pelo menos uma coluna de inteiro sem sinal.%s\nEscreva uma coluna de tipo UNSIGNED_INT.\n", RED, RESET);
            printf("Digite o nome da %s%dª%s coluna: ", YEL, aux + 1, RESET);
            scanf(" %[^\n]", table.colunas[aux].nome);
            table.colunas[aux].tipo = UNSIGNED_INT;
            table.numColunas++;
        }
    } while (checarColunaUIntExiste(&table) == 0);
    printf("%s", separador);
    printf("Digite o nome da coluna que contem a %schave primária%s: ", CYN, RESET);
    scanf(" %[^\n]", table.colunaPK);
    checarNomePK(&table);
    salvarNoHeader(nomeTabela);
    salvarMetadados(&table);
    printf("%s", separador);
    printf("Tabela %s%s%s adicionada com sucesso!\n", YEL, table.nome, RESET);
    return table;
}

/**
 * @brief Função responsável por listar as tabelas existentes.
 *
 * A função lê o conteúdo do arquivo "header.txt" e exibe os nomes das tabelas existentes.
 * Caso o arquivo não possa ser aberto, uma mensagem de erro é exibida.
 */
void listarTabelas() {
    char *header = lerArquivo("./data/header.txt");

    printf("%s", separador);
    if (header != NULL) {
        printf("Nomes das tabelas existentes:\n");
        printf("%s", header);
        free(header);
    } else {
        printf("Não existem tabelas salvas no seu banco de dados.\n");
    }
}

/**
 * @brief Função responsável por apagar uma tabela.
 *
 * A função solicita ao usuário o nome da tabela que deseja apagar.
 * Em seguida, verifica se a tabela existe.
 * Se a tabela existir, o arquivo correspondente é removido do sistema de arquivos.
 * Além disso, a tabela também é removida do cabeçalho.
 *
 */
void apagarTabela() {
    char tabelaApagar[MAX_NAME_SIZE];
    while (1) {
        printf("%s", separador);
        printf("Digite o nome da tabela que deseja apagar:\n");
        scanf(" %[^\n]", tabelaApagar);
        if (checarTabelaExiste(tabelaApagar)) {
            char confirmacao[MAX_NAME_SIZE];
            printf("Essa é uma ação %sDESTRUTIVA%s e não pode ser revertida!\nSe quiser continuar digite o nome da tabela %s%s%s novamente: \n", RED, RESET, BRED, tabelaApagar, RESET);
            scanf(" %[^\n]", confirmacao);
            if (strcmp(tabelaApagar, confirmacao) == 0) {
                char *caminho = gerarCaminhoDeArquivo(tabelaApagar);
                remove(caminho);
                free(caminho);
                apagarTabelaDoHeader(tabelaApagar);
                printf("Tabela %s apagada com sucesso!\n", tabelaApagar);
                break;
            } else {
                printf("Ação cancelada!\n");
                break;
            }
        } else {
            printf("%sErro! Essa tabela não existe! Tente novamente.%s\n", RED, RESET);
        }
    }
}

/**
 * @brief Função responsável por imprimir uma tabela.
 * Solicita ao usuário o nome da tabela que deseja visualizar.
 * Verifica se a tabela existe e, em caso afirmativo, imprime seu conteúdo.
 * Apenas a primeira linha é impressa completamente, as demais linhas são truncadas para caberem na tela.
 *
 */
void printarTabela() {
    char tabelaPrintar[MAX_NAME_SIZE];
    printf("%s", separador);
    printf("Digite o nome da tabela que deseja visualizar: ");
    scanf(" %[^\n]", tabelaPrintar);
    while (!checarTabelaExiste(tabelaPrintar)) {
        printf("%sErro! Essa tabela não existe! Tente novamente: %s", RED, RESET);
        printf("Digite o nome da tabela que deseja visualizar: ");
        scanf(" %[^\n]", tabelaPrintar);
    }
    IntermediarioPrintarTabela(tabelaPrintar);
}

/**
 * @brief Função responsável por imprimir os dados de uma tabela a partir do nome.
 * 
 * @param nomeTabela O nome da tabela.
 */
void IntermediarioPrintarTabela(char *nomeTabela) {
    char *caminhoTabela = gerarCaminhoDeArquivo(nomeTabela);
    FILE *arquivo = fopen(caminhoTabela, "r");
    int linhas = contarLinhas(lerArquivo(caminhoTabela));
    separadorDeLinha(nomeTabela);
    if (linhas > 3) {
        char buffer[400]; // Tamanho máximo da linha

        fgets(buffer, sizeof(buffer), arquivo); // Lê a 1
        fgets(buffer, sizeof(buffer), arquivo); // Lê a 2

        // Pega a coluna da chave primária para formatar a saída
        int colunaPK = 0;
        if (fgets(buffer, sizeof(buffer), arquivo) != NULL) { // pega a 3 (que é a de 0 e 1s)
            char *token = strtok(buffer, ",");
            while (token != NULL) {
                if (strcmp(token, "1") == 0) {
                    break;
                } else {
                    colunaPK++;
                }
            }
        }

        rewind(arquivo); // Volta para o início do arquivo pra imprimir os dados

        // Lê e imprime apenas a primeira linha
        if (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
            char *token = strtok(buffer, ",");
            int contador = 0;
            while (token != NULL) {
                if (contador == colunaPK) {
                    printf("| %s%12s%s", CYN, token, RESET);
                } else {
                    printf("| %12s", token);
                }
                token = strtok(NULL, ",");
                contador++;
            }
            separadorDeLinha(nomeTabela);
        }

        // Pular a 2 e a 3
        fgets(buffer, sizeof(buffer), arquivo); // Lê a 2
        fgets(buffer, sizeof(buffer), arquivo); // Lê a 3 (que é a de 0 e 1s)

        // Imprime o resto
        for (int l = 3; l < linhas; l++) {
            if (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
                int contador = 0;
                char *token = strtok(buffer, ",");
                while (token != NULL) {
                    if (contador == colunaPK) {
                        printf("| %s%12s%s", UCYN, token, RESET);
                    } else {
                        printf("| %12s", token);
                    }
                    token = strtok(NULL, ",");
                    contador++;
                }
                separadorDeLinha(nomeTabela);
            }
        }
    } else {
        printf("A tabela %s%s %snão contem dados%s para serem exibidos.\n", YEL, nomeTabela, RED, RESET);
    }
    fclose(arquivo);
}

/**
 * @Brief Função que pede ao usuário a tabela e valor a ser pesquisado.
 *
 *
 *
*/

void pesquisar() {
    char tabelaPesquisar[MAX_NAME_SIZE];
    printf("%s", separador);
    printf("Digite o nome da tabela onde deseja pesquisar:\n");
    scanf(" %[^\n]", tabelaPesquisar);
    while (!checarTabelaExiste(tabelaPesquisar)) {
        printf("Erro! Essa tabela não existe! Tente novamente\n");
        printf("Digite o nome da tabela onde deseja pesquisar:\n");
        scanf(" %[^\n]", tabelaPesquisar);
    }

    char valorPesquisar[MAX_NAME_SIZE];
    printf("%s", separador);
    printf("Digite o valor que deseja buscar:\n");
    scanf(" %[^\n]", valorPesquisar);

    char *caminhoTabela = gerarCaminhoDeArquivo(tabelaPesquisar);
    FILE *arquivo = fopen(caminhoTabela, "r");
    int linhas = contarLinhas(lerArquivo(caminhoTabela));
    int colunaPKApagar = 0;
    int confirmar = 0;
    printf("%s", separador);
    char buffer[400]; // Tamanho máximo da linha
    // Pular a 1, 2 e 3
    fgets(buffer, sizeof(buffer), arquivo); // Lê a 1
    fgets(buffer, sizeof(buffer), arquivo); // Lê a 2
    fgets(buffer, sizeof(buffer), arquivo); // Lê a 3

    for (int l = 0; l < linhas; l++) {
        if (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
            char *token = strtok(buffer, ",");
            while (token != NULL) {

                if (strcmp(token, valorPesquisar) == 0) {
                    printf("O valor %s foi encontrado\n", valorPesquisar);
                    confirmar = 1;
                }
                token = strtok(NULL, ",");
            }
        }
    }
    if (confirmar == 0) {
        printf("O valor %s não foi encontrado\n", valorPesquisar);
    }
    fclose(arquivo);
}

/**
 * Função responsável por imprimir um separador de linha na saída padrão.
 * O separador é composto por um número de traços igual ao número de colunas da tabela multiplicado por 14, mais um.
 *
 * @param nomeTabela O nome da tabela.
 */
void separadorDeLinha(char *nomeTabela) {
    char *caminhoTabela = gerarCaminhoDeArquivo(nomeTabela);
    char *conteudoTabela = lerArquivo(caminhoTabela);
    char *linhaAtual = strtok(conteudoTabela, "\n");
    int numColunas = contarVirgulas(linhaAtual);
    int vezes = (numColunas * 14) + 1;
    for (int i = 0; i < vezes; i++) {
        printf("-");
    }
    printf("\n");
    free(caminhoTabela);
    free(conteudoTabela);
}