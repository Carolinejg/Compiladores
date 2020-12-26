#include<stdlib.h>
#include "tabela_simbolos.h"
#include <string.h>

int qtd=0; /* quantidade de registro ocupados na tabela*/
int Escopo = 0;

void adiciona_tabela(TipoSimbolo tipo, char lexema [TAM])
{
    strcpy(tabela[qtd].nome,lexema);
    tabela[qtd].tipo=tipo;
    tabela[qtd].escopo=Escopo;
    qtd=qtd+1;
}
/***eu passo o lexema ele vai procurar se existe um lexema igual ja declarado,
dentro do meso escopo, se existe ele (busca)
retorna a posição desse lexema na tabela para verifica_tipo que retorna o tipodela*/

int verifica_tipo(char lexema[TAM])
{
    int result = busca(lexema);
    if(result != -1)
    {
        return tabela[result].tipo;
    }
    return -1;
}
int busca(char lexema[TAM])
{
    int i;
    for(i = qtd; i >= 0; i--)
    {
        if (tabela[i].escopo == Escopo)
        {
            if(strcmp(tabela[i].nome, lexema) == 0) return i;
        }
    }
    return -1;
}

void remove_locais()
{
    int i;
    for(i = qtd; i >= 0; i--)
    {
        if(tabela[i].escopo == 1 && tabela[i].ehParametro == 0)
        {
            qtd=qtd-1;
        }
    }
}
const char* toString(TipoSimbolo tipo)
{
    switch(tipo)
    {
        case INT:
            return "int";
        case FLOAT:
            return "float";
        case CHAR:
            return "char";
        case VOID:
            return "void";
    }
    return "erro";
}
void imprime_tabela()
{
    int i;
    printf("%d simbolos\nnome\ttipo\tescopo\t\n", qtd);
    for(i = 0; i < qtd; i++)
    {
        printf("%s\t%s\t%d\t%s\n",
               tabela[i].nome,
               toString(tabela[i].tipo),
               tabela[i].escopo,
               tabela[i].ehFuncao?"FUNC":tabela[i].ehParametro?"PARAM":tabela[i].ehPrototipo?"PROTO":"VAR");
    }
}
/**
    busca_com_erro
    busca lexema na tabela de simbolos
    dá erro SE EXISTIR na tabela
***/

void busca_com_erro(char lexema[TAM])
{
    int indice = busca(lexema);
    if (indice != -1)
    {
        printf("Simbolo duplicado %s\n", lexema);
        exit(-1);
    }
}


void adiciona_var_tabela(TipoSimbolo tipo, char lexema[TAM])
{
    Escopo=0;
    busca_com_erro(lexema);
    adiciona_tabela(tipo, lexema);
    tabela[qtd-1].ehFuncao = 0;
    tabela[qtd-1].ehParametro = 0;
    tabela[qtd-1].ehPrototipo= 0;
}

void adiciona_funcao_tabela(TipoSimbolo tipo, char lexema[TAM])
{
    Escopo = 0;
    busca_com_erro(lexema);
    adiciona_tabela(tipo, lexema);
    tabela[qtd-1].ehFuncao = 1;
    tabela[qtd-1].ehParametro = 0;
    tabela[qtd-1].ehPrototipo= 0;
}
void adiciona_funcao_tabela_ehprototipo(TipoSimbolo tipo, char lexema[TAM])
{
    Escopo = 0;
    busca_com_erro(lexema);
    adiciona_tabela(tipo, lexema);
    tabela[qtd-1].ehFuncao = 1;
    tabela[qtd-1].ehParametro = 0;
    tabela[qtd-1].ehPrototipo= 1;
}
void adiciona_param_tabela(TipoSimbolo tipo, char lexema[TAM])
{
    Escopo = 1;
    busca_com_erro(lexema);
    adiciona_tabela(tipo, lexema);
    tabela[qtd-1].ehFuncao = 1;
    tabela[qtd-1].ehParametro = 1;
    tabela[qtd-1].ehPrototipo= 0;
}

