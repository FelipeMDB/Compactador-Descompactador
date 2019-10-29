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

    void inserirNaArvore(NoArvore *novoNo, NoArvore *raiz)
    {

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
        letra = fgetc(arquivo);
        while (letra != EOF)
        {
            /*printf ("%c", letra);*/
            letra = fgetc(arquivo);
            tamanhoArquivo++;
        }
        char textoArquivo[tamanhoArquivo];
        rewind(arquivo);
        fread(textoArquivo, sizeof(char), tamanhoArquivo, arquivo);
        fclose(arquivo);


        char foiPercorrido[tamanhoArquivo];
        int i;
        for(i = 0; i < tamanhoArquivo; i++)
            foiPercorrido[i] = 0;

        NoFila *inicio = (NoFila*)malloc(sizeof(NoFila));
        inicio->dado = NULL;
        inicio->prox = NULL;
        for(i = 0; i < tamanhoArquivo; i++)
        {
            char letraAtual = textoArquivo[i];

            NoArvore *novoNo;
            novoNo = (NoArvore*)malloc(sizeof(NoArvore));

            if(foiPercorrido[i] == 0)
            {
                 novoNo->letra = letraAtual;
                 novoNo->quantidade = 0;
                int l;
                for(l=0; l<tamanhoArquivo; l++)
                {
                    if(textoArquivo[l] == letraAtual)
                    {
                        foiPercorrido[l] = 1;
                        (novoNo->quantidade) = (novoNo->quantidade) + 1;
                    }
                }
                inserirNaFila(novoNo, inicio);
            }
        }



        /*fim da leitura de arquivo*/

        char letrasNoArquivo[strlen(textoArquivo)];
        printf(textoArquivo);


        NoFila *aux = inicio;
        while(aux != NULL)
        {
            printf("\n%c, %d", (unsigned char)(aux->dado)->letra, (int)(aux->dado)->quantidade);
            aux = aux->prox;
        }

        return 0;
    }







