    #include <stdio.h>
    #include <stdlib.h>
typedef struct NoArvore
{
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


/*void inserirNaArvore(NoArvore *novoNo, NoArvore *raiz)
{

}*/

*NoArvore juntarNos(NoArvore *noUm, NoArvore *noDois)
{
    NoArvore *raiz = (NoArvore*)malloc(sizeof(NoArvore));
    raiz->letra = NULL;
    raiz->quantidade = noUm->dado->quantidade+noDois->dado->quantidade;

    raiz->esq = noUm;
    raiz->dir = noDois;

    return raiz;
}

*NoFila desenfileirar(NoFila *inicio)
{
    NoFila *noAuxiliar = (NoFila*)malloc(sizeof(NoFila));
    *noAuxiliar = *inicio;
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
                        /*noAtual->prox = (NoFila*)malloc(sizeof(NoFila)); /*Ponteiro próximo de noAtual é alocado na memória*/
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

int main()
{
    /*Leitura de arquivo*/
    FILE *arquivo;
    char nomeArquivo[25];
    char letra;
    int tamanhoArquivo = 0;

    printf("Digite o nome do arquivo\n");
    scanf("%s", nomeArquivo);
    arquivo = fopen(nomeArquivo, "rb");

    if(arquivo == NULL)
    {
        printf("Não foi possivel abrir o arquivo\n");
        exit(0);
    }


    int quantidade[255];
    int i;
    for(i = 0; i < 255; i++)
        quantidade[i] = 0;

    letra = fgetc(arquivo);
    while (letra != EOF)
    {
        quantidade[letra] = quantidade[letra] + 1;
        letra = fgetc(arquivo);
    }
    fclose(arquivo);


    /*criação da fila de priorjdades*/
    NoFila *inicio = (NoFila*)malloc(sizeof(NoFila));
    inicio->dado = NULL;
    inicio->prox = NULL;

    /*armazenamento das letras e suas respectivas quantidades na fila de prioridades*/
    for(i = 0; i < 255; i++)
    {
        if(quantidade[i] != 0)
        {
            NoArvore *novoNo;
            novoNo = (NoArvore*)malloc(sizeof(NoArvore));

            novoNo->letra = i;
            novoNo->quantidade = quantidade[i];
            inserirNaFila(novoNo, inicio);
        }
    }



    /*convertendo a fila em árvore*/



    while(*inicio->prox != NULL)
    {
        NoFila *esq = desenfileirar(inicio);
        NoFila *dir = desenfileirar(inicio);
        inserirNaFila(juntarNos(esq->dado, dir->dado));
    }

    /*teste de ordem da fila*/

    NoFila *aux = inicio;
    while(aux != NULL)
    {
        printf("\n%c, %d", (unsigned char)(aux->dado)->letra, (int)(aux->dado)->quantidade);
        aux = aux->prox;
    }

     NoArvore *auxi = inicio;
     NoArvore *auxi2 = NULL;
    while(aux != NULL)
    {
        printf("\n%c, %d", (unsigned char)(auxi->dado)->letra, (int)(auxi->dado)->quantidade);
        auxi = auxi->dir;
        auxi2 = auxi2->esq;
        printf("\n%c, %d", (unsigned char)(auxi2->dado)->letra, (int)(auxi2->dado)->quantidade);
    }

    return 0;


}
