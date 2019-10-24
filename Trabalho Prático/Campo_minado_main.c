#include "cabecalho.h"

int main(int argc, char *argv[]) {
    char nivel[10], campo[MAX][MAX];
    int ok = 0;
    
    menuInicial();
    
    // se não tem arquivo de entrada
    do {
        printf("Digite o nível de dificuldade: [ facil ] [ medio ] [ dificil ]: ");
        scanf("%s", nivel);
        if (!strcmp(nivel, "facil") || !strcmp(nivel, "medio") || !strcmp(nivel, "dificil"))
            ok = 1;
        else printf("Comando inválido, digite novamente\n");
    } while (!ok);

    criaJogoAleatorio(campo, nivel);
    
    return 0;
}