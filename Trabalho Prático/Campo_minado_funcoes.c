#include "cabecalho.h"

char** alocaMatriz(int n, int m) {
    char **mat = malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        mat[i] = malloc(m * sizeof(char));
    }
    return mat;
}

void desalocaMatriz(char **mat, int n, int m) {
    for (int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}

void inicializa(char **campo, int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            campo[i][j] = '-';
}

void revelaBombas(Dados *dadosJogo) {
    for (int i = 0; i < dadosJogo->n; i++) {
        for (int j = 0; j < dadosJogo->m; j++) {
            if (dadosJogo->resolvido[i][j] == 'B')
                dadosJogo->campo[i][j] = 'B';
        }
    }
}

void menuInicial() {
    system("clear");
    printf("              ");
    printf(TAB_TL);
    
    for (int i = 0; i < 40; i++)
        printf(TAB_HOR);
    printf(TAB_TR "\n");
    printf("              ");
    printf(TAB_VER BG_BLACK(WHITE(BOLD("             CAMPO MINADO               "))) TAB_VER);
    printf("\n              ");
    printf(TAB_BL);
    
    for (int i = 0; i < 40; i++)
        printf(TAB_HOR);
    printf(TAB_BR "\n");
}

void criaJogoAleatorio(Dados *dadosJogo, char nivel[]) {
    int n, m;
    int bombas;
    
    if (!strcmp(nivel, "FACIL")) {
        n = 5;
        m = 5;
        bombas = 3;
    }
    else if (!strcmp(nivel, "MEDIO")) {
        n = 12;
        m = 12;
        bombas = 25;
    }
    else {
        n = 13;
        m = 26;
        bombas = 70;
    }
    
    dadosJogo->n = n;
    dadosJogo->m = m;
    
    // alocando matrizes
    dadosJogo->campo = alocaMatriz(n, m);
    dadosJogo->resolvido = alocaMatriz(n, m);
    
    inicializa(dadosJogo->campo, dadosJogo->n, dadosJogo->m);
    inicializa(dadosJogo->resolvido, dadosJogo->n, dadosJogo->m);
    colocaBombas(dadosJogo, bombas);
    resolveJogo(dadosJogo->resolvido, dadosJogo->n, dadosJogo->m);
    jogar(dadosJogo, bombas);
}

void colocaBombas(Dados *dadosJogo, int bombas) {
    srand(time(NULL));
    int i = 0;
    
    while (i < bombas) {
        int x = random() % dadosJogo->n;
        int y = random() % dadosJogo->m;
        
        if (dadosJogo->resolvido[x][y] == '-') {
            dadosJogo->resolvido[x][y] = 'B';
            i++;
        }
    }
}

void marca(Dados *dadosJogo, int x, int y, int *contJogadas) {
    if (dadosJogo->resolvido[x][y] == '-')
        revelaCelulas(dadosJogo, x, y, contJogadas);

    else if (dadosJogo->resolvido[x][y] == 'B') {
        system("clear");
        
        // imprime onde estao as bombas
        printf(RED(BOLD("               BOMBA!!!\n")));
        revelaBombas(dadosJogo);
        imprimeCampo(dadosJogo->campo, dadosJogo->n, dadosJogo->m);
        desalocaMatriz(dadosJogo->campo, dadosJogo->n, dadosJogo->m);
        desalocaMatriz(dadosJogo->resolvido, dadosJogo->n, dadosJogo->m);
        exit(0);
    }
    else {
        dadosJogo->campo[x][y] = dadosJogo->resolvido[x][y];
        *contJogadas = *contJogadas + 1;
    }
        
}

void revelaCelulas(Dados *dadosJogo, int x, int y, int *contJogadas) {
    *contJogadas = *contJogadas + 1;
    dadosJogo->campo[x][y] = ' ';
    dadosJogo->resolvido[x][y] = ' ';
    
    int dx[] = {0, -1, 0, 1, 1, 1, -1, -1};
    int dy[] = {1, 0, -1, 0, -1, 1, 1, -1};
    
    for (int i = 0; i < 8; i++) {
        int linha = x + dx[i];
        int coluna = y + dy[i];
        if (linha >= 0 && coluna >= 0 && linha < dadosJogo->n && coluna < dadosJogo->m) {
            if (dadosJogo->resolvido[linha][coluna] == '-')
                revelaCelulas(dadosJogo, linha, coluna, contJogadas);
            else {
                if (dadosJogo->campo[linha][coluna] == '-')
                    *contJogadas = *contJogadas + 1;
                dadosJogo->campo[linha][coluna] = dadosJogo->resolvido[linha][coluna];
            }
        }
    }
}

// Funções de Impressão
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void imprimeCampo(char **campo, int n, int m) {
    // Imprime linhas em cima
    printf("\n   ");
    for (char i = 'A'; i < (char) m + 65; i++)
        printf("%c  ", i);
    printf("\n  ");
    
    printf(TAB_TL);
    for (int i = 0; i < m ; i++) {
        printf(TAB_HOR TAB_HOR);
        if (i < m - 1)
            printf(TAB_TJ);
    }
    printf(TAB_TR "\n");
    
    // Imprime o meio do campo
    int lin = 0, col = 0;
    for (int i = 0; i < 2 * n - 1; i++) {
        if (i % 2)
            printf("  " TAB_ML);
        else {
            printf("%c ", lin + 65);
            printf(TAB_VER);
        }
        
        for (int j = 0; j < m; j++) {
            if (i % 2) printf(TAB_HOR TAB_HOR);
            else printCor(campo[lin][col++]);
            if (j < m - 1) {
                if (i % 2) printf(TAB_MJ);
                else printf(TAB_VER);
            }
        }
        
        if (i % 2) printf(TAB_MR);
        else {
            printf(TAB_VER);
            lin++;
        }
        col = 0;
        printf("\n");
    }
    
    // Imprime linhas em baixo
    printf("  " TAB_BL);
    for (int i = 0; i < m; i++) {
        printf(TAB_HOR TAB_HOR);
        if (i < m - 1)
            printf(TAB_BJ);
    }
    printf(TAB_BR "\n");
}

void printCor(char valor) {
    if (valor == '1')
        printf(BLUE(BOLD("1 ")));
    else if (valor == '2')
        printf(GREEN(BOLD("2 ")));
    else if (valor == '3')
        printf(RED(BOLD("3 ")));
    else if (valor == '4')
        printf(CYAN(BOLD("4 ")));
    else if (valor == '5')
        printf(YELLOW(BOLD("5 ")));
    else if (valor == '6')
        printf(MAGENTA(BOLD("6 ")));
    else if (valor == '7')
        printf(BLACK(BOLD("7 ")));
    else if (valor == '8')
        printf(WHITE(BOLD("8 ")));
    else if (valor == 'B')
        printf(BG_RED(BOLD("B ")));
    else if (valor == ' ')
        printf("  ");
    else if (valor == '-') printf(BOLD("- "));
    else printf(BOLD("X "));
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void jogar(Dados *dadosJogo, int bombas) {
    char opcao[15];
    char coordenadas[15];
    int contJogadas = 0;
    
    while (1) {
        // Confere se terminou o jogo
        if (contJogadas == (dadosJogo->n * dadosJogo->m) - bombas) {
            printf(GREEN(BOLD("               PARABÉNS, VOCÊ VENCEU!!!")));
            imprimeCampo(dadosJogo->campo, dadosJogo->n, dadosJogo->m);
            desalocaMatriz(dadosJogo->campo, dadosJogo->n, dadosJogo->m);
            desalocaMatriz(dadosJogo->resolvido, dadosJogo->n, dadosJogo->m);
            exit(0);
        }
        
        // Caso não tenha ganhado ainda
        int ok = 1;
        imprimeCampo(dadosJogo->campo, dadosJogo->n, dadosJogo->m);
        printf(BOLD("\n           DIGITE UM DOS COMANDOS:\n") TAB_TL);
        for (int i = 0; i < 45; i++)
            printf(TAB_HOR);
        printf(TAB_TR "\n");
        printf(TAB_VER BOLD("x        -> MARCAR UM MINA                   ") TAB_VER "\n");
        printf(TAB_VER BOLD("o        -> REVELAR O VALOR DE UMA CÉLULA    ") TAB_VER "\n");
        printf(TAB_VER BOLD("resolver -> RESOLVE O JOGO AUTOMATICAMENTE   ") TAB_VER "\n");
        printf(TAB_VER BOLD("salvar   -> SALVAR O JOGO                    ") TAB_VER "\n");
        printf(TAB_VER BOLD("sair     -> ENCERRA O PROGRAMA               ") TAB_VER "\n");
        printf(TAB_BL);
        for (int i = 0; i < 45; i++)
            printf(TAB_HOR);
        printf(TAB_BR "\n");
        
        do {
            scanf("%s", opcao);
            if (!strcmp(opcao, "sair"))
                exit(0);
            
            // Marcar uma bomba
            else if (!strcmp(opcao, "x")) {
                int pode = 1;
                int lin, col;
                
                printf(BOLD("DIGITE A LINHA E COLUNA PARA MARCAR UMA BOMBA: "));
                do {
                    pode = 1;
                    scanf("%s", coordenadas);
                    lin = (int) coordenadas[0] - 65;
                    col = (int) coordenadas[1] - 65;
                    
                    if (lin < 0 || lin >= dadosJogo->n || col < 0 || col >= dadosJogo->m) {
                        printf(BOLD("ESSA POSIÇÃO NÃO EXISTE! DIGITE NOVAMENTE: "));
                        pode = 0;
                    }
                    else if (dadosJogo->campo[lin][col] != '-') {
                        printf(BOLD("ESSA POSIÇÃO JÁ FOI REVELADA! DIGITE OUTRA: "));
                        pode = 0;
                    }
                } while (!pode);
                dadosJogo->campo[lin][col] = 'X';
            }
            
            // Revelar uma célula
            else if (!strcmp(opcao, "o")) {
                int pode = 1;
                int lin, col;
                
                printf(BOLD("DIGITE A LINHA E COLUNA A SER REVELADA: "));
                do {
                    pode = 1;
                    scanf("%s", coordenadas);
                    lin = (int) coordenadas[0] - 65;
                    col = (int) coordenadas[1] - 65;
                    
                    if (lin < 0 || lin >= dadosJogo->n || col < 0 || col >= dadosJogo->m) {
                        printf(BOLD("ESSA POSIÇÃO NÃO EXISTE! DIGITE NOVAMENTE: "));
                        pode = 0;
                    }
                    else if (dadosJogo->campo[lin][col] != '-') {
                        printf(BOLD("ESSA POSIÇÃO JÁ FOI REVELADA! DIGITE OUTRA: "));
                        pode = 0;
                    }
                } while (!pode);
                marca(dadosJogo, lin, col, &contJogadas);
            }
            
            // Salvar jogo
            else if (!strcmp(opcao, "salvar")) {
                char nomeArquivo[15];
                printf("Digite o nome do arquivo para ser salvo: ");
                scanf("%s", nomeArquivo);
                
                // Criando um arquivo para o salvar o jogo em andamento
                FILE *andamento = fopen(nomeArquivo, "w");
                
                // Escrevendo os dados no arquivo
                fprintf(andamento, "%d %d\n\n", dadosJogo->n, dadosJogo->m);
                for (int i = 0; i < dadosJogo->n; i++) {
                    for (int j = 0; j < dadosJogo->m; j++) {
                        if (j) fprintf(andamento, " ");
                        if (dadosJogo->campo[i][j] == 'X')
                            fprintf(andamento, "x");
                        else if (dadosJogo->campo[i][j] == '-')
                            fprintf(andamento, "-");
                        else fprintf(andamento, "o");
                    }
                    fprintf(andamento, "\n");
                }
                // Salvar jogo resolvido
                exit(0);
            }
            
            // Resolver jogo
            else if (!strcmp(opcao, "resolver")) {
                system("clear");
                imprimeCampo(dadosJogo->resolvido, dadosJogo->n, dadosJogo->m);
                exit(0);
            }
            
            // Difgitou um comando inválido
            else {
                printf(BOLD("COMANDO INVÁLIDO! DIGITE NOVAMENTE: "));
                ok = 0;
            }
        } while (!ok);
        system("clear");
    }
}

void resolveJogo(char **resolvido, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (resolvido[i][j] == 'B') {
                // Em cima
                if (i) {
                    if (resolvido[i - 1][j] == '-')
                        resolvido[i - 1][j] = '1';
                    else {
                        if (resolvido[i - 1][j] != 'B')
                            resolvido[i - 1][j] = (char) (resolvido[i - 1][j] + 1);
                    }
                    // Diagonal principal em cima
                    if (j) {
                        if (resolvido[i - 1][j - 1] == '-')
                        resolvido[i - 1][j - 1] = '1';
                        else {
                            if (resolvido[i - 1][j - 1] != 'B')
                                resolvido[i - 1][j - 1] = (char) (resolvido[i - 1][j - 1] + 1);
                        }
                    }
                }
                
                // Em baixo
                if (i < n - 1) {
                    if (resolvido[i + 1][j] == '-')
                        resolvido[i + 1][j] = '1';
                    else {
                        if (resolvido[i + 1][j] != 'B')
                            resolvido[i + 1][j] = (char) (resolvido[i + 1][j] + 1);
                    }
                    // Diagonal principal em baixo
                    if (j < m - 1) {
                        if (resolvido[i + 1][j + 1] == '-')
                        resolvido[i + 1][j + 1] = '1';
                        else {
                            if (resolvido[i + 1][j + 1] != 'B')
                                resolvido[i + 1][j + 1] = (char) (resolvido[i + 1][j + 1] + 1);
                        }
                    }
                }
                
                // Esquerda
                if (j) {
                    if (resolvido[i][j - 1] == '-')
                        resolvido[i][j - 1] = '1';
                    else {
                        if (resolvido[i][j - 1] != 'B')
                            resolvido[i][j - 1] = (char) (resolvido[i][j - 1] + 1);
                    }
                    // Diagonal secundaria em baixo
                    if (i < n - 1) {
                        if (resolvido[i + 1][j - 1] == '-')
                            resolvido[i + 1][j - 1] = '1';
                        else {
                            if (resolvido[i + 1][j - 1] != 'B')
                                resolvido[i + 1][j - 1] = (char) (resolvido[i + 1][j - 1] + 1);
                        }
                    }
                }
                
                // Direita
                if (j < m - 1) {
                    if (resolvido[i][j + 1] == '-')
                        resolvido[i][j + 1] = '1';
                    else {
                        if (resolvido[i][j + 1] != 'B')
                            resolvido[i][j + 1] = (char) (resolvido[i][j + 1] + 1);
                    }
                    //  Diagonal secundaria em cima
                    if (i) {
                        if (resolvido[i - 1][j + 1] == '-')
                            resolvido[i - 1][j + 1] = '1';
                        else {
                            if (resolvido[i - 1][j + 1] != 'B')
                                resolvido[i - 1][j + 1] = (char) (resolvido[i - 1][j + 1] + 1);
                        }
                    }
                }
            }
        }
    }
}