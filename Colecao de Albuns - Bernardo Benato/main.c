// Arquivo: main.c | Autor: Bernardo Rodrigues Benato
// Programa independente para testar o modulo de albuns.
#include "albuns.h"

int main() {
    int opcao;
    carregarAlbunsCSV();
    do {
        printf("\n===== CDTECA PESSOAL: MODULO DE ALBUNS =====\n");
        printf("1. Colecao de albuns\n0. Encerrar\n");
        opcao = lerInt("Opcao: ");
        switch (opcao) {
            case 1: moduloAlbuns(); break;
            case 0: printf("Encerrando.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
    return 0;
}
