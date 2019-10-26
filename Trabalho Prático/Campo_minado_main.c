#include "cabecalho.h"

int main(int argc, char *argv[]) {
    char nivel[10], campo[MAX][MAX];
    int ok = 0;
    
    menuInicial();
    
    // se não tem arquivo de entrada
    do {
        printf(BOLD("DGITE O NÍVEL DE DIFICULDADE: [ FACIL ] [ MEDIO ] [ DIFICIL ]: "));
        scanf("%s", nivel);
        if (!strcmp(nivel, "FACIL") || !strcmp(nivel, "MEDIO") || !strcmp(nivel, "DIFICIL"))
            ok = 1;
        else printf(BOLD("COMANDO INVÁLIDO! DIGITE NOVAMENTE\n"));
    } while (!ok);
    system("clear");
    criaJogoAleatorio(campo, nivel);
    
    return 0;
}