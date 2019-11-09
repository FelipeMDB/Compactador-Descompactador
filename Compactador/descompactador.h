#ifndef DESCOMPACTADOR
#define DESCOMPACTADOR
#include "estruturas.h"


void descompactar()
{
    /*Leitura de arquivo*/
    FILE *arquivo;
    char nomeArquivo[231];
    FILE *arquivoDecodificado;
    char nomeNovoArquivo[231];

    /*fila de prioridades*/
    NoFila *inicio;
    NoFila *atual;
    NoArvore *aux;

    /*variáveis para auxiliar processos*/
    int i;
    unsigned char quantidadeLetrasDiferentes = 0;
    char qtdLixo = 0;


    /*pede-se nomes do arquivo compactado e para o novo arquivo descompactado*/
    printf("\nDigite o nome do arquivo: ");
    scanf("%s", nomeArquivo);
    arquivo = fopen(nomeArquivo, "rb");

    /*Não há como descompactar um arquivo inexistente ou vazio*/
    if(arquivo == NULL || feof(arquivo))
    {
        printf("\nNão foi possivel abrir o arquivo, este provavelmente não existe ou esta vazio\n");
    }
    else
    {
        printf("\nDigite o nome do NOVO arquivo: ");
        scanf("%s", nomeNovoArquivo);
        arquivoDecodificado = fopen(nomeNovoArquivo, "wb");

        /*guarda quantos bits foram lixo e quantos elementos há na fila de prioridades*/
        qtdLixo = fgetc(arquivo);
        if(feof(arquivo))
        {
            printf("\nO arquivo que voce deseja compactar esta vazio\n\n");
        }
        else
        {
            quantidadeLetrasDiferentes = fgetc(arquivo);

            /*lê formando fila de prioridades*/
            for(i = 0; i<=quantidadeLetrasDiferentes; i++)
            {
                unsigned char letra = fgetc(arquivo);
                unsigned int qtd = 0;
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

            /*converte fila para arvore*/
            converterParaArvore(inicio);

            {
                /*percorre por bits a arvore para recuperar letras*/
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
                        /*printf("\n%c",aux->letra);*/
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
                for(i = 0; i<7-qtdLixo; i ++)
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
            }


            /*fecha arquivos utilizados*/
            fclose(arquivoDecodificado);
            fclose(arquivo);

            /*desaloca ponteiros*/
            limparArvore(inicio->dado);
            free(inicio);

            printf("\nARQUIVO DESCOMPACTADO COM SUCESSO\n");
        }
    }
}

#endif
