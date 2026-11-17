// Arquivo: albuns.h | Autor: Bernardo (Nome Completo e RGM)
// MODULO 1 - COLECAO DE ALBUNS
#ifndef ALBUNS_H
#define ALBUNS_H

#include "utils.h"

struct Album {
    int id;
    char titulo[50];
    char artista[50];
    char genero[30];
    int ano;
};

struct Album albuns[MAX];
int totalAlbuns = 0;

// Definidas nos modulos seguintes (usadas na remocao em cascata)
void removerMusicasDoAlbum(int idAlbum);
void removerAcervoDoAlbum(int idAlbum);

// PERSISTENCIA: regrava o vetor inteiro em albuns.csv ("w" zera o arquivo)
void salvarAlbunsCSV() {
    FILE *arq = fopen("albuns.csv", "w");
    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel gravar albuns.csv!\n");
        return;
    }
	int i;
    for ( i = 0; i < totalAlbuns; i++) {
        fprintf(arq, "%d;%s;%s;%s;%d\n", albuns[i].id, albuns[i].titulo,
                albuns[i].artista, albuns[i].genero, albuns[i].ano);
    }
    fclose(arq);
}

void carregarAlbunsCSV() {
    FILE *arq = fopen("albuns.csv", "r");
    if (arq == NULL) return;

    totalAlbuns = 0;
    while (totalAlbuns < MAX &&
           fscanf(arq, "%d;%49[^;];%49[^;];%29[^;];%d\n",
                  &albuns[totalAlbuns].id, albuns[totalAlbuns].titulo,
                  albuns[totalAlbuns].artista, albuns[totalAlbuns].genero,
                  &albuns[totalAlbuns].ano) == 5) {
        totalAlbuns++;
    }
    fclose(arq);
}

// Retorna a posicao do ID no vetor, ou -1 se nao existir
int buscarIndiceAlbum(int id) {
    for (int i = 0; i < totalAlbuns; i++) {
        if (albuns[i].id == id) return i;
    }
    return -1;
}

void cadastrarAlbum() {
    if (totalAlbuns >= MAX) {
        printf("[ERRO] Colecao lotada!\n");
        return;
    }
    int id = lerInt("\nID do novo album: ");
    if (id <= 0) {
        printf("[ERRO] O ID deve ser positivo!\n");
        return;
    }
    if (buscarIndiceAlbum(id) != -1) {
        printf("[ERRO] Ja existe um album com o ID %d!\n", id);
        return;
    }

    albuns[totalAlbuns].id = id;
    lerTexto("Titulo: ", albuns[totalAlbuns].titulo, 50);
    lerTexto("Artista: ", albuns[totalAlbuns].artista, 50);
    lerTexto("Genero musical: ", albuns[totalAlbuns].genero, 30);
    albuns[totalAlbuns].ano = lerInt("Ano de lancamento: ");

    totalAlbuns++;
    salvarAlbunsCSV();
    printf("[OK] Album salvo com sucesso em 'albuns.csv'!\n");
}

void listarAlbuns() {
    printf("\n--- COLECAO DE ALBUNS (%d itens) ---\n", totalAlbuns);
    for (int i = 0; i < totalAlbuns; i++) {
        printf("ID: %-3d | %-28.28s | %-22.22s | %-16.16s | %d\n",
               albuns[i].id, albuns[i].titulo, albuns[i].artista,
               albuns[i].genero, albuns[i].ano);
    }
}

// BUSCA TEXTUAL: por parte do titulo ou do artista
void buscarAlbum() {
    char termo[50];
    int achou = 0;

    lerTexto("\nDigite parte do titulo ou do artista: ", termo, 50);
    for (int i = 0; i < totalAlbuns; i++) {
        if (contemTexto(albuns[i].titulo, termo) || contemTexto(albuns[i].artista, termo)) {
            printf(" -> Encontrado: [%d] %s - %s (%s, %d)\n", albuns[i].id,
                   albuns[i].titulo, albuns[i].artista, albuns[i].genero, albuns[i].ano);
            achou++;
        }
    }
    if (!achou) printf("Nenhum album encontrado para '%s'.\n", termo);
}

void editarAlbum() {
    int id = lerInt("\nID do album que deseja EDITAR: ");
    int pos = buscarIndiceAlbum(id);
    if (pos == -1) {
        printf("[ERRO] Album nao encontrado!\n");
        return;
    }

    printf("Editando '%s' (%s)\n", albuns[pos].titulo, albuns[pos].artista);
    lerTexto("Novo titulo: ", albuns[pos].titulo, 50);
    lerTexto("Novo artista: ", albuns[pos].artista, 50);
    lerTexto("Novo genero: ", albuns[pos].genero, 30);
    albuns[pos].ano = lerInt("Novo ano: ");

    salvarAlbunsCSV();
    printf("[OK] Album atualizado na memoria e no arquivo CSV!\n");
}

// REMOCAO com cascata: apaga tambem musicas, registro do acervo e audicoes
void removerAlbum() {
    int id = lerInt("\nID do album que deseja REMOVER: ");
    int pos = buscarIndiceAlbum(id);
    if (pos == -1) {
        printf("[ERRO] Album nao encontrado!\n");
        return;
    }

    printf("Remover '%s' tambem apagara suas musicas, o CD no acervo e as audicoes.\n",
           albuns[pos].titulo);
    if (!confirmar("Confirmar remocao")) {
        printf("Remocao cancelada.\n");
        return;
    }

    removerMusicasDoAlbum(id);
    removerAcervoDoAlbum(id);

    for (int j = pos; j < totalAlbuns - 1; j++) {
        albuns[j] = albuns[j + 1]; // puxa a fila para cobrir o item apagado
    }
    totalAlbuns--;
    salvarAlbunsCSV();
    printf("[OK] Album removido do sistema e de todos os CSVs relacionados!\n");
}

void moduloAlbuns() {
    int op;
    do {
        limparTela();
        printf("\n--- [MODULO 1: COLECAO DE ALBUNS] ---\n");
        printf("1. Cadastrar\n2. Listar\n3. Buscar por titulo/artista\n");
        printf("4. Editar\n5. Remover\n0. Voltar\n");
        op = lerInt("Opcao: ");
        switch (op) {
            case 1: cadastrarAlbum(); break;
            case 2: listarAlbuns(); break;
            case 3: buscarAlbum(); break;
            case 4: editarAlbum(); break;
            case 5: removerAlbum(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
        if (op != 0) pausar();
    } while (op != 0);
}

#endif
