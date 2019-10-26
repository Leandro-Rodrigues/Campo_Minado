#include "cabecalho.h"

void inicializa(char campo[MAX][MAX], int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            campo[i][j] = '-';
}

void revelaBombas(char campo[MAX][MAX], char resolvido[MAX][MAX], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (resolvido[i][j] == 'B')
                campo[i][j] = 'B';
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

void criaJogoAleatorio(char campo[MAX][MAX], char nivel[]) {
    int n, m;
    int bombas;
    char resolvido[MAX][MAX];
    
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
    
    inicializa(campo, n, m);
    inicializa(resolvido, n, m);
    colocaBombas(resolvido, n, m, bombas);
    resolveJogo(resolvido, n, m);
    jogar(campo, resolvido, n, m, bombas);
}

void colocaBombas(char resolvido[MAX][MAX], int n, int m, int bombas) {
    srand(time(NULL));
    int i = 0;
    
    while (i < bombas) {
        int x = random() % n;
        int y = random() % m;
        
        if (resolvido[x][y] == '-') {
            resolvido[x][y] = 'B';
            i++;
        }
    }
}

void jogarNovamente() {
    char op[15];
    do {
        printf(BOLD("DESEJA JOGAR NOVAMENTE? [SIM] [NAO]: "));
        scanf("%s", op);
        
        if (strcmp(op, "SIM") && strcmp(op, "NAO"))
            printf(BOLD("COMANDO INVÁLIDO! DIGITE SIM OU NAO\n"));
        else if (!strcmp(op, "SIM"))
            main();
        else exit(0);
    } while (strcmp(op, "SIM") && strcmp(op, "NAO"));
}

void marca(char campo[MAX][MAX], char resolvido[MAX][MAX], int n, int m, int x, int y, int *contJogadas) {
    if (resolvido[x][y] == '-')
        revelaCelulas(campo, resolvido, n, m, x, y, contJogadas);

    else if (resolvido[x][y] == 'B') {
        system("clear");
        
        // imprime onde estao as bombas
        printf(RED(BOLD("               BOMBA!!!\n")));
        revelaBombas(campo, resolvido, n, m);
        imprimeCampo(campo, n, m);
        jogarNovamente();
    }
    else {
        campo[x][y] = resolvido[x][y];
        *contJogadas = *contJogadas + 1;
    }
        
}

void revelaCelulas(char campo[MAX][MAX], char resolvido[MAX][MAX], int n, int m, int x, int y, int *contJogadas) {
    *contJogadas = *contJogadas + 1;
    campo[x][y] = ' ';
    resolvido[x][y] = ' ';
    
    int dx[] = {0, -1, 0, 1, 1, 1, -1, -1};
    int dy[] = {1, 0, -1, 0, -1, 1, 1, -1};
    
    for (int i = 0; i < 8; i++) {
        int linha = x + dx[i];
        int coluna = y + dy[i];
        if (linha >= 0 && coluna >= 0 && linha < n && coluna < m) {
            if (resolvido[linha][coluna] == '-')
                revelaCelulas(campo, resolvido, n, m, linha, coluna, contJogadas);
            else {
                if (campo[linha][coluna] == '-')
                    *contJogadas = *contJogadas + 1;
                campo[linha][coluna] = resolvido[linha][coluna];
            }
        }
    }
}

void imprimeCampo(char campo[MAX][MAX], int n, int m) {
    // Imprime linhas em cima
    printf("   ");
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
        printf(BLACK(BOLD("5 ")));
    else if (valor == '6')
        printf(MAGENTA(BOLD("6 ")));
    else if (valor == '7')
        printf(YELLOW(BOLD("7 ")));
    else if (valor == '8')
        printf(WHITE(BOLD("8 ")));
    else if (valor == 'B')
        printf(BG_RED(BOLD("B ")));
    else if (valor == ' ')
        printf("  ");
    else if (valor == '-') printf(BOLD("- "));
    else printf(BOLD("X "));
}

void jogar(char campo[MAX][MAX], char resolvido[MAX][MAX], int n, int m, int bombas) {
    char opcao[15];
    int contJogadas = 0;
    
    while (1) {
        // Confere se terminou o jogo
        if (contJogadas == (n * m) - bombas) {
            printf(GREEN(BOLD("               PARABÉNS, VOCÊ VENCEU!!!\n")));
            imprimeCampo(campo, n, m);
            jogarNovamente();
        }
        
        // Caso não tenha ganhado ainda
        int ok = 1;
        imprimeCampo(campo, n, m);
        printf(BOLD("\n           DIGITE UM DOS COMANDOS:\n") TAB_TL);
        for (int i = 0; i < 45; i++)
            printf(TAB_HOR);
        printf(TAB_TR "\n");
        printf(TAB_VER BOLD("X        -> MARCAR UM MINA                   ") TAB_VER "\n");
        printf(TAB_VER BOLD("O        -> REVELAR O VALOR DE UMA CÉLULA    ") TAB_VER "\n");
        printf(TAB_VER BOLD("RESOLVER -> RESOLVE O JOGO ALTOMATICAMENTE   ") TAB_VER "\n");
        printf(TAB_VER BOLD("SALVAR   -> SALVAR O JOGO                    ") TAB_VER "\n");
        printf(TAB_VER BOLD("SAIR     -> ENCERRA O PROGRAMA               ") TAB_VER "\n");
        printf(TAB_BL);
        for (int i = 0; i < 45; i++)
            printf(TAB_HOR);
        printf(TAB_BR "\n");
        
        do {
            scanf("%s", opcao);
            if (!strcmp(opcao, "SAIR"))
                exit(0);
            
            // Marcar uma bomba
            else if (!strcmp(opcao, "X")) {
                char x, y;
                int pode = 1;
                int lin, col;
                
                printf(BOLD("DIGITE A LINHA E COLUNA PARA MARCAR UMA BOMBA: "));
                do {
                    pode = 1;
                    scanf("\n%c %c", &x, &y);

                    lin = (int) x - 65;
                    col = (int) y - 65;
                    if (lin < 0 || lin >= n || col < 0 || col >= m) {
                        printf(BOLD("ESSA POSIÇÃO NÃO EXISTE! DIGITE NOVAMENTE: "));
                        pode = 0;
                    }
                    else if (campo[lin][col] != '-') {
                        printf(BOLD("ESSA POSIÇÃO JÁ FOI REVELADA! DIGITE OUTRA: "));
                        pode = 0;
                    }
                    //fflush(stdin);
                } while (!pode);
                campo[lin][col] = 'X';
            }
            
            // Revelar uma célula
            else if (!strcmp(opcao, "O")) {
                char x, y;
                int pode = 1;
                int lin, col;
                
                printf(BOLD("DIGITE A LINHA E COLUNA A SER REVELADA: "));
                do {
                    pode = 1;
                    scanf("\n%c %c", &x, &y);
                    lin = (int) x - 65;
                    col = (int) y - 65;
                    if (lin < 0 || lin >= n || col < 0 || col >= m) {
                        printf(BOLD("ESSA POSIÇÃO NÃO EXISTE! DIGITE NOVAMENTE: "));
                        pode = 0;
                    }
                    else if (campo[lin][col] != '-') {
                        printf(BOLD("ESSA POSIÇÃO JÁ FOI REVELADA! DIGITE OUTRA: "));
                        pode = 0;
                    }
                    //fflush(stdin);
                } while (!pode);
                marca(campo, resolvido, n, m, lin, col, &contJogadas);
            }
            
            // Salvar jogo
            else if (!strcmp(opcao, "SALVAR")) {
                
            }
            
            // Resolver jogo
            else if (!strcmp(opcao, "RESOLVER")) {
                system("clear");
                imprimeCampo(resolvido, n, m);
                jogarNovamente();
            }
            
            else {
                printf(BOLD("COMANDO INVÁLIDO! DIGITE NOVAMENTE: "));
                ok = 0;
            }
            //fflush(stdin);
        } while (!ok);
        system("clear");
    }
}

void resolveJogo(char resolvido[MAX][MAX], int n, int m) {
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