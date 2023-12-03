#include "../include/tableOperations.h"

Tabela criarTabela() {
    Tabela table;
    printf("%s", separador);
    printf("Digite o nome da tabela: ");
    scanf(" %[^\n]", table.nome);
    //Verificar se o nome da tabela já existe
    printf("Digite o número de colunas para a tabela: ");
    scanf("%u", &table.numColunas);
    for (int i = 0; i < table.numColunas; i++) {
        printf("%s", separador);
        printf("Digite o nome da %dª coluna: ", i+1);
        scanf(" %[^\n]", table.colunas[i].nome);
        printf("O tipo da coluna pode ser:\n"); // (escrito embaixo)
        printf("INT, UNSIGNED_INT, FLOAT, DOUBLE, CHAR ou STRING\n"); //adicionei as escolhas - bee

        char tipo[50];
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
    }while(checarColunaUIntExiste(&table) == 0);
    printf("%s", separador);
    printf("Digite o nome da coluna que contem a chave primária: ");
    scanf(" %[^\n]", table.colunaPK);
    checarNomePK(&table);
    printf("%s", separador);
    printf("Tabela %s adicionada com sucesso!\n", table.nome);
    char header[51];
    strcpy(header, table.nome);
    strcat(header, "\n");
    salvarEmArquivo("../data/header.txt", header, "a");
    //criar o arquivo da tabela
    //salvar a estrutura da tabela no arquivo da tabela
    return table;
}

void listarTabelas() {
    FILE *arquivoTitulo = fopen("../data/header.txt", "r");

    if (arquivoTitulo != NULL) {
        char nomeTabela[50];
        printf("%sNomes das tabelas existentes:\n", separador);
        while (fscanf(arquivoTitulo, " %[^\n]", nomeTabela) == 1) {
            printf("%s\n", nomeTabela);
        }
        fclose(arquivoTitulo);
    } else {
        printf("Nao foi possivel abrir arquivo.\n");
    }
}

void apagarTabela(Tabela *table);
