// Arquivo: musicas.h | Autor: Kamila (Nome Completo e RGM)
// MODULO 2 - CATALOGO DE MUSICAS
#ifndef MUSICAS_H
#define MUSICAS_H

#include "utils.h"
#include "albuns.h"

struct Musica {
    int id;
    int idAlbum;
    char titulo[50];
    int duracaoSeg;
    int reproducoes;
};

struct Musica musicas[MAX];
int totalMusicas = 0;

// Definida em audicoes.h (usada na remocao em cascata)
void removerAudicoesDaMusica(int idMusica);

void salvarMusicasCSV() {
    FILE *arq = fopen("musicas.csv", "w");
    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel gravar musicas.csv!\n");
        return;
    }
    for (int i = 0; i < totalMusicas; i++) {
        fprintf(arq, "%d;%d;%s;%d;%d\n", musicas[i].id, musicas[i].idAlbum,
                musicas[i].titulo, musicas[i].duracaoSeg, musicas[i].reproducoes);
    }
    fclose(arq);
}

void carregarMusicasCSV() {
    FILE *arq = fopen("musicas.csv", "r");
    if (arq == NULL) return;

    totalMusicas = 0;
    while (totalMusicas < MAX &&
           fscanf(arq, "%d;%d;%49[^;];%d;%d\n",
                  &musicas[totalMusicas].id, &musicas[totalMusicas].idAlbum,
                  musicas[totalMusicas].titulo, &musicas[totalMusicas].duracaoSeg,
                  &musicas[totalMusicas].reproducoes) == 5) {
        totalMusicas++;
    }
    fclose(arq);
}

int buscarIndiceMusica(int id) {
    for (int i = 0; i < totalMusicas; i++) {
        if (musicas[i].id == id) return i;
    }
    return -1;
}

// Remove da memoria (puxa a fila), sem mexer no arquivo
void apagarMusicaNoVetor(int pos) {
    for (int j = pos; j < totalMusicas - 1; j++) {
        musicas[j] = musicas[j + 1];
    }
    totalMusicas--;
}

void cadastrarMusica() {
    if (totalMusicas >= MAX) {
        printf("[ERRO] Catalogo lotado!\n");
        return;
    }
    int id = lerInt("\nID da nova musica: ");
    if (id <= 0) {
        printf("[ERRO] O ID deve ser positivo!\n");
        return;
    }
    if (buscarIndiceMusica(id) != -1) {
        printf("[ERRO] Ja existe uma musica com o ID %d!\n", id);
        return;
    }
    int idAlbum = lerInt("ID do album: ");
    if (buscarIndiceAlbum(idAlbum) == -1) {
        printf("[ERRO] Album nao encontrado! Cadastre o album primeiro.\n");
        return;
    }

    musicas[totalMusicas].id = id;
    musicas[totalMusicas].idAlbum = idAlbum;
    lerTexto("Nome da musica: ", musicas[totalMusicas].titulo, 50);
    musicas[totalMusicas].duracaoSeg = lerInt("Duracao em segundos: ");
    if (musicas[totalMusicas].duracaoSeg <= 0) {
        printf("[ERRO] A duracao deve ser maior que zero!\n");
        return;
    }
    musicas[totalMusicas].reproducoes = 0;

    totalMusicas++;
    salvarMusicasCSV();
    printf("[OK] Musica salva com sucesso em 'musicas.csv'!\n");
}

void listarMusicas() {
    printf("\n--- CATALOGO DE MUSICAS (%d itens) ---\n", totalMusicas);
    for (int i = 0; i < totalMusicas; i++) {
        int pa = buscarIndiceAlbum(musicas[i].idAlbum);
        printf("ID: %-3d | %-30.30s | %-24.24s | %d:%02d | %d reproducoes\n",
               musicas[i].id, musicas[i].titulo,
               pa != -1 ? albuns[pa].titulo : "(album removido)",
               musicas[i].duracaoSeg / 60, musicas[i].duracaoSeg % 60,
               musicas[i].reproducoes);
    }
}

// BUSCA TEXTUAL (sem diferenciar maiusculas/minusculas)
void buscarMusica() {
    char termo[50];
    int achou = 0;

    lerTexto("\nDigite parte do nome da musica: ", termo, 50);
    for (int i = 0; i < totalMusicas; i++) {
        if (contemTexto(musicas[i].titulo, termo)) {
            printf(" -> Encontrada: [%d] %s (%d:%02d) - %d reproducoes\n",
                   musicas[i].id, musicas[i].titulo, musicas[i].duracaoSeg / 60,
                   musicas[i].duracaoSeg % 60, musicas[i].reproducoes);
            achou++;
        }
    }
    if (!achou) printf("Nenhuma musica encontrada para '%s'.\n", termo);
}

void editarMusica() {
    int id = lerInt("\nID da musica que deseja EDITAR: ");
    int pos = buscarIndiceMusica(id);
    if (pos == -1) {
        printf("[ERRO] Musica nao encontrada!\n");
        return;
    }

    printf("Editando '%s' (para trocar de album, remova e cadastre de novo)\n", musicas[pos].titulo);
    lerTexto("Novo nome: ", musicas[pos].titulo, 50);
    int dur = lerInt("Nova duracao em segundos: ");
    if (dur <= 0) {
        printf("[ERRO] A duracao deve ser maior que zero! Duracao mantida.\n");
    } else {
        musicas[pos].duracaoSeg = dur;
    }

    salvarMusicasCSV();
    printf("[OK] Musica atualizada na memoria e no arquivo CSV!\n");
}

void removerMusica() {
    int id = lerInt("\nID da musica que deseja REMOVER: ");
    int pos = buscarIndiceMusica(id);
    if (pos == -1) {
        printf("[ERRO] Musica nao encontrada!\n");
        return;
    }
    if (!confirmar("Isso tambem apaga as audicoes dessa musica. Confirmar")) {
        printf("Remocao cancelada.\n");
        return;
    }

    removerAudicoesDaMusica(id);
    apagarMusicaNoVetor(pos);
    salvarMusicasCSV();
    printf("[OK] Musica removida do sistema e do CSV!\n");
}

// Chamada pela remocao de album: apaga todas as musicas dele
void removerMusicasDoAlbum(int idAlbum) {
    for (int i = totalMusicas - 1; i >= 0; i--) {
        if (musicas[i].idAlbum == idAlbum) {
            removerAudicoesDaMusica(musicas[i].id);
            apagarMusicaNoVetor(i);
        }
    }
    salvarMusicasCSV();
}

void moduloMusicas() {
    int op;
    do {
        limparTela();
        printf("\n--- [MODULO 2: CATALOGO DE MUSICAS] ---\n");
        printf("1. Cadastrar\n2. Listar\n3. Buscar por nome\n");
        printf("4. Editar\n5. Remover\n0. Voltar\n");
        op = lerInt("Opcao: ");
        switch (op) {
            case 1: cadastrarMusica(); break;
            case 2: listarMusicas(); break;
            case 3: buscarMusica(); break;
            case 4: editarMusica(); break;
            case 5: removerMusica(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
        if (op != 0) pausar();
    } while (op != 0);
}

#endif
