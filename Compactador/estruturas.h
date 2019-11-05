#ifndef ESTRUTURAS
#define ESTRUTURAS
typedef struct NoArvore
{
    char temValor;
    unsigned char letra;
    int quantidade;
    struct NoArvore *esq;
    struct NoArvore *dir;
} NoArvore;


typedef struct NoFila
{
    NoArvore *dado;
    struct NoFila *prox;
} NoFila;

typedef struct
{
    char codigo[8];
    char qtosBits;
}CodLetra;


NoArvore* juntarNos(NoArvore *noUm, NoArvore *noDois)
{
    NoArvore *raiz = (NoArvore*)malloc(sizeof(NoArvore));
    raiz->quantidade = (noUm->quantidade)+(noDois->quantidade);
    raiz->temValor = 0;
    raiz->esq = noUm;
    raiz->dir = noDois;

    return raiz;
}

NoFila* desenfileirar(NoFila *inicio)
{
    NoFila *noAuxiliar = (NoFila*)malloc(sizeof(NoFila));
    *noAuxiliar = *inicio;
    noAuxiliar->prox = NULL;
    *inicio = *(inicio->prox);
    return noAuxiliar;
}

void inserirNaFila(NoArvore *novoNo, NoFila *inicio)
{
    NoFila *novoNoFila;
    novoNoFila = (NoFila*)malloc(sizeof(NoFila));
    novoNoFila->dado = novoNo;
    novoNoFila->prox = NULL;

    if(inicio->dado == NULL)
    {
        inicio->dado = novoNo;
    }
    else
    {
        if((inicio->dado)->quantidade >= (novoNoFila->dado)->quantidade)
        {
            NoFila noAuxiliar = *inicio;                    /*um nó fila recebe o conteúdo do ponteiro inicio*/
            *inicio = *novoNoFila;                          /*o conteudo do inicio passa a ser o que é novoNoFila*/
            inicio->prox = (NoFila*)malloc(sizeof(NoFila));  /*o prox de inicio recebe um malloc*/
            *(inicio->prox) = noAuxiliar;                      /*o conteudo do prox de inicio recebe o noAuxiliar*/
        }
        else
        {
            NoFila *noAtual = inicio;  /*Ponteiro que caminha pela fila*/
            char achou = 0;
            while(achou == 0)
            {
                if((noAtual->dado)->quantidade <= (novoNoFila->dado)->quantidade)
                {
                    if(noAtual->prox == NULL)
                    {
                        achou = 1;
                        noAtual->prox = novoNoFila;                     /*Conteúdo do ponteiro passa a ser o novo nó fila*/
                    }
                    else if(((noAtual->prox)->dado)->quantidade > (novoNoFila->dado)->quantidade)
                    {
                        achou = 1;
                        NoFila noAuxiliar = *(noAtual->prox); /*noAuxiliar recebe conteudo de prox de noAtual*/
                        *(noAtual->prox) = *novoNoFila;        /*conteudo de prox passa a ser novoNoFila*/

                        noAtual->prox->prox = (NoFila*)malloc(sizeof(NoFila)); /*aloca prox de novoNoFila*/
                        *(noAtual->prox->prox) = noAuxiliar;     /*guarda noAuxiliar no prox*/
                    }
                }
                noAtual = noAtual->prox;
            }
        }
    }
}


CodLetra codigosLetras[255];

void codificarLetras(NoArvore* atual, char cod, char indice, char codigo[])
{
    codigo[indice] = cod;
    if(atual->temValor == 0)
    {
        codificarLetras(atual->esq, 0, indice+1, codigo);
        codificarLetras(atual->dir, 1, indice+1, codigo);
    }
    else
    {
        int i;
        for(i=0; i<=indice; i++)
            codigosLetras[atual->letra].codigo[i] = codigo[i];
        codigosLetras[atual->letra].qtosBits = indice+1;
    }
}



void converterParaArvore(NoFila *inicio)
{
    /*convertendo a fila em árvore*/

    while(inicio->prox!= NULL)
    {
        if(inicio->prox->prox == NULL)
        {
            NoFila *dir = (NoFila*)malloc(sizeof(NoFila));
            NoFila *esq = desenfileirar(inicio);
            *dir = *inicio;
            dir->dado = (NoArvore*)malloc(sizeof(NoArvore));
            *(dir->dado) = *(inicio->dado);
            inicio->dado->temValor = 0;
            inicio->dado->quantidade  = (dir->dado->quantidade) + (esq->dado->quantidade);
            inicio->dado->esq = esq->dado;
            inicio->dado->dir = dir->dado;
            inicio->prox = NULL;
        }
        else
        {
            NoFila *esq = desenfileirar(inicio);
            NoFila *dir = desenfileirar(inicio);
            inserirNaFila(juntarNos(esq->dado, dir->dado), inicio);
        }
    }
}

#endif
