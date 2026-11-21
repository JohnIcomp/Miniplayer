#include "lse.h"
#include <stddef.h>
#include "stdlib.h"
#include "assert.h"
#include "stdbool.h"

/* Representacao interna: NAO mover para lse.h. */
typedef struct elem {
    void *carga;
    struct elem *prox;
} t_elem;
struct lse {
    t_elem *inicio;
    int tamanho;
    /* M08 (otimizacao opcional): t_elem *fim; */
};


t_elem* criar_elem_lse(void* carga){
    t_elem* novo = malloc(sizeof(t_elem));
    if(novo == NULL){
        return NULL;
    }
    novo->carga = carga;
    novo->prox=NULL;

    return novo;
}
/* Stubs intencionalmente incompletos; testes devem falhar ate implementacao. */
t_lse *lse_criar(void) {
    t_lse* nova = malloc(sizeof(t_lse));
    if(nova == NULL){
        return NULL;
    }
    nova->inicio = NULL;
    nova->tamanho = 0;
    return nova;
    } 

    /* TODO M02/M03 */
int lse_tamanho(const t_lse *lista){
    assert(lista != NULL);

    return lista-> tamanho;
    }
     /* TODO M03 */
void *lse_primeiro(const t_lse *lista){
    if(lista == NULL || lista->inicio == NULL){
        return NULL;
    }
    return lista->inicio->carga;
    }
     /* TODO M03 */
int lse_inserir_inicio(t_lse *lista, void *carga){
    if(lista == NULL){
        return 0;
    }
    t_elem* novo = criar_elem_lse(carga);
    if(novo == NULL){
        return 0;
    }
    if(lista->inicio == NULL){
        lista->inicio = novo;
    }else{
        novo->prox = lista->inicio;
        lista->inicio = novo;
    }
    lista->tamanho++;
    return 1;
    }
     /* TODO M04 */

int lse_inserir_fim(t_lse *lista, void *carga) {
    assert(lista != NULL);
    t_elem* novo = criar_elem_lse(carga);
    if(novo==NULL){
        return 0;
    }
    if (lista->inicio == NULL){
        lista->inicio =novo;
    }else{
        t_elem* cam = lista->inicio;
        while(cam->prox!=NULL){
            cam = cam->prox;
        }
        cam->prox = novo;
    }
    lista->tamanho++;

    return 1;
    }
     /* TODO M04 */
void *lse_remover_inicio(t_lse *lista){
    assert(lista!=NULL);
    if(lista->tamanho==0){
        return NULL;
    }

    t_elem* prim= lista->inicio;
    lista->inicio = prim->prox;

    void* carga = prim->carga;
    lista->tamanho--;
    free(prim);
    return carga;
    }
     /* TODO M04 */
void *lse_buscar(const t_lse *lista, const void *chave, t_lse_comparador cmp){

    assert(lista!=NULL);
    t_elem* cam = lista->inicio;

    while(cam!=NULL){
        if (cmp(chave, cam->carga) == 0){
            return cam->carga;
        }else{
            cam = cam->prox;
        }
    }

    return NULL;
} 
    /* TODO M04 */
void *lse_remover(t_lse *lista, const void *chave, t_lse_comparador cmp){
    assert(lista != NULL); 
    bool achou=false;
    t_elem * cam = lista->inicio;
    t_elem* ant = NULL;
    while((cam!=NULL) && (!achou)){
        if(cmp(chave, cam->carga)==0){
            achou = true;
        }else{
            ant = cam;  
            cam = cam->prox;
        }
    }
    if(!achou){
        return NULL;
    }else{
        if(lista->inicio == cam){
            lista->inicio = cam->prox;
        }else{
            ant->prox= cam->prox;
        }
        void* carga = cam->carga;
        free(cam);
        lista->tamanho--;
        return carga;
    }
    }
     /* TODO M04 */
int lse_inserir_ordenado(t_lse *l, void *c, t_lse_comparador cmp) { (void)l; (void)c; (void)cmp; return 0; } /* TODO M05 */

void lse_destruir(t_lse *lista, t_lse_destruir_carga destruir_carga) {
    if(lista == NULL){                     
        return;
    }
    t_elem *cam = lista->inicio;
    while(cam!=NULL){
        t_elem *prox = cam->prox;
        if(destruir_carga != NULL){
            destruir_carga(cam->carga);
        }
        free(cam);
        cam = prox;
    }
    free(lista);
}
/* TODO M03 */ 
