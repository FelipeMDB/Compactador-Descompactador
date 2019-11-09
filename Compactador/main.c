    #include <stdio.h>
    #include <stdlib.h>
    #include "compactador.h"
    #include "descompactador.h"

int main()
{

    for(;;)
    {
        char i=0;
        printf("OI");
        printf("\nEscolha entre o menu de opcoes abaixo:\n1- Compactar Arquivo\n2- Descompactar Arquivo\n3- Limpar Tela\n4- Sair\n");
        scanf("%d", &i);
        if(i == 1)
            compactar();
        else if(i == 2)
            descompactar();
        else if(i == 3)
            system("cls");
        else if(i == 4)
            return 0;
    }



    return 0;
}
