// Arquivo: acervo.h | Autor: Izadora (Nome Completo e RGM)
// MODULO 3 - ACERVO E CONSERVACAO DOS CDS
#ifndef ACERVO_H
#define ACERVO_H

#include "utils.h"
#include "albuns.h"
#include "musicas.h"

struct Acervo {
    int idAlbum;
    char tipo[30];
    char conservacao[30];
    int totalUsos;
};

struct Acervo acervo[MAX];
int totalAcervo = 0;

void salvarAcervoCSV() {
    FILE *arq = fopen("acervo.csv", "w");
    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel gravar acervo.csv!\n");
        return;
    }
    for (int i = 0; i < totalAcervo; i++) {
        fprintf(arq, "%d;%s;%s;%d\n", acervo[i].idAlbum, acervo[i].tipo,
                acervo[i].conservacao, acervo[i].totalUsos);
    }
    fclose(arq);
}

void carregarAcervoCSV() {
    FILE *arq = fopen("acervo.csv", "r");
    if (arq == NULL) return;

    totalAcervo = 0;
    while (totalAcervo < MAX &&
           fscanf(arq, "%d;%29[^;];%29[^;];%d\n",
                  &acervo[totalAcervo].idAlbum, acervo[totalAcervo].tipo,
                  acervo[totalAcervo].conservacao, &acervo[totalAcervo].totalUsos) == 4) {
        totalAcervo++;
    }
    fclose(arq);
}

// O acervo e identificado pelo ID do album (um CD por album)
int buscarIndiceAcervo(int idAlbum) {
    for (int i = 0; i < totalAcervo; i++) {
        if (acervo[i].idAlbum == idAlbum) return i;
    }
    return -1;
}

// Menu de niveis: evita erro de digitacao e garante que o strcmp funcione
void escolherConservacao(char *destino) {
    int n;
    printf("Estado de conservacao:\n");
    for (int i = 0; i < 4; i++) printf("  %d. %s\n", i + 1, NIVEIS_CONSERVACAO[i]);
    do {
        n = lerInt("Escolha (1-4): ");
    } while (n < 1 || n > 4);
    strcpy(destino, NIVEIS_CONSERVACAO[n - 1]);
}

// BAIXA AUTOMATICA: desce um nivel (Novo > Bom > Regular > Desgastado)
// Retorna 1 se mudou, 0 se ja estava no ultimo nivel
int degradarConservacao(int pos) {
    for (int i = 0; i < 3; i++) {
        if (strcmp(acervo[pos].conservacao, NIVEIS_CONSERVACAO[i]) == 0) {
            strcpy(acervo[pos].conservacao, NIVEIS_CONSERVACAO[i + 1]);
            return 1;
        }
    }
    return 0;
}

void registrarCD() {
    if (totalAcervo >= MAX) {
        printf("[ERRO] Acervo lotado!\n");
        return;
    }
    int id = lerInt("\nID do album do CD: ");
    if (buscarIndiceAlbum(id) == -1) {
        printf("[ERRO] Album nao encontrado! Cadastre o album primeiro.\n");
        return;
    }
    if (buscarIndiceAcervo(id) != -1) {
        printf("[ERRO] Esse album ja esta registrado no acervo!\n");
        return;
    }

    acervo[totalAcervo].idAlbum = id;
    lerTexto("Tipo de midia (CD, CD duplo, etc.): ", acervo[totalAcervo].tipo, 30);
    escolherConservacao(acervo[totalAcervo].conservacao);
    acervo[totalAcervo].totalUsos = 0;

    totalAcervo++;
    salvarAcervoCSV();
    printf("[OK] CD registrado com sucesso em 'acervo.csv'!\n");
}

void listarAcervo() {
    printf("\n--- ACERVO DE CDS (%d itens) ---\n", totalAcervo);
    for (int i = 0; i < totalAcervo; i++) {
        int pa = buscarIndiceAlbum(acervo[i].idAlbum);
        printf("Album %-3d | %-28.28s | %-18.18s | %-10s | %d usos\n",
               acervo[i].idAlbum, pa != -1 ? albuns[pa].titulo : "(album removido)",
               acervo[i].tipo, acervo[i].conservacao, acervo[i].totalUsos);
    }
}

// BUSCA TEXTUAL pelo titulo/artista do album do CD
void buscarCD() {
    char termo[50];
    int achou = 0;

    lerTexto("\nDigite parte do titulo ou artista do album: ", termo, 50);
    for (int i = 0; i < totalAcervo; i++) {
        int pa = buscarIndiceAlbum(acervo[i].idAlbum);
        if (pa != -1 && (contemTexto(albuns[pa].titulo, termo) ||
                         contemTexto(albuns[pa].artista, termo))) {
            printf(" -> Encontrado: %s - %s | %s | %s | %d usos\n", albuns[pa].titulo,
                   albuns[pa].artista, acervo[i].tipo, acervo[i].conservacao,
                   acervo[i].totalUsos);
            achou++;
        }
    }
    if (!achou) printf("Nenhum CD encontrado no acervo para '%s'.\n", termo);
}

void editarCD() {
    int id = lerInt("\nID do album do CD que deseja EDITAR: ");
    int pos = buscarIndiceAcervo(id);
    if (pos == -1) {
        printf("[ERRO] CD nao encontrado no acervo!\n");
        return;
    }

    printf("Editando CD (atual: %s / %s)\n", acervo[pos].tipo, acervo[pos].conservacao);
    lerTexto("Novo tipo de midia: ", acervo[pos].tipo, 30);
    escolherConservacao(acervo[pos].conservacao);

    salvarAcervoCSV();
    printf("[OK] CD atualizado na memoria e no arquivo CSV!\n");
}

void removerCD() {
    int id = lerInt("\nID do album do CD que deseja REMOVER do acervo: ");
    int pos = buscarIndiceAcervo(id);
    if (pos == -1) {
        printf("[ERRO] CD nao encontrado no acervo!\n");
        return;
    }

    for (int j = pos; j < totalAcervo - 1; j++) {
        acervo[j] = acervo[j + 1];
    }
    totalAcervo--;
    salvarAcervoCSV();
    printf("[OK] CD removido do acervo e do CSV!\n");
}

// Chamada pela remocao de album
void removerAcervoDoAlbum(int idAlbum) {
    int pos = buscarIndiceAcervo(idAlbum);
    if (pos == -1) return;
    for (int j = pos; j < totalAcervo - 1; j++) {
        acervo[j] = acervo[j + 1];
    }
    totalAcervo--;
    salvarAcervoCSV();
}

void moduloAcervo() {
    int op;
    do {
        limparTela();
        printf("\n--- [MODULO 3: ACERVO E CONSERVACAO] ---\n");
        printf("1. Registrar CD\n2. Listar acervo\n3. Buscar por titulo/artista\n");
        printf("4. Editar CD\n5. Remover CD\n0. Voltar\n");
        op = lerInt("Opcao: ");
        switch (op) {
            case 1: registrarCD(); break;
            case 2: listarAcervo(); break;
            case 3: buscarCD(); break;
            case 4: editarCD(); break;
            case 5: removerCD(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
        if (op != 0) pausar();
    } while (op != 0);
}

#endif
