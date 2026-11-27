# Diário de bordo
## Missão M01 — 11/11
- Integrantes e papéis: John Kennedy de Almeida Castro (Codificação e Teste) e João Pedro do Nascimento Seixas (Documentação)
- Objetivo: preparar o ambiente de compilação (GCC e Make) e implementar o módulo música (musica_criar e musica_destruir) com alocação dinâmica de memória.
- O que implementamos: Foi implementado `musica_criar` e `musica_destruir`. A Implementação armazena o ID, título, artista e duração da música, realizando cópias independentes das strings.
- Decisão técnica e justificativa: Utilizamos alocação dinâmica para armazenar os dados da música. As strings são copiadas para evitar que alterações nas variáveis originais modifiquem os dados armazenados, garantindo também a liberação dos recursos alocados.
- Problema encontrado e solução: Ao rodar make build/test_musica no PowerShell, foi criada uma pasta chamada "-p" e o executável não foi gerado. Causa: o Makefile usa comandos de Linux (mkdir -p), que o PowerShell do Windows não entende. Solução: apagar a pasta "-p" e passar a usar um terminal compatível com Linux (WSL com Ubuntu ou Git Bash).
- Evidências de testes: Testamos a criação de uma música, a integridade dos seus atributos, a independência das strings, a destruição de uma música e a passagem de ponteiro `NULL` em `build/test_musica`. Os testes passaram.
- Próxima ação: Iniciar a implementação da lista simplesmente encadeada na M02.

## Missão M02 — 13/11
- Integrantes e papéis: João Pedro do Nascimento Seixas (Codicação) e John Kennedy de Almeida Castro (Documentação)
- Objetivo: Implementar a criação de uma lista simplesmente encadeada vazia, suas consultas básicas e a preparação de sua estrutura.
- O que implementamos: Estruturamos `lse_criar`, `lse_tamanho`, `lse_primeiro` e `lse_destruir`, permitindo inicializar uma lista vazia e consultar seu tamanho e primeiro elemento.
- Decisão técnica e justificativa: Representamos uma lista vazia com `inicio = NULL` e `tamanho = 0`. Mantivemos a estrutura dos nós como um detalhe interno de `lse.c`, evitando expor sua implementação para outros módulos.
- Problema encontrado e solução: As funções estavam inicialmente como stubs e não atendiam aos contratos esperados pelos testes. Implementamos os comportamentos necessários e completamos a interface da lista para permitir sua utilização pelos demais módulos.
- Evidências de testes: Verificamos se a lista era criada corretamente, se seu tamanho inicial era zero e se o primeiro elemento retornava `NULL`.
- Próxima ação: Implementar a base completa da lista simplesmente encadeada genérica e a inserção de elementos no início na M03.

## Missão M03 — 16/11
- Integrantes e papéis: John Kennedy de Almeida Castro (codificação) e João Pedro do Nascimento Seixas (Documentação)
- Objetivo: implementar a base da lista simplesmente encadeada genérica (criar, tamanho, primeiro, inserir no início e destruir), mantendo t_elem escondido em lse.c e t_lse como tipo opaco.
- O que implementamos: lse_criar, lse_tamanho, lse_primeiro, lse_inserir_inicio, além da função auxiliar interna criar_elem_lse.
- Decisão técnica e justificativa: Mantivemos `t_elem` privado em `lse.c` e utilizamos carga genérica (`void *`) para permitir operações sobre diferentes tipos de dados sem tornar a lista dependente da estrutura de músicas, centralizando a criação dos nós em `criar_elem_lse`.
- Problema encontrado e solução: Foi necessário garantir que a inserção atualizasse corretamente o ponteiro inicial e o tamanho da lista sem perder o encadeamento dos nós existentes.
- Evidências de testes: Verificamos a criação da lista vazia, consultas iniciais e inserções no início da lista, confirmando a atualização correta do topo e do contador de elementos.
- Próxima ação: Implementar a inserção no fim, a remoção do início, a busca por chave, a remoção específica e a destruição completa da lista na M04.

## Missão M04 — 18/11
- Integrantes e papéis: João Pedro do Nascimento Seixas (Codificação) e John Kennedy de Almeida Castro (Documentação e teste)
- Objetivo: implementar inserção no fim, remoção do início, busca e remoção por chave, usando um comparador recebido por callback.
- O que implementamos: lse_inserir_fim, lse_remover_inicio, lse_buscar e lse_remover, lse_destruir.
- Decisão técnica e justificativa: Optamos por não adicionar um ponteiro para o último nó, realizando o percurso da lista durante a inserção no fim. Utilizamos callbacks de comparação para manter a estrutura genérica e independente do tipo `t_musica`. A remoção libera somente o nó, devolvendo a carga para que sua liberação seja responsabilidade de quem utiliza a lista, enquanto `lse_destruir` utiliza callback destrutor opcional.
- Problema encontrado e solução: Foi necessário tratar diferentes situações de remoção, como listas vazias, remoção do único elemento, remoção no meio e no final da lista, além de chaves duplicadas. Corrigimos as atualizações dos ponteiros e do tamanho para preservar os invariantes.
- Evidências de testes: Verificamos inserção no fim, busca de elementos em diferentes posições, remoções no início, meio e fim, chaves duplicadas, cargas genéricas, argumentos inválidos e liberação via `lse_destruir`.
- Próxima ação: testar busca e remoção (início, meio, fim, chave inexistente) e seguir para a M05 (inserção ordenada).

## Missão M05 — 23/11
- Integrantes e papéis: João Pedro do Nascimento Seixas (Codificação) e John Kennedy de Almeida Castro (Documentação e teste)
- Objetivo: fazer a biblioteca receber músicas na posição certa, sem ordenar a coleção inteira depois de cada inserção. Então, vamos implementar o `lse_inserir_ordenado` para resolver isso.
- O que implementamos: lse_inserir_ordenado.
- Decisão técnica e justificativa: Optamos por inserir cada elemento já na posição correta, em vez de ordenar a lista depois, o que custa O(n) no pior caso, pois a lista pode ser percorrida até o fim. Utilizamos o callback de comparação para que o critério de ordem (título, duração ou identificador) seja definido por quem usa a lista, mantendo `lse.c` independente do tipo `t_musica`. A inserção aloca apenas o novo nó, sem copiar a carga, e retorna 0, sem alterar a lista, quando os argumentos são inválidos ou a alocação falha.
- Evidências de testes: 
- Próxima ação: 

## Missão M06 — 25/11
- Integrantes e papéis: João Pedro do Nascimento Seixas (Codificação) e John Kennedy de Almeida Castro (Documentação e teste)
- Objetivo: Implementar o TAD Pilha (LIFO) por composição, reutilizando a lista simplesmente encadeada, sem duplicar o encadeamento.
- O que implementamos: Implementamos pilha_criar, pilha_empilhar,pilha_desempilhar, pilha_topo e pilha_destruir em src/pilha.c. Cada operação delega para uma função da lista: lse_criar, lse_inserir_inicio, lse_remover_inicio, lse_primeiro e lse_destruir.
- Decisão técnica e justificativa: Optamos por guardar uma lista dentro da pilha (`struct pilha { t_lse *lista; }`) e usar o início da lista como topo, o que mantém empilhar, desempilhar e consultar o topo em O(1); a destruição é O(n). A pilha não copia cargas: pilha_desempilhar devolve a carga sem liberá-la, e pilha_destruir repassa o callback opcional, que pode ser `NULL` quando as cargas pertencem a outra estrutura (como as músicas da biblioteca). Em pilha_criar, a pilha é liberada se a criação da lista falhar, evitando vazamento. Cada função verifica se a pilha é `NULL` antes de delegar, pois lse_remover_inicio usa assert. Usamos cargas diferentes de `NULL`, porque `NULL` também indica pilha vazia.
- Evidências de testes: O `Makefile.incremental` da M06 usa `$(CC)`, que não existia no nosso ambiente (`cc` não encontrado); resolvemos passando `CC=gcc` na chamada do `make`. No PowerShell, o `mkdir -p` do Makefile criou uma pasta "-p" e interrompeu a compilação; passamos a usar o Git Bash, onde o comando funciona.
- Evidências de testes: Executamos `make CC=gcc -f missoes/M06/Makefile.incremental test_m06`. A compilação ocorreu com `-Wall -Wextra -Wpedantic`, sem avisos, e a saída foi "M06: todos os testes passaram.". O teste cobre ordem LIFO, topo sem remoção, pilhas independentes, destruição com callback e argumentos `NULL`.
- Próxima ação: Integrar a pilha ao histórico de reprodução na M07.

> Duplicar esta seção a cada missão e alternar os papéis na dupla.