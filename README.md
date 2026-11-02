# CDteca Pessoal

Sistema de console em C para gerenciar uma coleção pessoal de CDs: álbuns, músicas, estado de conservação do acervo e histórico de audições.

Projeto da disciplina **Algoritmos e Pensamento Computacional** (Projeto P2).

## Integrantes

| Integrante | Módulo |
|---|---|
| Bernardo Rodrigues Benato (RGM: ___) | Coleção de Álbuns |
| Kamila (Nome Completo e RGM) | Catálogo de Músicas |
| Izadora (Nome Completo e RGM) | Acervo e Conservação |
| Cassiani (Nome Completo e RGM) | Audições e Relatórios |

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

## Sprint 2

*(Escrever aqui o objetivo, o que foi desenvolvido e a situação dos módulos na segunda etapa.)*

### Objetivo

### O que foi desenvolvido

### Situação dos módulos

### Como compilar e executar
