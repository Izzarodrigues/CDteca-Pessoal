// Arquivo: audicoes.h | Autor: Cassiani (Nome Completo e RGM)
// MODULO 4 - AUDICOES (modulo transacional) E RELATORIOS
#ifndef AUDICOES_H
#define AUDICOES_H

#include "utils.h"
#include "albuns.h"
#include "musicas.h"
#include "acervo.h"

struct Audicao {
    int id;
    int idMusica;
    int diaSemana;   // 1 = Dom ... 7 = Sab
    int segundos;    // tempo ouvido (calculado pela duracao da musica)
};

struct Audicao audicoes[MAX_AUDICOES];
int totalAudicoes = 0;

// Item usado nos rankings (copia dos dados: o vetor original nao e alterado)
struct ItemRank {
    int id;
    char nome[50];
    int reproducoes;
    int segundos;
};

void salvarAudicoesCSV() {
    FILE *arq = fopen("audicoes.csv", "w");
    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel gravar audicoes.csv!\n");
        return;
    }
    for (int i = 0; i < totalAudicoes; i++) {
        fprintf(arq, "%d;%d;%d;%d\n", audicoes[i].id, audicoes[i].idMusica,
                audicoes[i].diaSemana, audicoes[i].segundos);
    }
    fclose(arq);
}

void carregarAudicoesCSV() {
    FILE *arq = fopen("audicoes.csv", "r");
    if (arq == NULL) return;

    totalAudicoes = 0;
    while (totalAudicoes < MAX_AUDICOES &&
           fscanf(arq, "%d;%d;%d;%d\n",
                  &audicoes[totalAudicoes].id, &audicoes[totalAudicoes].idMusica,
                  &audicoes[totalAudicoes].diaSemana, &audicoes[totalAudicoes].segundos) == 4) {
        totalAudicoes++;
    }
    fclose(arq);
}

int buscarIndiceAudicao(int id) {
    for (int i = 0; i < totalAudicoes; i++) {
        if (audicoes[i].id == id) return i;
    }
    return -1;
}

// ID automatico (maior ID + 1): nunca repete
int proximoIdAudicao() {
    int maior = 0;
    for (int i = 0; i < totalAudicoes; i++) {
        if (audicoes[i].id > maior) maior = audicoes[i].id;
    }
    return maior + 1;
}

// Soma (+1) ou desfaz (-1) a contagem da musica e o uso do CD no acervo
void ajustarContadores(int idMusica, int delta) {
    int pm = buscarIndiceMusica(idMusica);
    if (pm == -1) return;
    musicas[pm].reproducoes += delta;
    if (musicas[pm].reproducoes < 0) musicas[pm].reproducoes = 0;

    int pa = buscarIndiceAcervo(musicas[pm].idAlbum);
    if (pa != -1) {
        acervo[pa].totalUsos += delta;
        if (acervo[pa].totalUsos < 0) acervo[pa].totalUsos = 0;
    }
}

// Indice do album de uma audicao (via musica), ou -1
int indiceAlbumDaAudicao(int i) {
    int pm = buscarIndiceMusica(audicoes[i].idMusica);
    if (pm == -1) return -1;
    return buscarIndiceAlbum(musicas[pm].idAlbum);
}

// REGRA DE NEGOCIO: valida musica -> album -> CD no acervo, calcula o tempo
// automaticamente, soma reproducao e da "baixa" na conservacao por desgaste
void registrarAudicao() {
    if (totalAudicoes >= MAX_AUDICOES) {
        printf("[ERRO] Historico de audicoes lotado!\n");
        return;
    }
    int idM = lerInt("\nID da musica ouvida: ");
    int pm = buscarIndiceMusica(idM);
    if (pm == -1) {
        printf("[ERRO] Musica nao encontrada!\n");
        return;
    }
    int pal = buscarIndiceAlbum(musicas[pm].idAlbum);
    if (pal == -1) {
        printf("[ERRO] O album dessa musica nao existe!\n");
        return;
    }
    int pac = buscarIndiceAcervo(musicas[pm].idAlbum);
    if (pac == -1) {
        printf("[ERRO] O CD de '%s' nao esta registrado no acervo!\n", albuns[pal].titulo);
        return;
    }
    int dia = lerInt("Dia da semana (1=Dom, 2=Seg, ... 7=Sab): ");
    if (dia < 1 || dia > 7) {
        printf("[ERRO] Dia invalido!\n");
        return;
    }

    audicoes[totalAudicoes].id = proximoIdAudicao();
    audicoes[totalAudicoes].idMusica = idM;
    audicoes[totalAudicoes].diaSemana = dia;
    audicoes[totalAudicoes].segundos = musicas[pm].duracaoSeg;
    totalAudicoes++;

    musicas[pm].reproducoes++;
    acervo[pac].totalUsos++;

    printf("[OK] Audicao registrada: '%s' (%s) - %d:%02d ouvidos.\n", musicas[pm].titulo,
           albuns[pal].titulo, musicas[pm].duracaoSeg / 60, musicas[pm].duracaoSeg % 60);

    if (acervo[pac].totalUsos % USOS_PARA_DESGASTE == 0) {
        if (degradarConservacao(pac)) {
            printf("[ATENCAO] O CD completou %d usos e a conservacao caiu para '%s'.\n",
                   acervo[pac].totalUsos, acervo[pac].conservacao);
        }
    }

    salvarAudicoesCSV();
    salvarMusicasCSV();
    salvarAcervoCSV();
}

void listarAudicoes() {
    printf("\n--- HISTORICO DE AUDICOES (%d itens) ---\n", totalAudicoes);
    for (int i = 0; i < totalAudicoes; i++) {
        int pm = buscarIndiceMusica(audicoes[i].idMusica);
        int pa = indiceAlbumDaAudicao(i);
        printf("ID: %-3d | %-28.28s | %-24.24s | %s | %d:%02d\n", audicoes[i].id,
               pm != -1 ? musicas[pm].titulo : "(musica removida)",
               pa != -1 ? albuns[pa].titulo : "(album removido)",
               NOMES_DIAS[audicoes[i].diaSemana - 1],
               audicoes[i].segundos / 60, audicoes[i].segundos % 60);
    }
}

// BUSCA TEXTUAL pelo nome da musica ou do album
void buscarAudicao() {
    char termo[50];
    int achou = 0;

    lerTexto("\nDigite parte do nome da musica ou do album: ", termo, 50);
    for (int i = 0; i < totalAudicoes; i++) {
        int pm = buscarIndiceMusica(audicoes[i].idMusica);
        int pa = indiceAlbumDaAudicao(i);
        if ((pm != -1 && contemTexto(musicas[pm].titulo, termo)) ||
            (pa != -1 && contemTexto(albuns[pa].titulo, termo))) {
            printf(" -> [%d] %s (%s) - %s\n", audicoes[i].id, musicas[pm].titulo,
                   albuns[pa].titulo, NOMES_DIAS[audicoes[i].diaSemana - 1]);
            achou++;
        }
    }
    if (!achou) printf("Nenhuma audicao encontrada para '%s'.\n", termo);
}

void editarAudicao() {
    int id = lerInt("\nID da audicao que deseja EDITAR: ");
    int pos = buscarIndiceAudicao(id);
    if (pos == -1) {
        printf("[ERRO] Audicao nao encontrada!\n");
        return;
    }

    int idM = lerInt("Novo ID da musica: ");
    int pm = buscarIndiceMusica(idM);
    if (pm == -1) {
        printf("[ERRO] Musica nao encontrada!\n");
        return;
    }
    if (buscarIndiceAcervo(musicas[pm].idAlbum) == -1) {
        printf("[ERRO] O CD dessa musica nao esta no acervo!\n");
        return;
    }
    int dia = lerInt("Novo dia da semana (1=Dom ... 7=Sab): ");
    if (dia < 1 || dia > 7) {
        printf("[ERRO] Dia invalido!\n");
        return;
    }

    ajustarContadores(audicoes[pos].idMusica, -1); // desfaz a antiga
    audicoes[pos].idMusica = idM;
    audicoes[pos].diaSemana = dia;
    audicoes[pos].segundos = musicas[pm].duracaoSeg;
    ajustarContadores(idM, +1);                    // aplica a nova

    salvarAudicoesCSV();
    salvarMusicasCSV();
    salvarAcervoCSV();
    printf("[OK] Audicao atualizada na memoria e nos arquivos CSV!\n");
}

void removerAudicao() {
    int id = lerInt("\nID da audicao que deseja REMOVER: ");
    int pos = buscarIndiceAudicao(id);
    if (pos == -1) {
        printf("[ERRO] Audicao nao encontrada!\n");
        return;
    }

    ajustarContadores(audicoes[pos].idMusica, -1);
    for (int j = pos; j < totalAudicoes - 1; j++) {
        audicoes[j] = audicoes[j + 1];
    }
    totalAudicoes--;

    salvarAudicoesCSV();
    salvarMusicasCSV();
    salvarAcervoCSV();
    printf("[OK] Audicao removida do sistema e dos CSVs!\n");
}

// Chamada pela remocao de musica/album
void removerAudicoesDaMusica(int idMusica) {
    int j = 0;
    for (int i = 0; i < totalAudicoes; i++) {
        if (audicoes[i].idMusica != idMusica) {
            audicoes[j] = audicoes[i];
            j++;
        }
    }
    totalAudicoes = j;
    salvarAudicoesCSV();
}

// ============================================================
// RELATORIOS ANALITICOS
// ============================================================

// 1. Tempo total de escuta por album (soma dos segundos das audicoes)
void relatorioTempoPorAlbum() {
    int seg[MAX] = {0};
    int total = 0;

    for (int i = 0; i < totalAudicoes; i++) {
        int pa = indiceAlbumDaAudicao(i);
        if (pa != -1) {
            seg[pa] += audicoes[i].segundos;
            total += audicoes[i].segundos;
        }
    }
    printf("\n--- TEMPO TOTAL DE ESCUTA POR ALBUM ---\n");
    for (int i = 0; i < totalAlbuns; i++) {
        printf("%-30.30s : ", albuns[i].titulo);
        imprimirTempo(seg[i]);
        printf("\n");
    }
    printf("\nTOTAL GERAL: ");
    imprimirTempo(total);
    printf("\n");
}

// 2. MATRIZ 2D: linhas = albuns, colunas = dias da semana
void montarMatriz(int matriz[][7]) {
    for (int i = 0; i < MAX; i++)
        for (int d = 0; d < 7; d++)
            matriz[i][d] = 0;

    for (int i = 0; i < totalAudicoes; i++) {
        int pa = indiceAlbumDaAudicao(i);
        if (pa != -1) matriz[pa][audicoes[i].diaSemana - 1]++;
    }
}

void relatorioMatriz() {
    int matriz[MAX][7];
    montarMatriz(matriz);

    printf("\n--- AUDICOES POR ALBUM x DIA DA SEMANA ---\n");
    printf("%-26s", "Album");
    for (int d = 0; d < 7; d++) printf("%5s", NOMES_DIAS[d]);
    printf("   Dia favorito\n");

    for (int i = 0; i < totalAlbuns; i++) {
        int melhor = 0;
        printf("%-26.26s", albuns[i].titulo);
        for (int d = 0; d < 7; d++) {
            printf("%5d", matriz[i][d]);
            if (matriz[i][d] > matriz[i][melhor]) melhor = d;
        }
        if (matriz[i][melhor] > 0) printf("   %s\n", NOMES_DIAS[melhor]);
        else printf("   -\n");
    }
}

// BUBBLE SORT em vetor de structs: do mais ouvido para o menos ouvido
void bubbleSortRank(struct ItemRank v[], int n) {
    struct ItemRank aux;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j].reproducoes < v[j + 1].reproducoes ||
                (v[j].reproducoes == v[j + 1].reproducoes && v[j].segundos < v[j + 1].segundos)) {
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

// 3. Ranking de albuns (ordena uma COPIA, sem bagunçar o vetor original)
void relatorioRankingAlbuns() {
    struct ItemRank rank[MAX];

    for (int i = 0; i < totalAlbuns; i++) {
        rank[i].id = albuns[i].id;
        strcpy(rank[i].nome, albuns[i].titulo);
        rank[i].reproducoes = 0;
        rank[i].segundos = 0;
    }
    for (int i = 0; i < totalAudicoes; i++) {
        int pa = indiceAlbumDaAudicao(i);
        if (pa != -1) {
            rank[pa].reproducoes++;
            rank[pa].segundos += audicoes[i].segundos;
        }
    }
    bubbleSortRank(rank, totalAlbuns);

    printf("\n--- RANKING DE ALBUNS MAIS OUVIDOS ---\n");
    for (int i = 0; i < totalAlbuns; i++) {
        printf("%2d. %-30.30s | %3d audicoes | ", i + 1, rank[i].nome, rank[i].reproducoes);
        imprimirTempo(rank[i].segundos);
        printf("\n");
    }
}

// 4. Ranking de musicas
void relatorioRankingMusicas() {
    struct ItemRank rank[MAX];

    for (int i = 0; i < totalMusicas; i++) {
        rank[i].id = musicas[i].id;
        strcpy(rank[i].nome, musicas[i].titulo);
        rank[i].reproducoes = musicas[i].reproducoes;
        rank[i].segundos = musicas[i].reproducoes * musicas[i].duracaoSeg;
    }
    bubbleSortRank(rank, totalMusicas);

    printf("\n--- RANKING DE MUSICAS MAIS OUVIDAS (Top 10) ---\n");
    for (int i = 0; i < totalMusicas && i < 10; i++) {
        printf("%2d. %-34.34s | %3d reproducoes\n", i + 1, rank[i].nome, rank[i].reproducoes);
    }
}

// 5. Estatisticas gerais com calculos reais
void relatorioEstatisticas() {
    int totalRep = 0, desgastados = 0, segTotal = 0, nGeneros = 0;
    char generos[MAX][30];
    int contGenero[MAX] = {0};

    for (int i = 0; i < totalMusicas; i++) totalRep += musicas[i].reproducoes;
    for (int i = 0; i < totalAcervo; i++) {
        if (strcmp(acervo[i].conservacao, "Desgastado") == 0) desgastados++;
    }
    for (int i = 0; i < totalAudicoes; i++) segTotal += audicoes[i].segundos;

    // gênero mais ouvido: acumula as audicoes por genero
    for (int i = 0; i < totalAudicoes; i++) {
        int pa = indiceAlbumDaAudicao(i);
        if (pa == -1) continue;
        int g;
        for (g = 0; g < nGeneros; g++) {
            if (strcmp(generos[g], albuns[pa].genero) == 0) break;
        }
        if (g == nGeneros) {
            strcpy(generos[nGeneros], albuns[pa].genero);
            nGeneros++;
        }
        contGenero[g]++;
    }

    printf("\n--- ESTATISTICAS GERAIS ---\n");
    printf("Total de audicoes registradas : %d\n", totalAudicoes);
    printf("Tempo total de escuta         : ");
    imprimirTempo(segTotal);
    printf("\n");
    if (totalMusicas > 0)
        printf("Media de reproducoes/musica   : %.2f\n", (float)totalRep / totalMusicas);
    if (totalAcervo > 0)
        printf("CDs desgastados               : %d de %d (%.1f%%)\n", desgastados, totalAcervo,
               100.0f * desgastados / totalAcervo);
    if (nGeneros > 0) {
        int melhor = 0;
        for (int g = 1; g < nGeneros; g++) {
            if (contGenero[g] > contGenero[melhor]) melhor = g;
        }
        printf("Genero mais ouvido            : %s (%d audicoes)\n", generos[melhor], contGenero[melhor]);
    }
}

void menuRelatorios() {
    int op;
    do {
        limparTela();
        printf("\n--- RELATORIOS ---\n");
        printf("1. Tempo de escuta por album\n2. Matriz album x dia da semana\n");
        printf("3. Ranking de albuns (Bubble Sort)\n4. Ranking de musicas (Bubble Sort)\n");
        printf("5. Estatisticas gerais\n0. Voltar\n");
        op = lerInt("Opcao: ");
        switch (op) {
            case 1: relatorioTempoPorAlbum(); break;
            case 2: relatorioMatriz(); break;
            case 3: relatorioRankingAlbuns(); break;
            case 4: relatorioRankingMusicas(); break;
            case 5: relatorioEstatisticas(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
        if (op != 0) pausar();
    } while (op != 0);
}

void moduloAudicoes() {
    int op;
    do {
        limparTela();
        printf("\n--- [MODULO 4: AUDICOES E RELATORIOS] ---\n");
        printf("1. Registrar audicao\n2. Historico de audicoes\n3. Buscar audicao\n");
        printf("4. Editar audicao\n5. Remover audicao\n6. Relatorios\n0. Voltar\n");
        op = lerInt("Opcao: ");
        switch (op) {
            case 1: registrarAudicao(); break;
            case 2: listarAudicoes(); break;
            case 3: buscarAudicao(); break;
            case 4: editarAudicao(); break;
            case 5: removerAudicao(); break;
            case 6: menuRelatorios(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
        if (op != 0 && op != 6) pausar();
    } while (op != 0);
}

#endif
