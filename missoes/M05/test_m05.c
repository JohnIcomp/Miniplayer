/* Testes incrementais M05 — não acessar campos privados de t_lse/t_elem. */
#include <assert.h>
#include <stdio.h>
#include "lse.h"

static int comparar_int(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

typedef struct { int id; const char *titulo; } musica_t;
static int comparar_musica(const void *a, const void *b) {
    int x = ((const musica_t *)a)->id, y = ((const musica_t *)b)->id;
    return (x > y) - (x < y);
}


static void teste_vazia_inicio_meio_fim(void) {
    int a = 20, b = 10, c = 30, d = 25;
    t_lse *l = lse_criar(); assert(l);
    assert(lse_inserir_ordenado(l, &a, comparar_int) == 1);   /* lista vazia */
    assert(lse_tamanho(l) == 1);
    assert(lse_primeiro(l) == &a);

    assert(lse_inserir_ordenado(l, &b, comparar_int) == 1);   /* início: 10 < 20 */
    assert(lse_primeiro(l) == &b);

    assert(lse_inserir_ordenado(l, &c, comparar_int) == 1);   /* fim: 30 */
    assert(lse_inserir_ordenado(l, &d, comparar_int) == 1);   /* meio: 25 */
    assert(lse_tamanho(l) == 4);

    /* ordem esperada: 10, 20, 25, 30 */
    assert(lse_remover_inicio(l) == &b);
    assert(lse_remover_inicio(l) == &a);
    assert(lse_remover_inicio(l) == &d);
    assert(lse_remover_inicio(l) == &c);
    assert(lse_tamanho(l) == 0);
    lse_destruir(l, NULL);
}

static void teste_duplicados_estaveis(void) {
     musica_t a={10,"primeira"}, b={10,"segunda"}, c={5,"menor"}, d={10,"terceira"};
    t_lse *l=lse_criar(); assert(l);

    assert(lse_inserir_ordenado(l, &a, comparar_musica) == 1);
    assert(lse_inserir_ordenado(l, &b, comparar_musica) == 1);
    assert(lse_inserir_ordenado(l, &c, comparar_musica) == 1);
    assert(lse_inserir_ordenado(l, &d, comparar_musica) == 1);
    assert(lse_tamanho(l) == 4);

    /* o menor vem primeiro; os três de id 10 ficam na ordem de chegada */
    assert(lse_remover_inicio(l) == &c);
    assert(lse_remover_inicio(l) == &a);
    assert(lse_remover_inicio(l) == &b);
    assert(lse_remover_inicio(l) == &d);
    lse_destruir(l, NULL);
}

static void teste_invalido_e_reinsercao(void) {
    int x = 1, y = 2;

    assert(lse_inserir_ordenado(NULL, &x, comparar_int) == 0);   /* lista NULL */
    t_lse *l = lse_criar(); assert(l);
    assert(lse_inserir_ordenado(l, &x, NULL) == 0);              /* comparador NULL */
    assert(lse_tamanho(l) == 0);                                 /* lista não mudou */
    assert(lse_primeiro(l) == NULL);

    assert(lse_inserir_ordenado(l, &y, comparar_int) == 1);
    assert(lse_inserir_ordenado(l, &x, comparar_int) == 1);
    assert(lse_remover_inicio(l) == &x);                         /* remove o 1 */
    assert(lse_inserir_ordenado(l, &x, comparar_int) == 1);      /* reinsere */
    assert(lse_remover_inicio(l) == &x);
    assert(lse_remover_inicio(l) == &y);
    assert(lse_tamanho(l) == 0);
    lse_destruir(l, NULL);
}

int main(void) {
    teste_vazia_inicio_meio_fim();
    teste_duplicados_estaveis();
    teste_invalido_e_reinsercao();
    puts("M05: todos os testes passaram.");
    return 0;
}
