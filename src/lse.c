#include "lse.h"
#include <stddef.h>
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
    novo->carga = carga;
    novo->prox=NULL;

    return novo;
}
/* Stubs intencionalmente incompletos; testes devem falhar ate implementacao. */
t_lse *lse_criar(void) {
    t_lse* nova = malloc(sizeof(t_lse));
    if(nova == NULL){
        return NULL
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
    if(lista == NULL || lista-> == NULL){
        return NULL;
    }
    return lista->inicio->carga;
    }
     /* TODO M03 */
int lse_inserir_inicio(t_lse *lista, void *carga){
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
void *lse_remover_inicio(t_lse *l) { (void)l; return NULL; } /* TODO M04 */
void *lse_buscar(const t_lse *l, const void *ch, t_comparador cmp) { (void)l; (void)ch; (void)cmp; return NULL; } /* TODO M04 */
void *lse_remover(t_lse *l, const void *ch, t_comparador cmp) { (void)l; (void)ch; (void)cmp; return NULL; } /* TODO M04 */
int lse_inserir_ordenado(t_lse *l, void *c, t_comparador cmp) { (void)l; (void)c; (void)cmp; return 0; } /* TODO M05 */
void lse_destruir(t_lse *l, void (*destruir)(void *)) { (void)l; (void)destruir; /* TODO M03 */ }
