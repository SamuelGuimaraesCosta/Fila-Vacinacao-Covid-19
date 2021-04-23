#ifndef  FILA_PONTEIRO_H
#define  FILA_PONTEIRO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Pessoa {
  char nome[110];
  int idade, fase;
  bool comorbidade, pFase1, pFase4;
} Pessoa;

typedef struct Celula{
  Pessoa dado;
  struct Celula *prox;
}Celula;

typedef struct Fila {
  Celula *inicio;
  Celula *fim;
  int tam;
} Fila;

Celula *novaCelula() {
  Celula *tmp = (Celula*)malloc(sizeof(Celula));
  tmp->prox = NULL;
  return tmp;
}

void novaFila(Fila *f) {
  Celula *nova = novaCelula();

  f->inicio = nova;
  f->fim    = nova;
  f->tam    = 0;
}

void insereFinalDaFila(Fila *f, Pessoa dado) {
  Celula *nova = novaCelula();

  nova->dado   = dado;

  f->fim->prox = nova;
  f->fim       = nova;
  f->tam++;
}

void exibirDadosDaPessoa(Pessoa p) {
  if(p.comorbidade)
    printf("--> Nome: %s, Idade: %d, Fase de Vacinacao: %d, Com Comorbidade <--\n", p.nome, p.idade, p.fase);
  else if(p.pFase1)
    printf("--> Nome: %s, Idade: %d, Fase de Vacinacao: %d, Prof. de Saude <--", p.nome, p.idade, p.fase);
  else if(p.pFase4)
    printf("--> Nome: %s, Idade: %d, Fase de Vacinacao: %d, Prof. da 4a Fase <--", p.nome, p.idade, p.fase);
  else
    printf("--> Nome: %s, Idade: %d, Fase de Vacinacao: %d <--", p.nome, p.idade, p.fase);
}

void exibirDadosGeraisDaFila(Fila *f) {
  Celula *tmp = f->inicio->prox;

  while(tmp != NULL){
    exibirDadosDaPessoa(tmp->dado);
    tmp = tmp->prox;
  }
}

int tamanhoGeralDaFila(Fila *f) {
  return f->tam;
}

Pessoa desenfileirar(Fila *f) {
  if(f->tam == 0) {
    Pessoa p = {
      "Dado Invalido",
      -1,
      -1,
      false,
      false,
      false
    };
    return p;
  }

  Celula *tmp = f->inicio;

  f->inicio = f->inicio->prox;  
  
  free(tmp);

  f->tam--;

  return f->inicio->dado;
}

int menuOpcoes() {
  int op = 0;
  
  printf("\n\nSistema de Fila de Vacinacao Covid-19  -  v1.0\n\n");
  printf("1 - Cadastrar uma nova pessoa na fila.\n");
  printf("\nDigite a opcao desejada: ");
  scanf("%d", &op);

  return op;
}

void processoDeInsercaoNaFila() {
  int profFaseUm;
  Pessoa entradaPessoa;
  char nome[50], sobrenome[50], completo[110];

  printf("\nA pessoa na qual voce deseja inserir atua na area da saude?\n");
  printf("Digite 1 para SIM e 2 para NAO.\n\n");

  do {
    printf("Insira a opcao: ");
    scanf("%d", &profFaseUm);
    if(profFaseUm < 1 || profFaseUm > 2)
      printf("\nOpcao Incorreta: Digite 1 para SIM e 2 para NAO.\n");
  }while(profFaseUm < 1 || profFaseUm > 2);

  if(profFaseUm == 1) {
    printf("\nProfissional que atua na Area da Saude escolhido.\n");
    printf("Fase de Vacinacao: 1\n\n");
    printf("Insira o nome da Pessoa (MAX. 50 CARACTERES): ");
    scanf("%s", nome);
    printf("\nInsira o sobrenome da Pessoa (MAX. 50 CARACTERES): ");
    scanf("%s", sobrenome);
    strcat(completo, nome);
    strcat(completo, sobrenome);
    printf("\n-- %s --\n", completo);
  }
}

#endif