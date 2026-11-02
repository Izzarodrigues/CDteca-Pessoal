#include <stdio.h>

// Autor: Bernardo Rodrigues Benato RGM: 47415487 - Colecao de Albuns
struct Album {
    int id;
    char titulo[50];
    char artista[50];
    char genero[30];
    int ativo;
};
struct Album albuns[50];
int totalAlbuns = 0;

// Autor: Kamila de Cassia Marcon - RGM: 47123141- Catalogo de Musicas
struct Musica {
    int id;
    int idAlbum;
    char titulo[50];
    int reproducoes;
    int ativo;
};
struct Musica musicas[50];
int totalMusicas = 0;

// Autor: Izadora Maria Rodrigues - RGM:47728345 Acervo e Conservacao
struct Acervo {
    int idAlbum;
    char tipo[30];
    char conservacao[30];
    int ativo;
};
struct Acervo acervo[50];
int totalAcervo = 0;

// Autor: Cassiani Teixeira de Paula - RGM: 46620494 - Historico de Audicoes
struct Audicao {
    int idMusica;
    int quantidade;
    char data[11];
    int ativo;
};
struct Audicao audicoes[50];
int totalAudicoes = 0;

// Autor: Bernardo Rodrigues Benato - Busca auxiliar de albuns
int buscarAlbum(int id) {
    int i;
    for (i = 0; i < totalAlbuns; i++) {
        if (albuns[i].id == id && albuns[i].ativo == 1) {
            return i;
        }
    }
    return -1;
}

// Autor: Bernardo Rodrigues Benato - Modulo de albuns
void moduloAlbuns() {
    int opcao, id, i;
    do {
        printf("\n--- COLECAO DE ALBUNS ---\n");
        printf("1. Cadastrar album\n");
        printf("2. Listar albuns\n");
        printf("3. Buscar album\n");
        printf("4. Editar album\n");
        printf("5. Remover album\n");
        printf("0. Voltar\nOpcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                if (totalAlbuns >= 50) {
                    printf("Limite de 50 albuns atingido.\n");
                    break;
                }
                printf("ID: ");
                scanf("%d", &id);
                if (buscarAlbum(id) != -1) {
                    printf("Este ID ja esta em uso.\n");
                    break;
                }
                albuns[totalAlbuns].id = id;
                printf("Titulo: ");
                scanf("%49s", albuns[totalAlbuns].titulo);
                printf("Artista: ");
                scanf("%49s", albuns[totalAlbuns].artista);
                printf("Genero: ");
                scanf("%29s", albuns[totalAlbuns].genero);
                albuns[totalAlbuns].ativo = 1;
                totalAlbuns++;
                printf("Album cadastrado.\n");
                break;
            case 2:
                for (i = 0; i < totalAlbuns; i++) {
                    if (albuns[i].ativo == 1) {
                        printf("ID: %d | Titulo: %s | Artista: %s | Genero: %s\n",
                               albuns[i].id, albuns[i].titulo,
                               albuns[i].artista, albuns[i].genero);
                    }
                }
                break;
            case 3:
                printf("ID: ");
                scanf("%d", &id);
                i = buscarAlbum(id);
                if (i == -1) printf("Album nao encontrado.\n");
                else printf("Titulo: %s | Artista: %s\n",
                            albuns[i].titulo, albuns[i].artista);
                break;
            case 4:
                printf("[Em construcao] Edicao de album.\n");
                break;
            case 5:
                printf("ID: ");
                scanf("%d", &id);
                i = buscarAlbum(id);
                if (i == -1) printf("Album nao encontrado.\n");
                else {
                    albuns[i].ativo = 0;
                    printf("Album removido.\n");
                }
                break;
            case 0:
                printf("Voltando ao menu principal.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

// Autor: Kamila - Modulo de musicas
void moduloMusicas() {
    int opcao;
    do {
        printf("\n--- CATALOGO DE MUSICAS ---\n");
        printf("1. Cadastrar musica\n2. Listar / buscar musicas\n");
        printf("3. Editar musica\n4. Remover musica\n");
        printf("0. Voltar\nOpcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: printf("[Em construcao] Cadastro de musica.\n"); break;
            case 2: printf("[Em construcao] Consulta de musicas.\n"); break;
            case 3: printf("[Em construcao] Edicao de musica.\n"); break;
            case 4: printf("[Em construcao] Remocao de musica.\n"); break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

// Autor: Izadora - Modulo de acervo
void moduloAcervo() {
    int opcao;
    do {
        printf("\n--- ACERVO E CONSERVACAO ---\n");
        printf("1. Registrar CD\n2. Listar / buscar CDs\n");
        printf("3. Editar conservacao\n4. Remover CD\n");
        printf("0. Voltar\nOpcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: printf("[Em construcao] Registro de CD.\n"); break;
            case 2: printf("[Em construcao] Consulta de CDs.\n"); break;
            case 3: printf("[Em construcao] Edicao de conservacao.\n"); break;
            case 4: printf("[Em construcao] Remocao de CD.\n"); break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

// Autor: Cassiani - Modulo de audicoes e relatorios
void moduloAudicoes() {
    int opcao;
    do {
        printf("\n--- AUDICOES E RELATORIOS ---\n");
        printf("1. Registrar audicao\n2. Listar / buscar audicoes\n");
        printf("3. Editar audicao\n4. Remover audicao\n");
        printf("5. Musica mais ouvida\n6. Album mais ouvido\n");
        printf("0. Voltar\nOpcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: printf("[Em construcao] Registro de audicao.\n"); break;
            case 2: printf("[Em construcao] Consulta de audicoes.\n"); break;
            case 3: printf("[Em construcao] Edicao de audicao.\n"); break;
            case 4: printf("[Em construcao] Remocao de audicao.\n"); break;
            case 5: printf("[Em construcao] Relatorio de musica mais ouvida.\n"); break;
            case 6: printf("[Em construcao] Relatorio de album mais ouvido.\n"); break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

// Autor: Equipe CDteca Pessoal - Menu principal
int main() {
    int opcao;
    do {
        printf("\n========== CDTECA PESSOAL ==========\n");
        printf("1. Colecao de albuns\n2. Catalogo de musicas\n");
        printf("3. Organizacao do acervo\n4. Audicoes e relatorios\n");
        printf("0. Encerrar\nOpcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: moduloAlbuns(); break;
            case 2: moduloMusicas(); break;
            case 3: moduloAcervo(); break;
            case 4: moduloAudicoes(); break;
            case 0: printf("Encerrando a CDteca.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
    return 0;
}
