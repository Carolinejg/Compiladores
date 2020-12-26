#ifndef TABELA_H
#define TABELA_H

#include "LEXICO.h"
#include <string.h>
#define TAM 40

#define ESCOPO_E_GLOBAL (Escopo == 0)
#define ESCOPO_E_LOCAL (Escopo == 1)

typedef enum TipoSimbolo
{
    INT,
    FLOAT,
    CHAR,
    BOOL,
    VOID
} TipoSimbolo;

typedef struct linha_tabela_simbolos
{
    char nome[TAM];
    int escopo;
    TipoSimbolo tipo;
    int ehFuncao;
    int ehParametro;
    int ehPrototipo;

} linha_tabela_simbolos;

linha_tabela_simbolos tabela[32];
extern int qtd; /* quantidade de registro ocupados na tabela*/
int Escopo;

void adiciona_tabela(TipoSimbolo tipo, char lexema[TAM]);
int verifica_tipo(char lexema[TAM]);
int busca(char lexema[TAM]);
void remove_locais();
const char* toString(TipoSimbolo tipo);
void imprime_tabela();

void adiciona_var_tabela(TipoSimbolo tipo, char lexema[TAM]);
void adiciona_funcao_tabela(TipoSimbolo tipo, char lexema[TAM]);
void adiciona_funcao_tabela_ehprototipo(TipoSimbolo tipo, char lexema[TAM]);
void adiciona_param_tabela(TipoSimbolo tipo, char lexema[TAM]);



#endif
