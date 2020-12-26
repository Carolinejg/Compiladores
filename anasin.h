#include<stdio.h>
#include "LEXICO.h"
#include "tabela_simbolos.h"

int prog();
int decl();
int decl_var();
int tipo();
int tipos_param();
int cmd();
int atrib();
int expr();
int expr_simp();
int termo();
int fator();
int op_rel();
void prog_sem_retorno();
void prog_prototipo();
void prog_tipo (TipoSimbolo tipoFuncao);


int tiposParam();
int cabecalho();


int VerificarSinal(enum Sinal);
int VerificarPR(enum PalavraReservada);

Token token;
FILE *arquivo;

