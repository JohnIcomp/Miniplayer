# Arquitetura
## Componentes
| Módulo | Responsabilidade | Dependências |
|---|---|---|
| musica | Dados da música | biblioteca padrão |
| lse | Nós genéricos e encadeamento | biblioteca padrão |
| pilha | Política LIFO | lse |
| fila | Política FIFO | lse |
| miniplayer | Simulação e integração | demais TADs |

## Diagrama de dependências
MiniPlayer → (LSE, Pilha, Fila) → LSE → t_elem interno.

## Decisões técnicas (preencher)
- Por que `void *`?
A lista não precisa saber o que guarda. Com `void *carga`, o mesmo código de lista serve para músicas, para a pilha do histórico e para a fila de reprodução, sem duplicar encadeamento. O custo é perder a checagem de tipos do compilador: quem usa a lista precisa converter o ponteiro de volta (por exemplo, `t_musica *m = carga;`) e é responsável por saber o que colocou lá.

- Quem é dono das cargas?
A biblioteca é dona das músicas. A lista é dona apenas dos próprios nós (`t_elem`): ela os aloca na inserção e os libera na remoção e em `lse_destruir`. A inserção guarda o ponteiro da carga sem copiá-la. `lse_destruir(lista, NULL)` libera só nós e lista; com callback (como `musica_destruir`), libera também cada carga.

- Como tratar referências compartilhadas?
Fila e histórico guardam ponteiros para músicas que pertencem à biblioteca. Por isso, eles são destruídos com callback `NULL`, e só a biblioteca usa `musica_destruir`. Antes de liberar uma música, é preciso removê-la da fila e do histórico, senão sobram ponteiros inválidos ou ocorre liberação dupla.

- Quando adicionar ponteiro `fim`?
Sem `fim`, `lse_inserir_fim` percorre a lista inteira (O(n)). Isso pesa quando a fila enfileira muitas músicas, então a otimização fica para a M08. O custo é manter o `fim` correto em toda inserção e remoção, em especial ao remover o último nó e ao esvaziar a lista.