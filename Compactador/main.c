    #include <stdio.h>
    #include <stdlib.h>
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


/*void inserirNaArvore(NoArvore *novoNo, NoArvore *raiz)
{

}*/

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

int main()
{
    /*Leitura de arquivo*/
    FILE *arquivo;
    char nomeArquivo[25];
    FILE *arquivoCodificado;
    char nomeNovoArquivo[25];
    NoFila *inicio;
    NoFila *aux;
    int i;
    /*criação da fila de priorjdades*/
    inicio = (NoFila*)malloc(sizeof(NoFila));
    inicio->dado = NULL;
    inicio->prox = NULL;
    char quantidadeLetrasDiferentes = 0;



    {
        char letra;
        int quantidade[255];

        printf("Digite o nome do arquivo\n");
        scanf("%s", nomeArquivo);
        arquivo = fopen(nomeArquivo, "rb");

        if(arquivo == NULL)
        {
            printf("Não foi possivel abrir o arquivo\n");
            exit(0);
        }


        for(i = 0; i < 255; i++)
            quantidade[i] = 0;

        letra = fgetc(arquivo);
        while (letra != EOF)
        {
            quantidade[letra] = quantidade[letra] + 1;
            letra = fgetc(arquivo);
        }

        /*armazenamento das letras e suas respectivas quantidades na fila de prioridades*/
        for(i = 0; i < 255; i++)
        {
            if(quantidade[i] != 0)
            {
                NoArvore *novoNo;
                novoNo = (NoArvore*)malloc(sizeof(NoArvore));

                novoNo->letra = i;

                novoNo->quantidade = quantidade[i];
                novoNo->temValor = 1;
                novoNo->esq = NULL;
                novoNo->dir = NULL;
                inserirNaFila(novoNo, inicio);
                quantidadeLetrasDiferentes++;
            }
        }
    }


    /*teste de ordem da fila*/
    aux = inicio;
    while(aux != NULL)
    {
        printf("\n%c, %d", (unsigned char)(aux->dado)->letra, (int)(aux->dado)->quantidade);
        aux = aux->prox;
    }


    /*Escrevendo fila de prioridades no arquivo codificado*/
    printf("\nDigite o nome do novo arquivo: ");
    scanf("%s", &nomeNovoArquivo);
    arquivoCodificado = fopen(nomeNovoArquivo, "wb");
    fputc(' ', arquivoCodificado);
    fputc(quantidadeLetrasDiferentes, arquivoCodificado);

    aux = inicio;
    while(aux != NULL)
    {
        fputc(aux->dado->letra, arquivoCodificado);
        fprintf(arquivoCodificado, "%d",aux->dado->quantidade);
        aux = aux->prox;
    }

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

    {
        char codigo[8];
        codificarLetras(inicio->dado->esq, 0, 0, codigo);
        codificarLetras(inicio->dado->dir, 1, 0, codigo);
    }

    rewind(arquivo);

    for(i = 0; i<codigosLetras['o'].qtosBits; i++)
    {
        printf("%d\n", codigosLetras['o'].codigo[i]);
    }

    {
        char bytesRestantes = 7;
        char byteAtual = 0;
        char letra = fgetc(arquivo);
        while(letra != EOF)
        {
            for(i = 0; i < codigosLetras[letra].qtosBits; i++)
            {
                char cod = codigosLetras[letra].codigo[i] << bytesRestantes;
                byteAtual = byteAtual^cod;
                bytesRestantes--;
                if(bytesRestantes == -1)
                {
                    bytesRestantes = 7;
                    fputc(byteAtual, arquivoCodificado);
                    byteAtual = 0;
                }
            }
            letra = fgetc(arquivo);
        }

        rewind(arquivoCodificado);

        if(bytesRestantes != 7)
            fputc(bytesRestantes+1, arquivoCodificado);
        else
            fputc(0, arquivoCodificado);
    }


    fclose(arquivo);
    fclose(arquivoCodificado);

    return 0;


}
