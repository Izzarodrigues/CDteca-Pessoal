#include <stdio.h>
#include <string.h>

// INTEGRANTE BERNARDO - COLECAO DE ALBUNS
struct Album {
    int id;
    char titulo[50];
    char artista[50];
    char genero[30];
    int ativo;
};

struct Album albuns[50];
int totalAlbuns = 0;


// KAMILA - MUSICAS
struct Musica {
    int id;
    int idAlbum;
    char titulo[50];
    int reproducoes;
    int ativo;
};

struct Musica musicas[50];
int totalMusicas = 0;


// IZADORA - ACERVO E CONSERVACAO DOS CDS
struct Acervo {
    int idAlbum;
    char tipo[30];
    char conservacao[30];
};

struct Acervo acervo[50];
int totalAcervo = 0;


// CASSIANI - HISTORICO DE AUDICOES
struct Audicao {
    int idMusica;
    int quantidade;
};

struct Audicao audicoes[50];
int totalAudicoes = 0;


// ============================================================
// FUNCOES AUXILIARES TODOS OS INTEGRANTES
// ============================================================

int buscarAlbum(int id) {
    int i;

    for (i = 0; i < totalAlbuns; i++) {
        if (albuns[i].id == id && albuns[i].ativo == 1)
            return i;
    }

    return -1;
}

int buscarMusica(int id) {
    int i;

    for (i = 0; i < totalMusicas; i++) {
        if (musicas[i].id == id && musicas[i].ativo == 1)
            return i;
    }

    return -1;
}

void cabecalho() {
    printf("\n====================================\n");
    printf("        CDTECA PESSOAL\n");
    printf("====================================\n");
}


// ============================================================
// MODULO 1 - COLECAO DE ALBUNS
// BERNARDO
// ============================================================

void moduloAlbuns() {
    int op, id, i;

    do {
        printf("\n--- MODULO 1: COLECAO DE ALBUNS ---\n");
        printf("1. Cadastrar album\n");
        printf("2. Listar albuns\n");
        printf("3. Buscar album\n");
        printf("4. Remover album\n");
        printf("0. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                if (totalAlbuns >= 50) {
                    printf("Limite de albuns atingido!\n");
                    break;
                }

                printf("ID: ");
                scanf("%d", &id);

                if (buscarAlbum(id) != -1) {
                    printf("ID ja cadastrado!\n");
                    break;
                }

                albuns[totalAlbuns].id = id;

                printf("Titulo: ");
                scanf(" %49[^\n]", albuns[totalAlbuns].titulo);

                printf("Artista: ");
                scanf(" %49[^\n]", albuns[totalAlbuns].artista);

                printf("Genero musical: ");
                scanf(" %29[^\n]", albuns[totalAlbuns].genero);

                albuns[totalAlbuns].ativo = 1;
                totalAlbuns++;

                printf("Album cadastrado!\n");
                break;

            case 2:
                for (i = 0; i < totalAlbuns; i++) {
                    if (albuns[i].ativo == 1) {
                        printf("\nID: %d\n", albuns[i].id);
                        printf("Titulo: %s\n", albuns[i].titulo);
                        printf("Artista: %s\n", albuns[i].artista);
                        printf("Genero: %s\n", albuns[i].genero);
                    }
                }
                break;

            case 3:
                printf("ID do album: ");
                scanf("%d", &id);

                i = buscarAlbum(id);

                if (i == -1) {
                    printf("Album nao encontrado!\n");
                } else {
                    printf("Titulo: %s\n", albuns[i].titulo);
                    printf("Artista: %s\n", albuns[i].artista);
                }
                break;

            case 4:
                printf("ID do album: ");
                scanf("%d", &id);

                i = buscarAlbum(id);

                if (i == -1) {
                    printf("Album nao encontrado!\n");
                } else {
                    albuns[i].ativo = 0;
                    printf("Album removido!\n");
                }
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (op != 0);
}


// ============================================================
// MODULO 2 - CATALOGO DE MUSICAS
// KAMILA
// ============================================================

void moduloMusicas() {
    int op, id, idAlbum, i;

    do {
        printf("\n--- MODULO 2: CATALOGO DE MUSICAS ---\n");
        printf("1. Cadastrar musica\n");
        printf("2. Listar musicas\n");
        printf("3. Remover musica\n");
        printf("0. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                if (totalMusicas >= 50) {
                    printf("Limite de musicas atingido!\n");
                    break;
                }

                printf("ID da musica: ");
                scanf("%d", &id);

                if (buscarMusica(id) != -1) {
                    printf("ID ja cadastrado!\n");
                    break;
                }

                printf("ID do album: ");
                scanf("%d", &idAlbum);

                if (buscarAlbum(idAlbum) == -1) {
                    printf("Cadastre o album primeiro!\n");
                    break;
                }

                musicas[totalMusicas].id = id;
                musicas[totalMusicas].idAlbum = idAlbum;

                printf("Nome da musica: ");
                scanf(" %49[^\n]", musicas[totalMusicas].titulo);

                musicas[totalMusicas].reproducoes = 0;
                musicas[totalMusicas].ativo = 1;

                totalMusicas++;
                printf("Musica cadastrada!\n");
                break;

            case 2:
                for (i = 0; i < totalMusicas; i++) {
                    if (musicas[i].ativo == 1) {
                        printf("\nID: %d\n", musicas[i].id);
                        printf("Musica: %s\n", musicas[i].titulo);
                        printf("Reproducoes: %d\n",
                               musicas[i].reproducoes);
                    }
                }
                break;

            case 3:
                printf("ID da musica: ");
                scanf("%d", &id);

                i = buscarMusica(id);

                if (i == -1) {
                    printf("Musica nao encontrada!\n");
                } else {
                    musicas[i].ativo = 0;
                    printf("Musica removida!\n");
                }
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (op != 0);
}


// ============================================================
// MODULO 3 - ORGANIZACAO E CONSERVACAO DO ACERVO
// IZADORA
// ============================================================

void moduloAcervo() {
    int op, id, i;

    do {
        printf("\n--- MODULO 3: ORGANIZACAO DO ACERVO ---\n");
        printf("1. Registrar CD\n");
        printf("2. Consultar acervo\n");
        printf("3. Atualizar conservacao\n");
        printf("0. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                if (totalAcervo >= 50) {
                    printf("Limite do acervo atingido!\n");
                    break;
                }

                printf("ID do album: ");
                scanf("%d", &id);

                if (buscarAlbum(id) == -1) {
                    printf("Album nao encontrado!\n");
                    break;
                }

                for (i = 0; i < totalAcervo; i++) {
                    if (acervo[i].idAlbum == id) {
                        printf("Album ja registrado no acervo!\n");
                        break;
                    }
                }

                if (i < totalAcervo)
                    break;

                acervo[totalAcervo].idAlbum = id;

                printf("Tipo de midia (CD, CD duplo etc.): ");
                scanf(" %29[^\n]", acervo[totalAcervo].tipo);

                printf("Estado de conservacao: ");
                scanf(" %29[^\n]",
                      acervo[totalAcervo].conservacao);

                totalAcervo++;
                printf("CD registrado no acervo!\n");
                break;

            case 2:
                for (i = 0; i < totalAcervo; i++) {
                    id = buscarAlbum(acervo[i].idAlbum);

                    if (id != -1) {
                        printf("\nAlbum: %s\n", albuns[id].titulo);
                        printf("Midia: %s\n", acervo[i].tipo);
                        printf("Conservacao: %s\n",
                               acervo[i].conservacao);
                    }
                }
                break;

            case 3:
                printf("ID do album: ");
                scanf("%d", &id);

                for (i = 0; i < totalAcervo; i++) {
                    if (acervo[i].idAlbum == id) {
                        printf("Nova conservacao: ");
                        scanf(" %29[^\n]",
                              acervo[i].conservacao);

                        printf("Conservacao atualizada!\n");
                        break;
                    }
                }

                if (i == totalAcervo)
                    printf("CD nao encontrado no acervo!\n");

                break;

            case 0:
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (op != 0);
}


// ============================================================
// MODULO 4 - AUDICOES E RELATORIOS
// CASSIANI
// ============================================================

void moduloAudicoes() {
    int op, id, i, pos, maior;

    do {
        printf("\n--- MODULO 4: AUDICOES E RELATORIOS ---\n");
        printf("1. Registrar audicao\n");
        printf("2. Historico de audicoes\n");
        printf("3. Musica mais ouvida\n");
        printf("4. Album mais ouvido\n");
        printf("0. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                if (totalAudicoes >= 50) {
                    printf("Limite de audicoes atingido!\n");
                    break;
                }

                printf("ID da musica ouvida: ");
                scanf("%d", &id);

                pos = buscarMusica(id);

                if (pos == -1) {
                    printf("Musica nao encontrada!\n");
                    break;
                }

                musicas[pos].reproducoes++;

                audicoes[totalAudicoes].idMusica = id;
                audicoes[totalAudicoes].quantidade = 1;
                totalAudicoes++;

                printf("Audicao registrada!\n");
                break;

            case 2:
                for (i = 0; i < totalAudicoes; i++) {
                    pos = buscarMusica(audicoes[i].idMusica);

                    printf("Audicao %d: ", i + 1);

                    if (pos != -1)
                        printf("%s\n", musicas[pos].titulo);
                    else
                        printf("Musica removida do catalogo\n");
                }
                break;

            case 3:
                maior = -1;
                pos = -1;

                for (i = 0; i < totalMusicas; i++) {
                    if (musicas[i].ativo == 1 &&
                        musicas[i].reproducoes > maior) {
                        maior = musicas[i].reproducoes;
                        pos = i;
                    }
                }

                if (pos == -1) {
                    printf("Nenhuma musica cadastrada!\n");
                } else {
                    printf("Musica mais ouvida: %s\n",
                           musicas[pos].titulo);
                    printf("Reproducoes: %d\n",
                           musicas[pos].reproducoes);
                }
                break;

            case 4:
                maior = -1;
                pos = -1;

                for (i = 0; i < totalAlbuns; i++) {
                    int j, soma = 0;

                    if (albuns[i].ativo == 0)
                        continue;

                    for (j = 0; j < totalMusicas; j++) {
                        if (musicas[j].ativo == 1 &&
                            musicas[j].idAlbum == albuns[i].id) {
                            soma += musicas[j].reproducoes;
                        }
                    }

                    if (soma > maior) {
                        maior = soma;
                        pos = i;
                    }
                }

                if (pos == -1) {
                    printf("Nenhum album cadastrado!\n");
                } else {
                    printf("Album mais ouvido: %s\n",
                           albuns[pos].titulo);
                    printf("Artista: %s\n", albuns[pos].artista);
                    printf("Total de reproducoes: %d\n", maior);
                }
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (op != 0);
}


// ============================================================
// FUNCAO PRINCIPAL TODOS OS INTEGRANTES
// ============================================================

int main() {
    int op;

    do {
        cabecalho();

        printf("1. Colecao de albuns\n");
        printf("2. Catalogo de musicas\n");
        printf("3. Organizacao do acervo\n");
        printf("4. Audicoes e relatorios\n");
        printf("0. Encerrar sistema\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &op);

        switch (op) {
            case 1: moduloAlbuns(); break;
            case 2: moduloMusicas(); break;
            case 3: moduloAcervo(); break;
            case 4: moduloAudicoes(); break;
            case 0:
                printf("Encerrando a CDteca Pessoal!\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (op != 0);

    return 0;
}

