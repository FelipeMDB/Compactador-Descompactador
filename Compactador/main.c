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


void juntarNos(NoFila *noUm, NoFila *noDois)
{
    NoArvore *novoNoArvore;
    novoNoArvore = (NoArvore*)malloc(sizeof(NoArvore));
    novoNoArvore->letra = NULL;
    novoNoArvore->quantidade = noUm->dado->quantidade+noDois->dado->quantidade;
    NoArvore *noAuxiliar = (NoArvore*)malloc(sizeof(NoArvore));
    NoArvore *outroNoAuxiliar = (NoArvore*)malloc(sizeof(NoArvore));
    noAuxiliar = noUm->dado;
    outroNoAuxiliar = noDois->dado;
    if(noAuxiliar->quantidade < outroNoAuxiliar->quantidade)
    {
        novoNoArvore->esq = noAuxiliar;
        novoNoArvore->dir = outroNoAuxiliar;
    }
    else
    {
        novoNoArvore->esq = outroNoAuxiliar;
        novoNoArvore->dir = noAuxiliar;
    }

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
            NoFila noAuxiliar = *inicio;                    /*um n� fila recebe o conte�do do ponteiro inicio*/
            *inicio = *novoNoFila;                          /*o conteudo do inicio passa a ser o que � novoNoFila*/
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
                        /*noAtual->prox = (NoFila*)malloc(sizeof(NoFila)); /*Ponteiro pr�ximo de noAtual � alocado na mem�ria*/
                        noAtual->prox = novoNoFila;                     /*Conte�do do ponteiro passa a ser o novo n� fila*/
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
        printf("N�o foi possivel abrir o arquivo\n");
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


    /*cria��o da fila de priorjdades*/
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


    /*convertendo a fila em �rvore*/


    /*teste de ordem da fila*/

    NoFila *aux = inicio;
    while(aux != NULL)
    {
        printf("\n%c, %d", (unsigned char)(aux->dado)->letra, (int)(aux->dado)->quantidade);
        aux = aux->prox;
    }

    return 0;
}
