# CDteca Pessoal

Sistema de console em C para gerenciar uma coleção pessoal de CDs: álbuns, músicas, estado de conservação do acervo e histórico de audições.

Projeto da disciplina **Algoritmos e Pensamento Computacional** (Projeto P2).

## Integrantes

| Integrante | Módulo |
|---|---|
| Bernardo Benato (RGM: 47415487) | Coleção de Álbuns |
| Kamila Marcon (RGM: 47123141) | Catálogo de Músicas |
| Izadora Rodrigues (RGM: 47728345) | Acervo e Conservação |
| Cassiani Teixiera (RGM: 46620494) | Audições e Relatórios |

---

## Sprint 1 (Checkpoint 1)

**Objetivo:** montar a arquitetura base do sistema, com structs, menus e submenus, dividida por integrante.

### O que foi desenvolvido

- Uma `struct` global por integrante, cada uma com 4 ou mais campos e seu vetor de armazenamento de 50 posições.
- Menu principal em loop contínuo (`do-while` + `switch-case`) que direciona para os quatro submenus.
- Cada submenu com as operações de Cadastrar, Listar/Buscar, Editar e Remover.
- Código dividido em funções `void` fora do `main`, cada uma identificada com `// Autor:`.

### Situação dos módulos

| Módulo | Situação |
|---|---|
| Coleção de Álbuns | Cadastro, listagem, busca e remoção funcionando. Edição em construção. |
| Catálogo de Músicas | Menu pronto. Operações em construção. |
| Acervo e Conservação | Menu pronto. Operações em construção. |
| Audições e Relatórios | Menu pronto. Operações e relatórios (música e álbum mais ouvidos) em construção. |

### Como compilar e executar

```bash
gcc main.c -o cdteca
./cdteca
```

No Dev-C++, basta abrir o `main.c`, compilar e executar.

> Nesta etapa, os campos de texto aceitam apenas uma palavra, sem espaços.

---

## Sprint 2 (Checkpoint 2)

### Objetivo

Transformar a "casca" da Sprint 1 em um sistema que funciona de verdade: dividir o código em módulos `.h` (um por integrante), persistir os dados em arquivos `.csv`, trocar a lógica solta dos `case` por subfunções reais com busca textual e implementar regras de negócio que cruzam os quatro módulos, com relatórios analíticos, Matriz 2D e ordenação.

### O que foi desenvolvido

**Divisão em módulos (`.h`)**

- `main.c` enxuto: apenas inclui os módulos, carrega os CSVs na abertura e exibe o menu principal.
- Um arquivo `.h` por integrante, mais o `utils.h` com as funções compartilhadas.
- Ordem dos `#include` respeitando as dependências: `utils.h` → `albuns.h` → `musicas.h` → `acervo.h` → `audicoes.h`.

**Persistência em CSV**

- Cada módulo tem `salvar...CSV()` e `carregar...CSV()`, com separador `;`.
- Os dados são carregados automaticamente ao abrir o programa.
- Editar e Remover alteram o vetor na memória e regravam o arquivo inteiro com `fopen(..., "w")`, mantendo o CSV sempre sincronizado.
- Cada CSV acompanha o projeto com dados reais e coerentes entre si (veja a tabela abaixo).

| Arquivo | Campos | Registros |
|---|---|---|
| `albuns.csv` | `id;titulo;artista;genero;ano` | 9 |
| `musicas.csv` | `id;idAlbum;titulo;duracaoSeg;reproducoes` | 25 |
| `acervo.csv` | `idAlbum;tipo;conservacao;totalUsos` | 9 |
| `audicoes.csv` | `id;idMusica;diaSemana;segundos` | 40 |

**Subfunções reais e busca textual**

- Todo `case` dos submenus chama uma função própria: `cadastrar...()`, `listar...()`, `buscar...()`, `editar...()` e `remover...()`.
- Buscas por texto com `strstr`, sem diferenciar maiúsculas de minúsculas (função `contemTexto` do `utils.h`).
- Bloqueio de ID repetido no cadastro de álbuns e músicas, e de CD duplicado no acervo. As audições recebem ID automático (maior ID + 1).
- Validação de entradas (números inválidos são rejeitados) e troca de `;` por `,` nos textos digitados, para não quebrar o formato do CSV.

**Regras de negócio e cruzamento entre módulos**

- **Registrar audição** (módulo transacional) valida em cadeia: a música existe, o álbum dela existe e o CD está registrado no acervo.
- O tempo ouvido é calculado automaticamente a partir da duração da música.
- A reprodução da música e o uso do CD são contabilizados na hora.
- **Baixa automática por desgaste:** a cada 20 usos, a conservação do CD desce um nível (Novo → Bom → Regular → Desgastado).
- **Remoção em cascata:** ao remover um álbum, são removidos também suas músicas, o CD no acervo e as audições dessas músicas, em todos os CSVs. Ao remover uma música, suas audições também são apagadas.
- Editar ou remover uma audição desfaz ou ajusta os contadores da música e do acervo.

**Relatórios analíticos**

1. Tempo total de escuta por álbum (em horas, minutos e segundos).
2. **Matriz 2D** álbum × dia da semana, com o dia favorito de cada álbum.
3. Ranking de álbuns mais ouvidos, ordenado com **Bubble Sort** em vetor de structs (sobre uma cópia, sem alterar os dados originais).
4. Ranking de músicas mais ouvidas (Top 10), também com Bubble Sort.
5. Estatísticas gerais: total de audições, tempo total, média de reproduções por música, percentual de CDs desgastados e gênero mais ouvido.

**Usabilidade**

- `setlocale` com `<locale.h>` no início do `main`.
- `limparTela()` (`cls`/`clear`) a cada troca de menu e `pausar()` para o usuário ler os resultados.
- Campos de texto agora aceitam espaços (leitura com `%[^\n]`).
- O campo `ativo` da Sprint 1 foi removido: a remoção agora é física, puxando os registros do vetor para cobrir a posição apagada.

### Situação dos módulos

| Módulo | Arquivo | Situação |
|---|---|---|
| Coleção de Álbuns | `albuns.h` | Completo: cadastrar, listar, buscar (título/artista), editar e remover (com cascata), sincronizado com `albuns.csv`. |
| Catálogo de Músicas | `musicas.h` | Completo: cadastrar (valida o álbum), listar, buscar, editar e remover, sincronizado com `musicas.csv`. |
| Acervo e Conservação | `acervo.h` | Completo: registrar CD, listar, buscar, editar e remover, com níveis de conservação e desgaste automático, sincronizado com `acervo.csv`. |
| Audições e Relatórios | `audicoes.h` | Completo: registrar (com validação cruzada), histórico, buscar, editar e remover, mais os 5 relatórios, sincronizado com `audicoes.csv`. |

### Como compilar e executar

Estrutura do projeto (todos os arquivos na **mesma pasta**):

```
main.c
utils.h
albuns.h
musicas.h
acervo.h
audicoes.h
albuns.csv
musicas.csv
acervo.csv
audicoes.csv
```

**Pelo terminal:**

```bash
gcc main.c -o cdteca
./cdteca
```

**No Dev-C++:**

1. Abra somente o `main.c` (os `.h` são incluídos automaticamente).
2. Se aparecer erro de `for` com declaração, ative o padrão C99 em *Tools > Compiler Options* adicionando `-std=c99`.
3. Compile e execute com **F11**.

> Os arquivos `.csv` precisam estar na mesma pasta do executável. Para visualizar ou editar manualmente, use o Bloco de Notas ou o VS Code: salvar pelo Excel pode alterar o separador e impedir a leitura.
