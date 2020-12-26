#include "LEXICO.h"
#include "anasin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()

{

    inicializarTabelaDePR();
    arquivo = abrirArquivo("teste.txt");
    if (arquivo == NULL) return 1;

    while (prog())
    {
        printf("\n");

    }

    imprime_tabela();

    return 0;
}
