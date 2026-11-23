# Relatório de testes — MiniPlayer (M01 a M04)

| ID | Missão | Função/contrato | Entrada/cenário | Resultado esperado | Resultado obtido | Status |
|---|---|---|---|---|---|---|
| T01 | M01 | `musica_criar` | Instanciação com ID, título, artista e duração válidos | Ponteiro válido e campos gravados corretamente | Estrutura criada com todos os valores esperados | PASSOU |
| T02 | M01 | `musica_criar` | Modificação das strings de origem depois da criação | As informações salvas precisam se manter independentes | Mudanças nas strings de origem não afetaram a música | PASSOU |
| T03 | M01 | `musica_destruir` | Liberação de música válida e passagem de `NULL` | Desalocar a memória sem provocar falhas de acesso | Liberação realizada com sucesso e argumento `NULL` tratado sem erros | PASSOU |
| T04 | M01 | `musica_criar` | Parâmetro de título nulo (`NULL`) | Devolver `NULL` evitando alocação indevida | Devolveu `NULL` como previsto | PASSOU |
| T05 | M02 | `lse_criar` | Inicialização de uma lista vazia | Devolver uma estrutura válida com zero elementos | Lista inicializada com sucesso | PASSOU |
| T06 | M02 | `lse_tamanho` | Verificação da quantidade de itens em uma lista recém-criada | Devolver zero | Devolveu zero | PASSOU |
| T07 | M02 | `lse_primeiro` | Acesso ao primeiro item de uma lista vazia | Devolver `NULL` | Devolveu `NULL` | PASSOU |
| T08 | M02 | `lse_destruir` | Liberação de uma lista vazia sem função de callback | Desalocar a lista sem tentar limpar cargas inexistentes | Liberação concluída com sucesso | PASSOU |
| T09 | M03 | `lse_inserir_inicio` | Adição de itens no início da lista | Alocar nós, ajustar `inicio` e aumentar `tamanho` | Comportamento validado em teste auxiliar separado | PASSOU (AUXILIAR) |
| T10 | M03 | `lse_percorrer` | Iteração em lista vazia e em lista contendo três itens | Ignorar visitas quando vazia e percorrer os itens na sequência esperada | Iteração e ordenação validadas em teste auxiliar | PASSOU (AUXILIAR) |
| T11 | M03 | `lse_destruir` | Liberação usando callback para desalocar cargas dinâmicas | Acionar o destrutor uma vez por carga e desalocar os nós | Callback acionado com sucesso; análise com sanitizers livre de falhas | PASSOU (AUXILIAR) |
| T12 | M03 | Testes originais `test_m03.c` | Rodada dos testes-base contendo `assert(1==0)` | Parar o programa ao atingir o ponto intencional de falha | Programa parado em `teste_lista_vazia`, logo na primeira sentinela | FALHA INTENCIONAL |
| T13 | M03 | Robustez da lista | Adição com lista `NULL`, cargas `NULL` e callbacks facultativos | Lidar com parâmetros inválidos sem falha de memória e aceitar carga `NULL` | Cenários validados no teste auxiliar separado | PASSOU (AUXILIAR) |
| T14 | M04 | `lse_inserir_fim` | Adição ao final em lista vazia e já populada | Adicionar ao término mantendo a sequência e ajustando o tamanho | Itens adicionados e sequência mantida | PASSOU |
| T15 | M04 | `lse_buscar` | Pesquisa pelo primeiro, central, último e item ausente | Devolver a primeira carga compatível ou `NULL` | Retornos adequados e estrutura intacta depois das pesquisas | PASSOU |
| T16 | M04 | `lse_remover` | Exclusão de itens no começo, meio e término | Excluir apenas a primeira ocorrência compatível e ajustar os ponteiros | Exclusões realizadas com sucesso | PASSOU |
| T17 | M04 | `lse_remover_inicio` | Exclusão em lista vazia, com item único e múltiplas remoções seguidas | Devolver a carga excluída e ajustar adequadamente o início e o tamanho | Todos os casos rodaram conforme o esperado | PASSOU |
| T18 | M04 | `lse_remover` | Exclusão de chave ausente | Devolver `NULL` mantendo a lista inalterada | Devolveu `NULL` e manteve a estrutura intacta | PASSOU |
| T19 | M04 | `lse_buscar` e `lse_remover` | Presença de chaves repetidas | Localizar e excluir apenas a primeira aparição | Primeira aparição excluída e segunda mantida | PASSOU |
| T20 | M04 | Generalidade da LSE | Testes com `int` e registro similar a `t_musica` | Suportar guarda e comparação de distintos tipos de dados | Pesquisa e exclusão operaram corretamente para ambos os tipos | PASSOU |
| T21 | M04 | Tratamento de argumentos inválidos | Ponteiro de lista `NULL`, função de comparação `NULL` e lista vazia | Devolver os resultados esperados sem gerar falhas de acesso | Todos os cenários foram aprovados | PASSOU |
| T22 | M04 | Inserção e remoção | Exclusão seguida de nova inserção | Manter a ligação dos nós e o tamanho consistentes após os passos | Estrutura seguiu íntegra | PASSOU |
| T23 | M02–M04 | `make test_missoes` | Rodada completa dos testes incrementais | Rodar as suítes configuradas na sequência estabelecida pelo Makefile | M02 foi aprovada e a rodada parou na sentinela da M03, antes de chegar à M04 | FALHA INTENCIONAL |

## Casos-limite

### Estrutura vazia:

- M02: validamos a inicialização de uma lista vazia, apresentando `inicio == NULL` e `tamanho == 0`.
- M02: confirmamos que `lse_primeiro` devolve `NULL` quando não há elementos armazenados.
- M02: testamos a liberação de uma lista vazia sem o uso de callback.
- M04: confirmamos que `lse_remover_inicio` devolve `NULL` ao ser chamada sobre uma lista vazia.
- M03: os cenários previstos no arquivo de teste original mantêm os marcadores `assert(1==0)`, seguindo a instrução do professor.

### Estrutura com um elemento:

- M04: validamos a adição de um único item ao final da lista.
- M04: testamos a exclusão desse item único por meio de `lse_remover_inicio`.
- M04: confirmamos que, depois da exclusão, o tamanho retorna a zero e a lista volta a ficar vazia.
- M04: validamos ainda a exclusão do elemento único utilizando sua respectiva chave.

### Chave inexistente:

- M04: efetuamos pesquisas informando uma chave ausente na lista.
- Confirmamos que `lse_buscar` devolve `NULL`.
- Confirmamos que `lse_remover` igualmente devolve `NULL`.
- Verificamos que tanto o tamanho quanto a ordenação dos itens continuam intactos depois dessas chamadas.

### Falha de alocação (discutir estratégia de simulação):

Nos testes conduzidos até aqui, não foi aplicada uma simulação controlada para falhas de alocação de memória.

A abordagem planejada para uma validação futura consiste em adotar um wrapper de alocação, responsável por interceptar temporariamente as chamadas a `malloc` durante a bateria de testes. Esse wrapper pode ser ajustado para falhar em uma requisição pontual, possibilitando avaliar como as funções reagem diante de escassez de memória.

Por meio dessa abordagem, será possível validar:

- Se `lse_criar` devolve `NULL` ao falhar na alocação da estrutura principal da lista.
- Se `lse_inserir_inicio` devolve zero ao falhar na alocação de um novo nó.
- Se `lse_inserir_fim` devolve zero ao falhar na alocação de um novo nó.
- Se a estrutura já existente se mantém íntegra depois de uma falha de alocação.

Evitamos solicitar alocações excessivamente grandes para forçar erros, uma vez que essa técnica não oferece comportamento determinístico.

## Memória

### Comandos de compilação e execução

Todos os comandos foram rodados a partir do diretório raiz `TRABALHO_MINIPLAYER`.

**Testes individuais:**

```bash
make test_m01
make test_m02
make test_m03
make test_m04
```

Resultados:

- M01: rodada finalizada com sucesso.
- M02: rodada finalizada com sucesso.
- M03: compilação bem-sucedida, porém execução interrompida pelo `assert(1==0)` proposital.
- M04: rodada finalizada com sucesso.

**Teste integrado:**

```bash
make test_missoes
```

O comando demonstrou que a integração identifica corretamente os testes incrementais. A M02 foi aprovada e a M03 parou a execução devido à sentinela proposital. Já a M04 foi rodada de forma isolada e obteve aprovação.

**Compilação do programa principal:**

```bash
make all
```

A compilação foi finalizada sem erros.

**Verificação adicional da lista:**

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -g \
-Iinclude tests/test_lse.c src/lse.c -o /tmp/test_lse_root

/tmp/test_lse_root
```

Resultado: `test_lse: OK`.

Adicionalmente, foi rodado um teste auxiliar temporário voltado à M03, empregando AddressSanitizer e UndefinedBehaviorSanitizer para validar inserção, iteração, cargas genéricas e callback destrutor. Nenhuma falha foi detectada durante essa análise.

### Ferramentas utilizadas

- **GCC:** compilação do código-fonte em C.
- **GNU Make:** automação e execução dos testes isolados e integrados.
- **Biblioteca `assert.h`:** validação das condições esperadas nos casos de teste.
- **AddressSanitizer:** detecção de falhas relacionadas a acesso e gestão de memória.
- **UndefinedBehaviorSanitizer:** detecção de comportamentos indefinidos em tempo de execução.
- **Terminal:** disparo dos comandos, acompanhamento das saídas e diagnóstico de falhas.

### Problemas encontrados e corrigidos

1. **Ausência de cabeçalhos:** o kit inicial não trazia alguns arquivos `.h` indispensáveis. Os cabeçalhos faltantes foram adicionados para viabilizar a compilação dos módulos.
2. **Criação e inicialização da LSE:** foi preciso assegurar que uma lista recém-inicializada apresentasse ponteiro inicial nulo e tamanho zerado.
3. **Gerenciamento de memória:** foram estruturadas desalocações distintas para os nós e para as cargas, recorrendo ao callback destrutor quando aplicável.
4. **Encadeamento:** foram ajustadas e validadas as atualizações de ponteiros ao longo das operações de inserção e exclusão.
5. **Generalidade da lista:** foram adotadas cargas do tipo `void *` e funções de callback para comparação, eliminando o acoplamento direto entre o módulo `lse` e o tipo `t_musica`.
6. **Testes da M03:** as asserções `assert(1==0)` foram mantidas intactas segundo a recomendação do professor. A interrupção na M03 foi documentada como esperada, evitando confundi-la com reprovação da lógica.
7. **Integração dos Makefiles:** foi incorporado o suporte à detecção automática das missões, viabilizando o disparo dos testes diretamente pelo Makefile raiz.

## Conclusão

As funcionalidades referentes às missões M01, M02, M03 e M04 foram implementadas e testadas. As suítes oficiais de M01, M02 e M04 foram aprovadas. A lógica da M03 também passou por validação isolada através de testes auxiliares, enquanto seu arquivo de teste padrão conserva os marcadores propositais de falha.

A execução integrada via `make test_missoes` identifica adequadamente as missões configuradas, interrompendo o fluxo na M03 em razão da sentinela `assert(1==0)`. Esse comportamento foi devidamente registrado sem alterar as verificações originais fornecidas pelo professor.