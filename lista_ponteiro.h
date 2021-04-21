#ifndef  FILA_PONTEIRO_H
#define  FILA_PONTEIRO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Pessoa {
  char nome[100];
  int idade, fase;
  bool comorbidade, pFase1, pFase4;
} Pessoa;

typedef struct Celula {
  Pessoa dado;
  struct Celula *prox;
} Celula;

typedef struct Fila {
  Celula *inicio;
  Celula *fim;
  int tam;
} Fila;

Celula novaCelula() {
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
  if(p->comorbidade)
    printf("--> Nome: %s, Idade: %d, Fase de Vacinacao: %d, Com Comorbidade <--\n");
  else if(p->pFase1)
    printf("--> Nome: %s, Idade: %d, Fase de Vacinacao: %d, Prof. de Saude <--");
  else if(p->pFase4)
    printf("--> Nome: %s, Idade: %d, Fase de Vacinacao: %d, Prof. da 4a Fase <--");
  else
    printf("--> Nome: %s, Idade: %d, Fase de Vacinacao: %d <--");
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

#endif