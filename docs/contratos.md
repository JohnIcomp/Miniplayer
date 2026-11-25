# Contratos dos TADs — M01 a M04

## M01 — TAD Música

### 1. musica_criar

- **Nome e assinatura:** `t_musica *musica_criar(int id, const char *titulo, const char *artista, int duracao);`
- **Pré-condições:** `titulo` e `artista` não podem ser `NULL`. `id` e `duracao` são apenas valores inteiros.
- **Pós-condições:** devolve uma música com o ID, o título, o artista e a duração informados. Título e artista são copiados para memória própria da música, então mudar as strings originais depois não afeta os dados guardados.
- **Retorno:** o ponteiro para a música criada, ou `NULL` se algum argumento obrigatório for inválido ou se faltar memória.
- **Memória:** a função aloca a estrutura e as strings, e libera o que já tiver alocado se algo falhar no meio. Quem recebe a música é responsável por destruí-la com `musica_destruir`.
- **Invariantes:** os campos da música correspondem aos valores recebidos, e as strings são independentes das originais.
- **Testes:** `tests/test_musica.c` — criação, conferência dos campos, independência das strings, título `NULL` e destruição.

### 2. musica_destruir

- **Nome e assinatura:** `void musica_destruir(void *carga);`
- **Pré-condições:** `carga` é `NULL` ou aponta para uma `t_musica` válida que ainda não foi destruída. O parâmetro é `void *` para que a função possa ser usada como callback destrutor da lista.
- **Pós-condições:** libera o título, o artista e a própria estrutura.
- **Retorno:** nenhum. Se receber `NULL`, não faz nada.
- **Memória:** quem libera tudo é a própria função.
- **Invariantes:** nenhum recurso alocado por `musica_criar` fica para trás.
- **Testes:** `tests/test_musica.c` — destruição de uma música válida e chamada com `NULL`.

---

## M02 — TAD Lista Simplesmente Encadeada (LSE)

### 3. lse_criar

- **Nome e assinatura:** `t_lse *lse_criar(void);`
- **Pré-condições:** nenhuma.
- **Pós-condições:** cria uma lista vazia, com `inicio = NULL` e `tamanho = 0`.
- **Retorno:** o endereço da lista, ou `NULL` se a alocação falhar.
- **Memória:** a função aloca a lista; liberá-la é papel de `lse_destruir`.
- **Invariantes:** uma lista recém-criada tem tamanho zero, início nulo e nenhum nó.
- **Testes:** `missoes/M02/TESTE_INCREMENTAL_M02.c` — criação da lista e estado inicial.

### 4. lse_tamanho

- **Nome e assinatura:** `int lse_tamanho(const t_lse *lista);`
- **Pré-condições:** `lista` não pode ser `NULL`. Passar `NULL` é tratado como erro de uso e o programa aborta por `assert`.
- **Pós-condições:** só consulta; a lista não é modificada.
- **Retorno:** o número de nós da lista.
- **Memória:** não aloca nem libera nada.
- **Invariantes:** o valor devolvido é o campo `tamanho`, que sempre coincide com o número de nós alcançáveis.
- **Testes:** `missoes/M02/TESTE_INCREMENTAL_M02.c` — tamanho inicial igual a zero.

### 5. lse_primeiro

- **Nome e assinatura:** `void *lse_primeiro(const t_lse *lista);`
- **Pré-condições:** nenhuma; aceita `NULL`.
- **Pós-condições:** devolve a carga do primeiro nó sem removê-la e sem alterar a lista.
- **Retorno:** a carga do primeiro nó. Devolve `NULL` quando a lista é `NULL`, está vazia ou quando a primeira carga é `NULL`; para diferenciar esses casos, usa-se `lse_tamanho`.
- **Memória:** não aloca nem libera. A carga continua sendo de quem a inseriu.
- **Invariantes:** `inicio`, `tamanho` e os encadeamentos permanecem iguais.
- **Testes:** `missoes/M02/TESTE_INCREMENTAL_M02.c` — primeiro elemento de uma lista vazia é `NULL`.

### 6. lse_destruir

- **Nome e assinatura:** `void lse_destruir(t_lse *lista, t_lse_destruir_carga destruir_carga);`
- **Pré-condições:** `lista` é `NULL` ou uma lista criada por `lse_criar`. O callback é opcional.
- **Pós-condições:** percorre os nós; para cada um, chama o callback com a carga (se ele foi fornecido) e libera o nó. No fim, libera a própria lista, que deixa de ser válida.
- **Retorno:** nenhum. Com `lista == NULL`, não faz nada.
- **Memória:** a função libera nós e lista. As cargas só são liberadas quando há callback; sem ele, continuam pertencendo a quem as criou.
- **Invariantes:** nenhum nó da lista fica alocado depois da chamada. O próximo nó é guardado antes de cada `free`.
- **Testes:** `missoes/M02/TESTE_INCREMENTAL_M02.c` — lista vazia; `missoes/M03/test_m03.c` — destruição com callback (ainda com marcador `assert(1==0)`).

---

## M03 — Inserção no início

### 7. lse_inserir_inicio

- **Nome e assinatura:** `int lse_inserir_inicio(t_lse *lista, void *carga);`
- **Pré-condições:** nenhuma sobre `lista` (se for `NULL`, a função falha). A carga pode ser `NULL`: por decisão da M03, um nó pode existir sem carga.
- **Pós-condições:** cria um nó com a carga, liga-o ao antigo primeiro, atualiza `inicio` e soma um ao `tamanho`. Se algo falhar, a lista fica como estava.
- **Retorno:** `1` em sucesso; `0` se a lista for `NULL` ou se faltar memória.
- **Memória:** a função aloca o nó (por meio de `criar_elem_lse`), sem copiar a carga. O nó será liberado por uma remoção ou por `lse_destruir`.
- **Invariantes:** o novo nó passa a ser o primeiro, `tamanho` cresce em um, e o número de nós alcançáveis continua igual a `tamanho`.
- **Testes:** `missoes/M03/test_m03.c` — inserção e encadeamento (ainda com marcadores de falha); `tests/test_lse.c` — inserção de dois elementos e remoção em seguida.

### Percurso (pendente)

O enunciado da M03 prevê `lse_percorrer`, mas ela ainda não foi implementada nem declarada em `lse.h`. O contrato será escrito quando o professor confirmar que ela faz parte da missão.

---

## M04 — Inserção no fim, busca e remoção

Nas funções de busca e remoção, o comparador tem a forma `int comparar(const void *chave, const void *carga)` e devolve `0` quando a carga corresponde à chave. A lista sempre o chama como `comparar(chave, carga)`.

### 8. lse_inserir_fim

- **Nome e assinatura:** `int lse_inserir_fim(t_lse *lista, void *carga);`
- **Pré-condições:** `lista` não pode ser `NULL` (violação aborta por `assert`). A carga pode ser `NULL`.
- **Pós-condições:** cria um nó e o liga depois do último. Em lista vazia, o novo nó vira o primeiro. O `tamanho` aumenta em um.
- **Retorno:** `1` em sucesso; `0` se faltar memória, com a lista intacta.
- **Memória:** aloca o nó, sem copiar a carga. O nó é liberado por uma remoção ou por `lse_destruir`.
- **Invariantes:** a ordem dos elementos que já estavam na lista é mantida e o último nó aponta para `NULL`.
- **Testes:** `missoes/M04/test_m04.c` — lista vazia e não vazia, ordem e tamanho.

### 9. lse_buscar

- **Nome e assinatura:** `void *lse_buscar(const t_lse *lista, const void *chave, t_lse_comparador comparar);`
- **Pré-condições:** `lista` não pode ser `NULL` (aborta por `assert`); `comparar` precisa ser uma função válida; a chave deve ser compatível com o comparador.
- **Pós-condições:** percorre a lista e devolve a primeira carga para a qual `comparar(chave, carga) == 0`. Não altera a lista.
- **Retorno:** a carga encontrada, ou `NULL` se nenhuma corresponder.
- **Memória:** não aloca nem libera. Devolve só uma referência, sem passar a propriedade.
- **Invariantes:** nós, tamanho, início e ordem ficam inalterados.
- **Testes:** `missoes/M04/test_m04.c` — primeiro, intermediário e último elemento, chave inexistente e registros genéricos.

### 10. lse_remover

- **Nome e assinatura:** `void *lse_remover(t_lse *lista, const void *chave, t_lse_comparador comparar);`
- **Pré-condições:** `lista` não pode ser `NULL` (aborta por `assert`); `comparar` precisa ser válido; a chave deve ser compatível com o comparador. Convém não usar cargas `NULL` nesses cenários, porque `NULL` também significa "não encontrado".
- **Pós-condições:** remove só a primeira ocorrência da chave: religa o nó anterior (ou o `inicio`) ao seguinte, libera o nó e subtrai um do `tamanho`.
- **Retorno:** a carga removida, ou `NULL` se a chave não existir (lista inalterada).
- **Memória:** libera apenas o nó. A carga passa a ser responsabilidade de quem chamou.
- **Invariantes:** encadeamento válido, `tamanho` reduzido em um e ordem relativa dos demais mantida.
- **Testes:** `missoes/M04/test_m04.c` — início, meio e fim, chave inexistente, elemento único e chaves duplicadas.

### 11. lse_remover_inicio

- **Nome e assinatura:** `void *lse_remover_inicio(t_lse *lista);`
- **Pré-condições:** `lista` não pode ser `NULL` (aborta por `assert`).
- **Pós-condições:** remove o primeiro nó, atualiza `inicio`, subtrai um do `tamanho` e libera o nó.
- **Retorno:** a carga do nó removido; `NULL` se a lista estiver vazia (ou se a carga removida for `NULL`).
- **Memória:** libera só o nó; a carga fica com quem chamou.
- **Invariantes:** o novo início é o antigo segundo nó. Ao remover o último elemento, `inicio` vira `NULL` e `tamanho` vira zero.
- **Testes:** `missoes/M04/test_m04.c` — lista vazia, elemento único e remoções seguidas; `tests/test_lse.c` — remoções do início.

### 11. lse_inserir ordenado

---

## Invariantes da LSE
- `tamanho >= 0`.
- `tamanho == 0` se e somente se `inicio == NULL`.
- Há exatamente `tamanho` nós alcançáveis a partir de `inicio`.
- O último nó aponta para `NULL` e não há ciclos.
