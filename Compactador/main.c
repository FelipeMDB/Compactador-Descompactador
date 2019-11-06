    #include <stdio.h>
    #include <stdlib.h>
    #include "compactador.h"
    #include "descompactador.h"

int main()
{

    for(;;)
    {
        system("cls");
        char i=0;
        printf("Escolha entre o menu de opções abaixo:\n1- Compactar Arquivo\n2- Descompactar Arquivo\n3- Sair\n");
        scanf("%d", &i);
        if(i==1)
            compactar();
        else if(i == 2)
        {
            descompactar();
        }
        else
            return 0;
    }



    return 0;
}
