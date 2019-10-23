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

    void inserirNaFila(NoFila *novoNo, NoFila *inicio)
    {
        if(inicio == NULL)
        {
            inicio = novoNo;
        }
        else
        {

            if((*(*inicio).dado).quantidade >= ((*(*novoNo).dado).quantidade))
            {
                NoFila *noAuxiliar = inicio;
                inicio = novoNo;
                novoNo->prox = noAuxiliar;
            }
            else
            {
                NoFila *noAtual = inicio;
                char achou = 0;
                while(achou == 0)
                {
                    if((noAtual->dado)->quantidade <= (novoNo->dado)->quantidade)
                    {
                        if(noAtual->prox == NULL)
                        {
                            achou = 1;
                            noAtual->prox = novoNo;
                        }
                        else if(noAtual->prox->dado->quantidade > novoNo->dado->quantidade)
                        {
                            achou = 1;
                            NoFila *noAuxiliar = noAtual->prox;
                            noAtual->prox = novoNo;
                            novoNo->prox = noAuxiliar;
                        }
                    }
                    noAtual = noAtual->prox;
                }
            }
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

        NoFila *inicio;

        for(int i = 0; i < tamanhoArquivo; i++)
        {
            char letraAtual = textoArquivo[i];
            if(foiPercorrido[i] == 0)
            {
                NoArvore *novoNo;
                novoNo = (NoArvore*)malloc(sizeof(NoArvore));
                (*novoNo).letra = letra;
                (*novoNo).quantidade = 0;
                for(int l=0; l<tamanhoArquivo; l++)
                {
                    if(textoArquivo[l] == letraAtual)
                    {
                        foiPercorrido[l] = 1;
                        (*novoNo).quantidade++;
                    }
                }
                NoFila *novoNoFila;
                novoNoFila = (NoFila*)malloc(sizeof(NoFila));
                inserirNaFila(novoNoFila, inicio);
            }
        }



        /*fim da leitura de arquivo*/

        char letrasNoArquivo[strlen(textoArquivo)];
        printf(textoArquivo);

        scanf("%s", nomeArquivo);

    }







