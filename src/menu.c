#include <stdio.h>
#include "../include/menu.h"

void menuInicial(){
     int acao;
    while (1) {
        printf("%s", separador);
        printf("------------Bem Vindo(a)------------\n");
        printf("----------------MENU----------------\n");
        printf("O que gostaria de fazer?\n");
        printf("1 - Criar uma nova tabela\n");
        printf("2 - Listar todas as tabelas\n");
        printf("3 - Listar dados de uma tabela\n");
        printf("4 - Adicionar uma tupla em uma tabela\n");
        printf("5 - Pesquisar valor em uma tabela\n");
        printf("6 - Apagar uma tupla de uma tabela\n");
        printf("7 - Deletar uma tabela\n");
        printf("8 - Sair\n");
        printf("Digite o numero da acao desejada:\n");
        while (1) {
            scanf("%d", &acao);
            if (acao < 1 || acao > 8) {
                printf("Erro! O numero digitado nao corresponde a nenhuma funcao\nTente Novamente:");
            } else {
                break;
            }
        }
        switch (acao) {
        case 1:
            criarTabela();
            break;
        case 2:
            listarTabelas();
            break;
        case 3:
            printarTabela();
            break;
        case 4:
            //adicionarLinha();
            break;
        case 5:
            // função pesquisar valor
            break;
        case 6:
            // função deletar tupla
            break;
        case 7:
            apagarTabela();
            break;
        case 8:
            return 0;
        }
    }
}