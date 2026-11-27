#include "pilha.h"
#include "lse.h"
#include <stddef.h>
#include <stdlib.h>

struct pilha { t_lse *lista; };
/* M06: implementar apenas delegando para lse_*. */
t_pilha *pilha_criar(void) {
    t_pilha *p = malloc(sizeof(t_pilha));
    if(p == NULL){
        return NULL;
    }
    p->lista = lse_criar();
    if(p->lista == NULL){
        free(p);
        return NULL;
    }
    return p;
}

int pilha_empilhar(t_pilha *p, void *c) {
    if(p == NULL){
        return 0;
    }
    return lse_inserir_inicio(p->lista, c);
}


void *pilha_topo(const t_pilha *p) {
    if(p == NULL){
        return NULL;
    }
    return lse_primeiro(p->lista);
}

void *pilha_desempilhar(t_pilha *p) {
    if(p == NULL){
        return NULL;
    }
    return lse_remover_inicio(p->lista);
}

void pilha_destruir(t_pilha *p, void (*d)(void *)) {
    if(p == NULL){
        return;
    }
    lse_destruir(p->lista, d);
    free(p);
}