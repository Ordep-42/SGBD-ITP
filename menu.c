#include <stdio.h>
#include "menu.h"

void menuinicial(){
    int acao;
    printf("------------Bem Vindo(a)------------\n");
    printf("----------------MENU----------------\n");
    printf("O que gostaria de fazer?\n");
    printf("1 - Criar uma nova tabela\n");
    printf("2 - Listar todas as tabelas\n");
    printf("3 - Listar dados de uma tabela\n");
    printf("4 - Pesquisar valor em uma tabela\n");
    printf("5 - Apagar uma tupla de uma tabela\n");
    printf("6 - Deletar uma tabela\n");
    printf("Digite o numero da acao desejada:\n");
    while(1){
        scanf("%d",&acao);
        if (acao<1 || acao>6){
            printf("Erro! O numero digitado nao corresponde a nenhuma funcao\nTente Novamente:");
        }
        else{
            break;
        }
    }
    switch (acao) {
        case 1:
            Tabela teste = criar_tabela();
            break;
        case 2:
            //função listar tabelas
            break;
        case 3:
            //função listar dados
            break;
        case 4:
            //função pesquisar valor
            break;
        case 5:
            //função apagar tupla
            break;
        case 6:
            //função deletar lista
            break;
    }
}