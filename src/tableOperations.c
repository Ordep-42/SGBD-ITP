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
        printf("Já existe uma tabela com o nome desejado.\nEscolha outro nome e tente novamente.\n");
        printf("Digite o nome da tabela: ");
        scanf(" %[^\n]", nomeTabela);
    }
    strncpy(table.nome, nomeTabela, sizeof(nomeTabela));
    printf("Digite o número de colunas para a tabela: ");
    scanf("%u", &table.numColunas);
    for (int i = 0; i < table.numColunas; i++) {
        printf("%s", separador);
        char nomeColunaTemp[MAX_NAME_SIZE];
        while(1){ //verifica se já existe, mas n testei - bee
            printf("Digite o nome da %dª coluna: ", i+1);
            scanf(" %[^\n]", nomeColunaTemp);
            if (checarColunaExiste(&nomeColunaTemp, &table)){
                printf("Erro!, nome da coluna ja existe\nTente Novamente\n");
            }
            else{
                strcpy(table.colunas[i].nome,nomeColunaTemp);
                break;
            }   
        }
        printf("O tipo da coluna pode ser:\n"); // (escrito embaixo)
        printf("INT, UNSIGNED_INT, FLOAT, DOUBLE, CHAR ou STRING\n"); //adicionei as escolhas - bee

        // Pensando em implementar um switch case com numeros aqui (n aguento mais digitar UNSIGNED_INT toda vez q vou fazer um teste, ou tlvz eu crie um script pra isso :thinking:) - Peppo
        char tipo[20];
        while (1) { // enquanto o usuario não digitar algo válido ele vai repetir :P - bee
            printf("Digite o tipo desejado da %dª coluna: ", i + 1);
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
                printf("Erro!, tipo não encontrado\nTente Novamente\n");
            } // erro adicionado - bee
        }
    }
    int aux = table.numColunas;
    do {
        if (checarColunaUIntExiste(&table)) {
            break;
        } else {
            printf("Erro!,sua tabela deve conter pelo menos uma coluna de inteiro sem sinal\nEscreva uma coluna de tipo UNSIGNED_INT\n");
            printf("Digite o nome da %dª coluna: ", aux + 1);
            scanf(" %[^\n]", table.colunas[aux].nome);
            table.colunas[aux].tipo = UNSIGNED_INT;
            table.numColunas++;
        }
    } while (checarColunaUIntExiste(&table) == 0);
    printf("%s", separador);
    printf("Digite o nome da coluna que contem a chave primária: ");
    scanf(" %[^\n]", table.colunaPK);
    checarNomePK(&table);
    salvarNoHeader(nomeTabela);
    salvarMetadados(&table);
    printf("%s", separador);
    printf("Tabela %s adicionada com sucesso!\n", table.nome);
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

    if (header != NULL) {
        printf("%sNomes das tabelas existentes:\n", separador);
        printf("%s", header);
        free(header);
    } else {
        printf("Nao foi possivel abrir arquivo.\n");
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
            char *caminho = gerarCaminhoDeArquivo(tabelaApagar);
            remove(caminho);
            free(caminho);
            apagarTabelaDoHeader(tabelaApagar);
            printf("Tabela %s apagada com sucesso!\n", tabelaApagar);
            break;
        } else  {
            printf("Erro! Essa tabela não existe! Tente novamente\n");
        }
    }
}

/**
 * @brief Função responsável por imprimir uma tabela.
 * Solicita ao usuário o nome da tabela que deseja visualizar.
 * Verifica se a tabela existe e, em caso afirmativo, imprime seu conteúdo.
 * Apenas a primeira linha é impressa completamente, as demais linhas são truncadas para caberem na tela.
 * 
 * @param void
 * @return void
 */
void printarTabela() {
    char tabelaPrintar[MAX_NAME_SIZE];
    while (1) {
        printf("%s", separador);
        printf("Digite o nome da tabela que deseja visualizar:\n");
        scanf(" %[^\n]", tabelaPrintar);
        FILE *arquivo = fopen(gerarCaminhoDeArquivo(tabelaPrintar), "r");
        int linhas = contarLinhas(lerArquivo(gerarCaminhoDeArquivo(tabelaPrintar)));
        if (checarTabelaExiste(tabelaPrintar)) {
            printf("%s", separador);
            // Lê e imprime apenas a primeira linha
            char buffer[400];  // Tamanho máximo da linha
            if (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
                char *token = strtok(buffer, ",");
                while (token != NULL) {
                    printf("| %12s", token);
                    token = strtok(NULL, ",");
                }
                printf("%s", separador);
            }
            // Pular a 2 e 3
            fgets(buffer, sizeof(buffer), arquivo);  // Lê a 2
            fgets(buffer, sizeof(buffer), arquivo);  // Lê a 3
            // Imprime o resto
            for (int l = 3; l < linhas; l++) {
                if (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
                    char *token = strtok(buffer, ",");
                    while (token != NULL) {
                        printf("| %12s", token);
                        token = strtok(NULL, ",");
                    }
                    printf("%s", separador);
                }
            }
            fclose(arquivo);
            break;
        } else {
            printf("Erro! Essa tabela não existe! Tente novamente\n");
        }
    }
}