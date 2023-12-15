#include "../include/menu.h"

/**
 * @brief Função responsável por exibir o menu inicial do programa e realizar as ações selecionadas pelo usuário.
 */
void menuInicial() {
    int acao;
    while (1) {
        printf("%s", separador);
        printf("------------%sBem Vindo(a)%s------------\n", HBLU, RESET);
        printf("----------------%sMENU%s----------------\n", HCYN, RESET);
        printf("O que gostaria de fazer?\n");
        printf("%s1%s - %sCriar%s uma nova tabela\n", GRNB, RESET, YEL, RESET);
        printf("%s2%s - %sListar%s todas as tabelas\n", GRNB, RESET, CYN, RESET);
        printf("%s3%s - %sListar%s dados de uma tabela\n", GRNB, RESET, CYN, RESET);
        printf("%s4%s - %sAdicionar%s uma tupla em uma tabela\n", GRNB, RESET, GRN, RESET);
        printf("%s5%s - %sPesquisar%s valor em uma tabela\n", GRNB, RESET, MAG, RESET);
        printf("%s6%s - %sApagar%s uma tupla de uma tabela\n", GRNB, RESET, RED, RESET);
        printf("%s7%s - %sApagar%s uma tabela\n", GRNB, RESET, RED, RESET);
        printf("%s8%s - %sSair%s\n", GRNB, RESET, BLK, RESET);
        printf("Digite o %snumero%s da ação desejada: ", GRNB, RESET);
        while (1) {
            scanf("%d", &acao);
            if (acao < 1 || acao > 8) {
                printf("%sErro! O numero digitado nao corresponde a nenhuma função\nTente Novamente:%s ", RED, RESET);
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
            listarTabelas();
            printarTabela();
            break;
        case 4:
            listarTabelas();
            adicionarLinha();
            break;
        case 5:
            listarTabelas();
            // função pesquisar valor
            break;
        case 6:
            listarTabelas();
			apagarLinha();
            break;
        case 7:
            listarTabelas();
            apagarTabela();
            break;
        case 8:
            printf("Desligando o programa...\n");
            exit(EXIT_SUCCESS);
        }
    }
}
