# Diário de bordo
## Missão M01 — 11/11
- Integrantes e papéis: John Kennedy de Almeida Castro (Codificação e Teste) e João Pedro do Nascimento Seixas (Documentação)
- Objetivo: preparar o ambiente de compilação (GCC e Make) e implementar o módulo música (musica_criar e musica_destruir) com alocação dinâmica de memória.
- O que implementamos: Foi implementado `musica_criar` e `musica_destruir`. A Implementação armazena o ID, título, artista e duração da música, realizando cópias independentes das strings.
- Decisão técnica e justificativa:
- Problema encontrado e solução: Ao rodar make build/test_musica no PowerShell, foi criada uma pasta chamada "-p" e o executável não foi gerado. Causa: o Makefile usa comandos de Linux (mkdir -p), que o PowerShell do Windows não entende. Solução: apagar a pasta "-p" e passar a usar um terminal compatível com Linux (WSL com Ubuntu ou Git Bash).
- Evidências de testes:
- Próxima ação:

## Missão M02 — 13/11
- Integrantes e papéis: João Pedro do Nascimento Seixas (Codicação) e John Kennedy de Almeida Castro (Documentação)
- Objetivo:
- O que implementamos:
- Decisão técnica e justificativa:
- Problema encontrado e solução:
- Evidências de testes:
- Próxima ação:

## Missão M03 — 16/11
- Integrantes e papéis: John Kennedy de Almeida Castro (codificação) e João Pedro do Nascimento Seixas (Documentação)
- Objetivo: implementar a base da lista simplesmente encadeada genérica (criar, tamanho, primeiro, inserir no início e destruir), mantendo t_elem escondido em lse.c e t_lse como tipo opaco.
- O que implementamos: lse_criar, lse_tamanho, lse_primeiro, lse_inserir_inicio, além da função auxiliar interna criar_elem_lse.
- Decisão técnica e justificativa:
- Problema encontrado e solução:
- Evidências de testes:
- Próxima ação:

## Missão M04 — 18/11
- Integrantes e papéis: João Pedro do Nascimento Seixas (Codificação) e John Kennedy de Almeida Castro (Documentação e teste)
- Objetivo: implementar inserção no fim, remoção do início, busca e remoção por chave, usando um comparador recebido por callback.
- O que implementamos: lse_inserir_fim, lse_remover_inicio, lse_buscar e lse_remover, lse_destruir.
- Decisão técnica e justificativa:
- Problema encontrado e solução:
- Evidências de testes:
- Próxima ação: testar busca e remoção (início, meio, fim, chave inexistente) e seguir para a M05 (inserção ordenada).

> Duplicar esta seção a cada missão e alternar os papéis na dupla.
