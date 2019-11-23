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
    
    // Se não tem arquivo de entrada
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
    
    // Se tem arquivo de entrada
    else {
        int bombas = 0;
        FILE *arquivoResolvido = fopen(argv[1], "r");
            
        // Pegando os valores do arquivo com o jogo resolvido
        fscanf(arquivoResolvido, "%d", &dadosJogo.n);
        fscanf(arquivoResolvido, "%d\n\n", &dadosJogo.m);
        
        // Alocando matrizes
        dadosJogo.campo = alocaMatriz(dadosJogo.n, dadosJogo.m);
        dadosJogo.resolvido = alocaMatriz(dadosJogo.n, dadosJogo.m);
        
        // Lendo arquivo com o jogo resolvido
        for (int i = 0; i < dadosJogo.n; i++) {
            for (int j = 0; j < dadosJogo.m; ) {
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
        
        // Se passou como parâmetro apenas o jogo resolvido
        if (argc == 2) {
            inicializa(dadosJogo.campo, dadosJogo.n, dadosJogo.m);
            jogar(&dadosJogo, bombas);
        }
        
        // Se passou como parâmetro o jogo resolvido e um jogo salvo
        else if (argc == 3) {
            FILE *arquivoSalvo = fopen(argv[2], "r");
            fscanf(arquivoSalvo, "%d", &dadosJogo.n);
            fscanf(arquivoSalvo, "%d\n\n", &dadosJogo.m);
            
            // Lendo arquivo com o jogo salvo
            for (int i = 0; i < dadosJogo.n; i++) {
                for (int j = 0; j < dadosJogo.m; ) {
                    char c = fgetc(arquivoSalvo);
                    if (c == ' ' || c == '\n' || c == EOF)
                        continue;
                    if (c == 'o') {
                        if (dadosJogo.resolvido[i][j] == '-')
                            dadosJogo.campo[i][j] = ' ';
                        else dadosJogo.campo[i][j] = dadosJogo.resolvido[i][j];
                    }
                    else if (c == 'x')
                        dadosJogo.campo[i][j] = 'X';
                    else dadosJogo.campo[i][j] = c;
                    j++;
                }
            }
            fclose(arquivoSalvo);
            jogar(&dadosJogo, bombas);
        }
    }
    
    return 0;
}