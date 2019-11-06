#ifndef DESCOMPACTADOR
#define DESCOMPACTADOR
#include "estruturas.h"


void descompactar()
{
    /*Leitura de arquivo*/
    FILE *arquivo;
    char nomeArquivo[25];
    FILE *arquivoDecodificado;
    char nomeNovoArquivo[25];
    NoFila *inicio;
    NoFila *atual;
    NoArvore *aux;
    int i;
    unsigned char quantidadeLetrasDiferentes = 0;
    char qtdLixo = 0;

    {
        printf("Digite o nome do arquivo\n");
        scanf("%s", nomeArquivo);
        arquivo = fopen(nomeArquivo, "rb");

        if(arquivo == NULL)
        {
            printf("Não foi possivel abrir o arquivo, este provavelmente não existe\n");
            exit(0);
        }

        printf("\nDigite o nome do NOVO arquivo:");
        scanf("%s", nomeNovoArquivo);
        arquivoDecodificado = fopen(nomeNovoArquivo, "wb");

        qtdLixo = fgetc(arquivo);
        quantidadeLetrasDiferentes = fgetc(arquivo);

        for(i = 0; i<=quantidadeLetrasDiferentes; i++)
        {
            unsigned char letra = fgetc(arquivo);
            int qtd = 0;
            fread(&qtd, sizeof(int), 1, arquivo);
            NoArvore *novoNo = (NoArvore*) malloc(sizeof(NoArvore));
            novoNo->letra = letra;
            novoNo->esq = NULL;
            novoNo->dir = NULL;
            novoNo->quantidade = qtd;
            novoNo->temValor = 1;
            NoFila *novoNoFila = (NoFila*) malloc(sizeof(NoFila));
            novoNoFila->dado = novoNo;
            novoNoFila->prox = NULL;
            if(i==0)
            {
                inicio = novoNoFila;
                atual = inicio;
            }
            else
            {
                atual->prox = novoNoFila;
                atual = atual->prox;
            }

        }
        converterParaArvore(inicio);


        char byteAtual = 0;
        aux = inicio->dado;
        char byte  = fgetc(arquivo);
        char proximoByte = fgetc(arquivo);
        while(!(feof(arquivo)))
        {
            char cod = (byte << byteAtual);
            cod = cod >> 7;
            if(cod == 0)
                aux = aux->esq;
            else
                aux = aux->dir;

            if(aux->temValor == 1)
            {
                fputc(aux->letra, arquivoDecodificado);
                printf("\n%c",aux->letra);
                aux = inicio->dado;
            }
            byteAtual++;
            if(byteAtual > 7)
            {
                byteAtual = 0;
                byte = proximoByte;
                proximoByte = fgetc(arquivo);
            }
        }

        /*ultimo byte*/
        for(i = 0; i<8-qtdLixo; i ++)
        {
            char cod = (byte << byteAtual);
            cod = cod >> 7;
            if(cod == 0)
                aux = aux->esq;
            else
                aux = aux->dir;

            if(aux->temValor == 1)
            {
                fputc(aux->letra, arquivoDecodificado);
                aux = inicio->dado;
            }
            byteAtual++;
        }

        fclose(arquivoDecodificado);
        fclose(arquivo);

        limparArvore(inicio->dado);
        free(inicio);
    }
}

#endif
