#ifndef COMPACTADOR
#define COMPACTADOR
#include "estruturas.h"
void compactar()
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

    converterParaArvore(inicio);

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
        if( bytesRestantes!= 7)
            fputc(byteAtual, arquivoCodificado);

        rewind(arquivoCodificado);

        if(bytesRestantes != 7)
            fputc(bytesRestantes, arquivoCodificado);
        else
            fputc(0, arquivoCodificado);
    }


    fclose(arquivo);
    fclose(arquivoCodificado);
}

#endif
