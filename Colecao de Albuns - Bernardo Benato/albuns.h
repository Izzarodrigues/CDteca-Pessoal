// Arquivo: albuns.h | Autor: Bernardo Rodrigues Benato
// Modulo de colecao de albuns da CDteca Pessoal.
#ifndef ALBUNS_H
#define ALBUNS_H

#include "utils.h"

struct Album {
    int id;
    char titulo[50];
    char artista[50];
    char genero[30];
    int ativo;
};

struct Album albuns[MAX];
int totalAlbuns = 0;

// Devolve a posicao do album ativo ou -1 quando nao encontra.
int buscarIndiceAlbum(int id) {
    int i;
    for (i = 0; i < totalAlbuns; i++) {
        if (albuns[i].id == id && albuns[i].ativo == 1) return i;
    }
    return -1;
}

// Grava todos os registros no CSV. O ponto e virgula separa os campos.
void salvarAlbunsCSV() {
    FILE *arq = fopen("albuns.csv", "w");
    int i;
    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel salvar albuns.csv.\n");
        return;
    }
    for (i = 0; i < totalAlbuns; i++) {
        fprintf(arq, "%d;%s;%s;%s;%d\n", albuns[i].id, albuns[i].titulo,
                albuns[i].artista, albuns[i].genero, albuns[i].ativo);
    }
    fclose(arq);
}

// Le os registros ao abrir o programa. Cada linha deve ter cinco campos.
void carregarAlbunsCSV() {
    FILE *arq = fopen("albuns.csv", "r");
    if (arq == NULL) return;
    totalAlbuns = 0;
    while (totalAlbuns < MAX &&
           fscanf(arq, "%d;%49[^;];%49[^;];%29[^;];%d\n",
                  &albuns[totalAlbuns].id,
                  albuns[totalAlbuns].titulo,
                  albuns[totalAlbuns].artista,
                  albuns[totalAlbuns].genero,
                  &albuns[totalAlbuns].ativo) == 5) {
        totalAlbuns++;
    }
    fclose(arq);
}

// Retorna 1 se existe um ID, inclusive inativo. Evita reaproveitamento ambiguo.
int idAlbumJaUsado(int id) {
    int i;
    for (i = 0; i < totalAlbuns; i++) {
        if (albuns[i].id == id) return 1;
    }
    return 0;
}

// Autor: Bernardo Rodrigues Benato - Cadastro.
void cadastrarAlbum() {
    int id;
    if (totalAlbuns >= MAX) {
        printf("[ERRO] Limite de 50 albuns atingido.\n");
        return;
    }
    id = lerInt("ID do album: ");
    if (id <= 0 || idAlbumJaUsado(id)) {
        printf("[ERRO] ID invalido ou ja utilizado.\n");
        return;
    }
    albuns[totalAlbuns].id = id;
    lerTexto("Titulo: ", albuns[totalAlbuns].titulo, 50);
    lerTexto("Artista: ", albuns[totalAlbuns].artista, 50);
    lerTexto("Genero: ", albuns[totalAlbuns].genero, 30);
    albuns[totalAlbuns].ativo = 1;
    totalAlbuns++;
    salvarAlbunsCSV();
    printf("Album cadastrado!\n");
}

// Autor: Bernardo Rodrigues Benato - Listagem.
void listarAlbuns() {
    int i, achou = 0;
    for (i = 0; i < totalAlbuns; i++) {
        if (albuns[i].ativo == 1) {
            printf("ID: %d | Titulo: %s | Artista: %s | Genero: %s\n",
                   albuns[i].id, albuns[i].titulo,
                   albuns[i].artista, albuns[i].genero);
            achou++;
        }
    }
    if (achou == 0) printf("Nenhum album ativo cadastrado.\n");
}

// Autor: Bernardo Rodrigues Benato - Busca textual por titulo ou artista.
void buscarAlbum() {
    char termo[50];
    int i, achou = 0;
    lerTexto("Parte do titulo ou artista: ", termo, 50);
    for (i = 0; i < totalAlbuns; i++) {
        if (albuns[i].ativo == 1 &&
            (strstr(albuns[i].titulo, termo) != NULL ||
             strstr(albuns[i].artista, termo) != NULL)) {
            printf("ID: %d | %s - %s\n", albuns[i].id,
                   albuns[i].titulo, albuns[i].artista);
            achou++;
        }
    }
    if (achou == 0) printf("Nenhum album encontrado.\n");
}

// Autor: Bernardo Rodrigues Benato - Edicao refletida no CSV.
void editarAlbum() {
    int id = lerInt("ID do album para editar: ");
    int pos = buscarIndiceAlbum(id);
    if (pos == -1) {
        printf("Album nao encontrado.\n");
        return;
    }
    lerTexto("Novo titulo: ", albuns[pos].titulo, 50);
    lerTexto("Novo artista: ", albuns[pos].artista, 50);
    lerTexto("Novo genero: ", albuns[pos].genero, 30);
    salvarAlbunsCSV();
    printf("Album editado!\n");
}

// Autor: Bernardo Rodrigues Benato - Remocao logica persistida no CSV.
void removerAlbum() {
    int id = lerInt("ID do album para remover: ");
    int pos = buscarIndiceAlbum(id);
    if (pos == -1) {
        printf("Album nao encontrado.\n");
        return;
    }
    albuns[pos].ativo = 0;
    salvarAlbunsCSV();
    printf("Album removido logicamente!\n");
}

// Autor: Bernardo Rodrigues Benato - Submenu principal de albuns.
void moduloAlbuns() {
    int opcao;
    do {
        printf("\n--- COLECAO DE ALBUNS ---\n");
        printf("1. Cadastrar\n2. Listar\n3. Buscar por texto\n");
        printf("4. Editar\n5. Remover\n0. Voltar\n");
        opcao = lerInt("Opcao: ");
        switch (opcao) {
            case 1: cadastrarAlbum(); break;
            case 2: listarAlbuns(); break;
            case 3: buscarAlbum(); break;
            case 4: editarAlbum(); break;
            case 5: removerAlbum(); break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

#endif
