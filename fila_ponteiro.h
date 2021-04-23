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
  int profFaseUm, pCom, profFaseQuatro;
  Pessoa p;
  char nome[50], sobrenome[50], completo[110] = "";

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

    printf("Insira o Nome da Pessoa (MAX. 50 CARACTERES | SEM ESPACOS): ");
    scanf("%s", nome);
    printf("\nInsira o Sobrenome da Pessoa (MAX. 50 CARACTERES | SEM ESPACOS): ");
    scanf("%s", sobrenome);

    strcat(completo, nome);
    strcat(completo, " ");
    strcat(completo, sobrenome);
    strcpy(p.nome, completo);

    printf("\nInsira a Idade da Pessoa: ");
    scanf("%d", &p.idade);

    p.fase        = 1;
    p.comorbidade = false;
    p.pFase1      = true;
    p.pFase4      = false;
  } else {
    printf("Insira o Nome da Pessoa (MAX. 50 CARACTERES | SEM ESPACOS): ");
    scanf("%s", nome);
    printf("\nInsira o Sobrenome da Pessoa (MAX. 50 CARACTERES | SEM ESPACOS): ");
    scanf("%s", sobrenome);

    strcat(completo, nome);
    strcat(completo, " ");
    strcat(completo, sobrenome);
    strcpy(p.nome, completo);

    printf("\nInsira a Idade da Pessoa: ");
    scanf("%d", &p.idade);

    if(p.idade >= 75) {
      printf("\nPessoa com 75 anos ou mais escolhido.\n");
      printf("Fase de Vacinacao: 1\n\n");

      p.fase        = 1;
      p.comorbidade = false;
      p.pFase1      = false;
      p.pFase4      = false;
    } else if(p.idade >= 60 && p.idade <= 74) {
      printf("\nPessoa entre 60 e 74 anos escolhido.\n");
      printf("Fase de Vacinacao: 2\n\n");

      p.fase        = 2;
      p.comorbidade = false;
      p.pFase1      = false;
      p.pFase4      = false;
    } else {
      printf("\nA pessoa na qual voce deseja inserir tem alguma comorbidade que se encaixe na fase 3 de vacinacao?\n");
      printf("Digite 1 para SIM e 2 para NAO.\n\n");

      do {
        printf("Insira a opcao: ");
        scanf("%d", &pCom);

        if(pCom < 1 || pCom > 2)
          printf("\nOpcao Incorreta: Digite 1 para SIM e 2 para NAO.\n");
      }while(pCom < 1 || pCom > 2);

      if(pCom == 1) {
        printf("\nPessoa com alguma comorbidade escolhida.\n");
        printf("Fase de Vacinacao: 3\n\n");

        p.fase        = 3;
        p.comorbidade = true;
        p.pFase1      = false;
        p.pFase4      = false;
      } else {
        printf("\nA pessoa na qual voce deseja inserir eh um profissional da 4a fase?\n");
        printf("Digite 1 para SIM e 2 para NAO.\n\n");

        do {
          printf("Insira a opcao: ");
          scanf("%d", &profFaseQuatro);

          if(profFaseQuatro < 1 || profFaseQuatro > 2)
            printf("\nOpcao Incorreta: Digite 1 para SIM e 2 para NAO.\n");
        }while(profFaseQuatro < 1 || profFaseQuatro > 2);

        if(profFaseQuatro == 1) {
          printf("\nProfissional da Quarta Fase escolhido.\n");
          printf("Fase de Vacinacao: 4\n\n");

          p.fase        = 4;
          p.comorbidade = false;
          p.pFase1      = false;
          p.pFase4      = true;
        } else {
          printf("\nPessoa Sem Prioridade.\n");
          printf("Fase de Vacinacao: 5\n\n");

          p.fase        = 5;
          p.comorbidade = false;
          p.pFase1      = false;
          p.pFase4      = false;
        }
      }
    }
  }

  printf("\nN: %s, I: %d, F: %d, C: %s, PF1: %s, PF4: %s", p.nome, p.idade, p.fase, p.comorbidade ? "true" : "false", p.pFase1 ? "true" : "false", p.pFase4 ? "true" : "false");
}

#endif