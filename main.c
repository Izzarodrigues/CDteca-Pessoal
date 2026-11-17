// CDTECA PESSOAL - Checkpoint 2
// Compilar: gcc main.c -o cdteca     (rodar na mesma pasta dos arquivos .csv)
#include <stdio.h>
#include <locale.h>

#include "utils.h"
#include "albuns.h"     // Bernardo
#include "musicas.h"    // Kamila   (usa albuns.h)
#include "acervo.h"     // Izadora  (usa albuns.h e musicas.h)
#include "audicoes.h"   // Cassiani (usa todos os anteriores)

void cabecalho() {
    printf("\n====================================\n");
    printf("        CDTECA PESSOAL\n");
    printf("====================================\n");
}

int main() {
#ifdef _WIN32
    setlocale(LC_ALL, "Portuguese");
#else
    setlocale(LC_ALL, "pt_BR.UTF-8");
#endif

    // carrega os dados dos 4 arquivos CSV ao abrir o programa
    carregarAlbunsCSV();
    carregarMusicasCSV();
    carregarAcervoCSV();
    carregarAudicoesCSV();

    int op;
    do {
        limparTela();
        cabecalho();
        printf("1. Colecao de albuns\n");
        printf("2. Catalogo de musicas\n");
        printf("3. Acervo e conservacao\n");
        printf("4. Audicoes e relatorios\n");
        printf("0. Encerrar sistema\n");
        op = lerInt("Escolha uma opcao: ");

        switch (op) {
            case 1: moduloAlbuns(); break;
            case 2: moduloMusicas(); break;
            case 3: moduloAcervo(); break;
            case 4: moduloAudicoes(); break;
            case 0: printf("Encerrando a CDteca Pessoal!\n"); break;
            default: printf("Opcao invalida!\n"); pausar();
        }
    } while (op != 0);

    return 0;
}
