#include "cabecalho.h"

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
        printf(BG_WHITE(BLUE(BOLD("1 "))));
    else if (valor == '2')
        printf(BG_WHITE(GREEN(BOLD("2 "))));
    else if (valor == '3')
        printf(BG_WHITE(RED(BOLD("3 "))));
    else if (valor == '4')
        printf(BG_WHITE(CYAN(BOLD("4 "))));
    else if (valor == '5')
        printf(BG_WHITE(BLACK(BOLD("5 "))));
    else if (valor == '6')
        printf(BG_WHITE(MAGENTA(BOLD("6 "))));
    else if (valor == '7')
        printf(BG_WHITE(YELLOW(BOLD("7 "))));
    else if (valor == '8')
        printf(BG_WHITE(WHITE(BOLD("8 "))));
    else if (valor == 'B')
        printf(BG_RED(BOLD("B ")));
    else if (valor == ' ')
        printf(BG_WHITE("  "));
    else printf("%c ", valor);
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
    
    if (!strcmp(nivel, "facil")) {
        n = 5;
        m = 5;
        bombas = 3;
    }
    else if (!strcmp(nivel, "medio")) {
        n = 12;
        m = 12;
        bombas = 20;
    }
    else {
        n = 20;
        m = 20;
        bombas = 50;
    }
    
    inicializa(campo, n, m);
    inicializa(resolvido, n, m);
    colocaBombas(resolvido, n, m, bombas);
    resolveJogo(resolvido, n, m);
    jogar(campo, resolvido, n, m, bombas);
}

void resolveJogo(char resolvido[MAX][MAX], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (resolvido[i][j] == 'B') {
                if (i) {
                    // EM CIMA
                    if (resolvido[i - 1][j] == '-')
                        resolvido[i - 1][j] = '1';
                    else {
                        if (resolvido[i - 1][j] != 'B')
                            resolvido[i - 1][j] = (char) (resolvido[i - 1][j] + 1);
                    }
                    // DIAGONAL PRINCIPAL EM CIMA
                    if (j) {
                        if (resolvido[i - 1][j - 1] == '-')
                        resolvido[i - 1][j - 1] = '1';
                        else {
                            if (resolvido[i - 1][j - 1] != 'B')
                                resolvido[i - 1][j - 1] = (char) (resolvido[i - 1][j - 1] + 1);
                        }
                    }
                }
                
                if (i < n - 1) {
                    // EM BAIXO
                    if (resolvido[i + 1][j] == '-')
                        resolvido[i + 1][j] = '1';
                    else {
                        if (resolvido[i + 1][j] != 'B')
                            resolvido[i + 1][j] = (char) (resolvido[i + 1][j] + 1);
                    }
                    // DIAGONAL PRINCIPAL EM BAIXO
                    if (j < m - 1) {
                        if (resolvido[i + 1][j + 1] == '-')
                        resolvido[i + 1][j + 1] = '1';
                        else {
                            if (resolvido[i + 1][j + 1] != 'B')
                                resolvido[i + 1][j + 1] = (char) (resolvido[i + 1][j + 1] + 1);
                        }
                    }
                }
                
                if (j) {
                    // ESQUERDA
                    if (resolvido[i][j - 1] == '-')
                        resolvido[i][j - 1] = '1';
                    else {
                        if (resolvido[i][j - 1] != 'B')
                            resolvido[i][j - 1] = (char) (resolvido[i][j - 1] + 1);
                    }
                    // DIAGONAL SECUNDARIA EM BAIXO
                    if (i < n - 1) {
                        if (resolvido[i + 1][j - 1] == '-')
                            resolvido[i + 1][j - 1] = '1';
                        else {
                            if (resolvido[i + 1][j - 1] != 'B')
                                resolvido[i + 1][j - 1] = (char) (resolvido[i + 1][j - 1] + 1);
                        }
                    }
                }
                
                if (j < m - 1) {
                    // DIREITA
                    if (resolvido[i][j + 1] == '-')
                        resolvido[i][j + 1] = '1';
                    else {
                        if (resolvido[i][j + 1] != 'B')
                            resolvido[i][j + 1] = (char) (resolvido[i][j + 1] + 1);
                    }
                    //  DIAGONAL SECUNDARIA EM CIMA
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

void inicializa(char campo[MAX][MAX], int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            campo[i][j] = '-';
}

void jogarNovamente() {
    char op[15];
    do {
        printf("Deseja jogar novamente? [SIM] [NAO]: ");
        scanf("%s", op);
        
        if (strcmp(op, "SIM") && strcmp(op, "NAO"))
            printf("Comando inválido! Digite SIM ou NAO\n");
        else if (!strcmp(op, "SIM"))
            main();
        else exit(0);
    } while (strcmp(op, "SIM") && strcmp(op, "NAO"));
}

void jogar(char campo[MAX][MAX], char resolvido[MAX][MAX], int n, int m, int bombas) {
    char opcao[15];
    char op[15];
    int contJogadas = 0;
    
    while (1) {
        // Confere se terminou o jogo
        if (contJogadas == (n * m) - bombas) {
            printf(BOLD("PARABÉNS, VOCÊ VENCEU!!!\n"));
            imprimeCampo(campo, n, m);
            jogarNovamente();
        }
        //printf("ContJogadas = %d\n", contJogadas);
        
        // Caso não tenha ganhado ainda
        int ok = 1;
        imprimeCampo(campo, n, m);
        printf("\n           DIGITE UM DOS COMANDOS:\n\n");
        printf("x        -> Marcar um Mina\n");
        printf("o        -> revelar o valor de uma célula\n");
        printf("resolver -> Resolve o jogo altomaticamente\n");
        printf("salvar   -> Salva o jogo\n");
        printf("sair     -> Encerra o programa\n");
        
        do {
            scanf("%s", opcao);
            if (!strcmp(opcao, "sair"))
                exit(0);
            
            // Marcar uma bomba
            else if (!strcmp(opcao, "x")) {
                char x, y;
                int pode = 1;
                int lin, col;
                
                printf("Digite a linha e colona para marcar a bomba: ");
                do {
                    pode = 1;
                    scanf("\n%c %c", &x, &y);

                    lin = (int) x - 65;
                    col = (int) y - 65;
                    if (lin < 0 || lin >= n || col < 0 || col >= m) {
                        printf("Posição inválida! Digite novamente:\n");
                        pode = 0;
                    }
                    else if (campo[lin][col] != '-') {
                        printf("Essa posição já foi revelada! Digite outra:\n");
                        pode = 0;
                    }
                } while (!pode);
                campo[lin][col] = 'X';
                contJogadas++;
            }
            
            // Revelar uma célula
            else if (!strcmp(opcao, "o")) {
                char x, y;
                int pode = 1;
                int lin, col;
                
                printf("Digite a linha e colona a ser revelada: ");
                do {
                    pode = 1;
                    scanf("\n%c %c", &x, &y);
                    lin = (int) x - 65;
                    col = (int) y - 65;
                    if (lin < 0 || lin >= n || col < 0 || col >= m) {
                        printf("Posição inválida! Digite novamente: ");
                        pode = 0;
                    }
                    else if (campo[lin][col] != '-') {
                        printf("Essa posição já foi revelada! Digite outra: ");
                        pode = 0;
                    }
                } while (!pode);
                marca(campo, resolvido, n, m, lin, col, &contJogadas);
            }
            
            // Salvar jogo
            else if (!strcmp(opcao, "salvar")) {
                
            }
            // Resolver jogo
            else if (!strcmp(opcao, "resolver")) {
                imprimeCampo(resolvido, n, m);
                exit(0);
            }
            else {
                printf("Comando inválido! Digite novamente: ");
                ok = 0;
            }
        } while (!ok);
        system("clear");
    }
}

void marca(char campo[MAX][MAX], char resolvido[MAX][MAX], int n, int m, int x, int y, int *contJogadas) {
    if (resolvido[x][y] == '-')
        revelaCelulas(campo, resolvido, n, m, x, y, contJogadas);

    else if (resolvido[x][y] == 'B') {
        system("clear");
        
        // imprime onde estao as bombas
        printf("BOMBA!!!\n");
        revelaBombas(campo, resolvido, n, m);
        imprimeCampo(campo, n, m);
        jogarNovamente();
    }
    else {
        campo[x][y] = resolvido[x][y];
        *contJogadas = *contJogadas + 1;
    }
        
}

void revelaBombas(char campo[MAX][MAX], char resolvido[MAX][MAX], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (resolvido[i][j] == 'B')
                campo[i][j] = 'B';
        }
    }
}

int check(int i, int j, int n, int m) {
    return i >= 0 && j >= 0 && i < n && j < m;
}

void revelaCelulas(char campo[MAX][MAX], char resolvido[MAX][MAX], int n, int m, int x, int y, int *contJogadas) {
    *contJogadas = *contJogadas + 1;
    campo[x][y] = ' ';
    resolvido[x][y] = ' ';
    
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    for (int i = 0; i < 8; i++) {
        int linha = x + dx[i];
        int coluna = y + dy[i];
        if (check(linha, coluna, n, m)) {
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