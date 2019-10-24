    #include <stdio.h>
    #include <stdlib.h>
typedef struct NoArvore
    {
        char letra;
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
        NoArvore* novo = (NoArvore*)malloc(sizeof(NoArvore));
        novo->dir = novoNo->dir;
        novo->esq = novoNo->esq;
        novo->letra = novoNo->letra;
        novo->quantidade = novoNo->quantidade;

        NoFila *novoNoFila;
        novoNoFila = (NoFila*)malloc(sizeof(NoFila));
        novoNoFila->dado = novoNo;
        novoNoFila->prox = NULL;
        if(inicio->dado == NULL)
        {
            inicio->dado = novo;
        }
        else
        {

            /*if((*(*inicio).dado).quantidade >= ((*(*novoNoFila).dado).quantidade))
            {
                NoFila *noAuxiliar = inicio;
                inicio = novoNoFila;
                novoNoFila->prox = noAuxiliar;
            }
            else
            {*/
                NoFila *noAtual = inicio;
                char achou = 0;
                while(achou == 0)
                {
                    if((noAtual->dado)->quantidade <= (novoNoFila->dado)->quantidade)
                    {
                        if(noAtual->prox == NULL)
                        {
                            achou = 1;
                            noAtual->prox = novoNoFila;
                        }
                        else if(noAtual->prox->dado->quantidade > novoNoFila->dado->quantidade)
                        {
                            achou = 1;
                            NoFila *noAuxiliar = noAtual->prox;
                            noAtual->prox = novoNoFila;
                            novoNoFila->prox = noAuxiliar;
                        }
                    }
                    noAtual = noAtual->prox;
                }
            //}
        }
    }

    void main()
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
            //printf ("%c", letra);
            letra = fgetc(arquivo);
            tamanhoArquivo++;
        }
        char textoArquivo[tamanhoArquivo];
        rewind(arquivo);
        fread(textoArquivo, sizeof(char), tamanhoArquivo, arquivo);
        fclose(arquivo);


        char foiPercorrido[tamanhoArquivo];
        for(int i = 0; i < tamanhoArquivo; i++)
            foiPercorrido[i] = 0;

        NoFila *inicio = (NoFila*)malloc(sizeof(NoFila));
        inicio->dado = NULL;
        inicio->prox = NULL;
        for(int i = 0; i < tamanhoArquivo; i++)
        {
            char letraAtual = textoArquivo[i];

                NoArvore *novoNo;
                novoNo = (NoArvore*)malloc(sizeof(NoArvore));
            if(foiPercorrido[i] == 0)
            {
                (*novoNo).letra = (unsigned char)letraAtual;
                (*novoNo).quantidade = 0;
                for(int l=0; l<tamanhoArquivo; l++)
                {
                    if(textoArquivo[l] == letraAtual)
                    {
                        foiPercorrido[l] = 1;
                        (*novoNo).quantidade++;
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
            printf(aux->dado->letra);
            aux = aux->prox;
        }

        scanf("%s", nomeArquivo);

    }







