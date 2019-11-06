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
    unsigned char i;
    /*cria��o da fila de priorjdades*/
    inicio = (NoFila*)malloc(sizeof(NoFila));
    inicio->dado = NULL;
    inicio->prox = NULL;
    char quantidadeLetrasDiferentes = 0;

    {
        unsigned char letra;
        int quantidade[255];

        printf("Digite o nome do arquivo\n");
        scanf("%s", nomeArquivo);
        arquivo = fopen(nomeArquivo, "rb");

        if(arquivo == NULL)
        {
            printf("N�o foi possivel abrir o arquivo\n");
            exit(0);
        }


        for(i = 0; i < 255; i++)
            quantidade[i] = 0;

        letra = (unsigned char) fgetc(arquivo);
        while (!(feof(arquivo)))
        {
            quantidade[letra] = quantidade[letra] + 1;
            letra = (unsigned char)fgetc(arquivo);
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
    fputc(quantidadeLetrasDiferentes-1, arquivoCodificado);

    aux = inicio;
    while(aux != NULL)
    {
        fputc(aux->dado->letra, arquivoCodificado);
        fwrite(&(aux->dado->quantidade), 4, 1, arquivoCodificado);
        aux = aux->prox;
    }

    converterParaArvore(inicio);

    {
        char codigo[256];
        char *codigo = (char*)malloc(sizeof(char));
        codificarLetras(inicio->dado->esq, 0, 0, codigo);
        codificarLetras(inicio->dado->dir, 1, 0, codigo);
        free(codigo);
    }

    rewind(arquivo);

    for(i = 0; i<codigosLetras['o'].qtosBits; i++)
    {
        printf("%d\n", codigosLetras['o'].codigo[i]);
    }

    {
        char bytesRestantes = 7;
        char byteAtual = 0;
        unsigned char letra = fgetc(arquivo);
        while(!(feof(arquivo)))
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

    limparArvore(inicio->dado);
    free(inicio);
}

#endif
