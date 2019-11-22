/*
 *      Trabalho Prático - Campo Minado
 *      Leandro Rodrigues Rocha
 *      Turma 31
 *      Matrícula: 19.2.4085
 */

#include "cabecalho.h"

int main(int argc, char *argv[]) {
    Dados dadosJogo;
    char nivel[10];
    int ok = 0;
    
    menuInicial();
    
    // se não tem arquivo de entrada
    if (argc == 1) {
        do {
            printf(BOLD("DGITE O NÍVEL DE DIFICULDADE: [ FACIL ] [ MEDIO ] [ DIFICIL ]: "));
            scanf("%s", nivel);
            if (!strcmp(nivel, "FACIL") || !strcmp(nivel, "MEDIO") || !strcmp(nivel, "DIFICIL"))
                ok = 1;
            else printf(BOLD("COMANDO INVÁLIDO! DIGITE NOVAMENTE\n"));
        } while (!ok);
        system("clear");
        criaJogoAleatorio(&dadosJogo, nivel);
    }
    
    // se tem arquivo de entrada
    else {
        // se passou como parâmetro apenas o jogo resolvido
        if (argc == 2) {
            FILE *arquivoResolvido = fopen(argv[1], "r");
            int n, m;
            int bombas = 0;
            
            // pegando os valores do arquivo
            fscanf(arquivoResolvido, "%d", &n);
            fscanf(arquivoResolvido, "%d\n\n", &m);
            
            // alocando matrizes
            dadosJogo.campo = alocaMatriz(n, m);
            dadosJogo.resolvido = alocaMatriz(n, m);
            dadosJogo.n = n;
            dadosJogo.m = m;
            
            // lendo arquivo de texto com o jogo resolvido
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; ) {
                    char c = fgetc(arquivoResolvido);
                    if (c == ' ' || c == '\n' || c == EOF)
                        continue;
                    dadosJogo.resolvido[i][j] = c;
                    if (dadosJogo.resolvido[i][j] == 'x') {
                        bombas++;
                        dadosJogo.resolvido[i][j] = 'B';
                    }
                    else if (dadosJogo.resolvido[i][j] == '0')
                        dadosJogo.resolvido[i][j] = '-';
                    j++;
                }
            }
            
            fclose(arquivoResolvido);
            inicializa(dadosJogo.campo, n, m);
            jogar(&dadosJogo, bombas);
        }
        
        // se passou como parâmetro o jogo resolvido e um jogo salvo
        else if (argc == 3) {
            
        }
    }
    
    return 0;
}