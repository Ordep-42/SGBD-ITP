#include "../include/tableOperations.h"

Tabela criarTabela() {
    Tabela table;
    printf("%s", separador);
    printf("Digite o nome da tabela: ");
    char nomeTabela[MAX_NAME_SIZE];
    scanf(" %[^\n]", nomeTabela);
    while(checarTabelaExiste(nomeTabela)) {
        printf("Já existe uma tabela com o nome desejado.\nEscolha outro nome e tente novamente.\n");
        printf("Digite o nome da tabela: ");
        scanf(" %[^\n]", nomeTabela);
    }
    strncpy(table.nome, nomeTabela, sizeof(nomeTabela));
    printf("Digite o número de colunas para a tabela: ");
    scanf("%u", &table.numColunas);
    for (int i = 0; i < table.numColunas; i++) {
        printf("%s", separador);
        printf("Digite o nome da %dª coluna: ", i+1);
        scanf(" %[^\n]", table.colunas[i].nome);
        printf("O tipo da coluna pode ser:\n"); // (escrito embaixo)
        printf("INT, UNSIGNED_INT, FLOAT, DOUBLE, CHAR ou STRING\n"); //adicionei as escolhas - bee

        //Pensando em implementar um switch case com numeros aqui (n aguento mais digitar UNSIGNED_INT toda vez q vou fazer um teste, ou tlvz eu crie um script pra isso :thinking:) - Peppo
        char tipo[20];
        while(1){ //enquanto o usuario não digitar algo válido ele vai repetir :P - bee
            printf("Digite o tipo desejado da %dª coluna: ", i+1);
            scanf(" %[^\n]", tipo);
            if (strcmp(tipo, "INT") == 0) {table.colunas[i].tipo = INT; break;} //ficou feio ik but foi o único jeito que eu achei de brekar
            else if (strcmp(tipo, "UNSIGNED_INT") == 0) {table.colunas[i].tipo = UNSIGNED_INT; break;}
            else if (strcmp(tipo, "FLOAT") == 0) {table.colunas[i].tipo = FLOAT; break;}
            else if (strcmp(tipo, "DOUBLE") == 0) {table.colunas[i].tipo = DOUBLE; break;}
            else if (strcmp(tipo, "CHAR") == 0) {table.colunas[i].tipo = CHAR; break;}
            else if (strcmp(tipo, "STRING") == 0) {table.colunas[i].tipo = STRING; break;}
            else{printf("Erro!, tipo não encontrado\nTente Novamente\n");} //erro adicionado - bee
        }
    }
    int aux = table.numColunas;
    do{
        if(checarColunaUIntExiste(&table)){
            break;
        }
        else{
            printf("Erro!,sua tabela deve conter pelo menos uma coluna de inteiro sem sinal\nEscreva uma coluna de tipo UNSIGNED_INT\n");
            printf("Digite o nome da %dª coluna: ", aux + 1);
            scanf(" %[^\n]", table.colunas[aux].nome);
            table.colunas[aux].tipo = UNSIGNED_INT; 
            table.numColunas++;
        }
    } while(checarColunaUIntExiste(&table) == 0);
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

void listarTabelas() {
    char *header = lerArquivo("./data/header.txt");

    if (header != NULL) {
        char nomeTabela[MAX_NAME_SIZE];
        printf("%sNomes das tabelas existentes:\n", separador);
        printf("%s", header);
        free(header);
    } else {
        printf("Nao foi possivel abrir arquivo.\n");
    }
}

void apagarTabela(){
    char tabelaApagar[MAX_NAME_SIZE];
    while(1){
        printf("%s", separador);
        printf("Digite o nome da tabela que deseja apagar:\n");
        scanf(" %[^\n]", tabelaApagar);
        if (checarTabelaExiste(tabelaApagar)){
            char *caminho = gerarCaminhoDeArquivo(tabelaApagar);
            remove(caminho);
            free(caminho);
            apagarTabelaDoHeader(tabelaApagar);
            break;
        }
        else{
            printf("Erro! Essa tabela não existe! Tente novamente\n");
        }
    }
    printf("Tabela %s apagada com sucesso!\n", tabelaApagar);
}
