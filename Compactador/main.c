    #include <stdio.h>
    #include <stdlib.h>
    #include "compactador.h"

int main()
{


        char i=0;
        printf("Escolha entre o menu de opções abaixo:\n1- Compactar Arquivo\n2- Descompactar Arquivo\n3- Sair\n");
        scanf("%c", &i);
        compactar();


    return 0;
}
