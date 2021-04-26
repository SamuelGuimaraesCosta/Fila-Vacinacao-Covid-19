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

typedef struct Celula {
  Pessoa dado;
  struct Celula *prox;
} Celula;

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

void insereLikePrioridade(Fila *f, Pessoa dado) {
  Celula *nova = novaCelula();

  nova->dado = dado;

  if(dado.pFase1 || dado.idade >= 75) {
    Celula *ant = f->inicio;
    Celula *tmp = f->inicio->prox;

    while(tmp != NULL && tmp->dado.fase <= 1) {
      ant = ant->prox;
      tmp = tmp->prox;
    }

    nova->prox = tmp;
    ant->prox  = nova;

    f->tam++;

    if(tmp == NULL)
      f->fim = nova;
  } else if(dado.idade >= 60 && dado.idade <= 74) {
    Celula *ant = f->inicio;
    Celula *tmp = f->inicio->prox;

    while(tmp != NULL && tmp->dado.fase <= 2) {
      ant = ant->prox;
      tmp = tmp->prox;
    }

    nova->prox = tmp;
    ant->prox  = nova;

    f->tam++;

    if(tmp == NULL)
      f->fim = nova;
  } else if(dado.comorbidade) {
    Celula *ant = f->inicio;
    Celula *tmp = f->inicio->prox;

    while(tmp != NULL && tmp->dado.fase <= 3) {
      ant = ant->prox;
      tmp = tmp->prox;
    }

    nova->prox = tmp;
    ant->prox  = nova;

    f->tam++;

    if(tmp == NULL)
      f->fim = nova;
  } else if(dado.pFase4) {
    Celula *ant = f->inicio;
    Celula *tmp = f->inicio->prox;

    while(tmp != NULL && tmp->dado.fase <= 4) {
      ant = ant->prox;
      tmp = tmp->prox;
    }

    nova->prox = tmp;
    ant->prox  = nova;

    f->tam++;

    if(tmp == NULL)
      f->fim = nova;
  } else {
    f->fim->prox = nova;
    f->fim       = nova;

    f->tam++;
  }
}

void exibirDadosDaPessoa(Pessoa p) {
  if(p.comorbidade)
    printf("--> Nome: %s, Idade: %d, Fase de Vacinacao: %d, Com alguma Comorbidade <--\n", p.nome, p.idade, p.fase);
  else if(p.pFase1)
    printf("--> Nome: %s, Idade: %d, Fase de Vacinacao: %d, Prof. de Saude <--\n", p.nome, p.idade, p.fase);
  else if(p.pFase4)
    printf("--> Nome: %s, Idade: %d, Fase de Vacinacao: %d, Prof. da 4a Fase <--\n", p.nome, p.idade, p.fase);
  else
    printf("--> Nome: %s, Idade: %d, Fase de Vacinacao: %d <--\n", p.nome, p.idade, p.fase);
}

void exibirDadosGeraisDaFila(Fila *f) {
  Celula *tmp = f->inicio->prox;
  if(f->tam == 0){
    printf("\n\n-->Nao existem pessoas cadastradas na fila\n");
  }

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
  printf("2 - Exibir dados gerais da fila de vacinacao.\n");
  printf("3 - Exibir dados de acordo com a prioridade do usuario.\n");
  printf("\nDigite a opcao desejada: ");
  scanf("%d", &op);

  return op;
}

void processoDeInsercaoNaFila(Fila *f) {
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
    printf("\nProfissional que atua na Area da Saude escolhido(a).\n");
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

    insereLikePrioridade(f, p);
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
      printf("\nPessoa com 75 anos ou mais escolhido(a).\n");
      printf("Fase de Vacinacao: 1\n\n");

      p.fase        = 1;
      p.comorbidade = false;
      p.pFase1      = false;
      p.pFase4      = false;

      insereLikePrioridade(f, p);
    } else if(p.idade >= 60 && p.idade <= 74) {
      printf("\nPessoa entre 60 e 74 anos escolhido(a).\n");
      printf("Fase de Vacinacao: 2\n\n");

      p.fase        = 2;
      p.comorbidade = false;
      p.pFase1      = false;
      p.pFase4      = false;

      insereLikePrioridade(f, p);
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
        printf("\nPessoa com alguma comorbidade escolhido(a).\n");
        printf("Fase de Vacinacao: 3\n\n");

        p.fase        = 3;
        p.comorbidade = true;
        p.pFase1      = false;
        p.pFase4      = false;

        insereLikePrioridade(f, p);
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
          printf("\nProfissional da Quarta Fase escolhido(a).\n");
          printf("Fase de Vacinacao: 4\n\n");

          p.fase        = 4;
          p.comorbidade = false;
          p.pFase1      = false;
          p.pFase4      = true;

          insereLikePrioridade(f, p);
        } else {
          printf("\nPessoa Sem Prioridades na Fila escolhido(a).\n");
          printf("Fase de Vacinacao: 5\n\n");

          p.fase        = 5;
          p.comorbidade = false;
          p.pFase1      = false;
          p.pFase4      = false;

          insereLikePrioridade(f, p);
        }
      }
    }
  }
}
void exibirDadosDeAcordoComGrupoDaFila(Fila *f){
  Celula *tmp = f->inicio->prox;
  if(f->tam == 0){
    printf("\n\n-->Nao existem pessoas cadastradas na fila\n");
  }
  printf("\n\n-->Qual fase da vacinacao voce deseja exibir?\n");
  int fase = 0;
  do{
    scanf("%d",&fase);
  }while(fase < 1 || fase > 5);

  while(tmp != NULL){
    if(fase==1){
      if(tmp->dado.fase==1){
      exibirDadosDaPessoa(tmp->dado);
       
      }
    }
    else if(fase==2){
      if(tmp->dado.fase==2){
      exibirDadosDaPessoa(tmp->dado);
      }
    }
     else if(fase==3){
      if(tmp->dado.fase==3){
      exibirDadosDaPessoa(tmp->dado);
      }
    }
     else if(fase==4){
      if(tmp->dado.fase==4){
      exibirDadosDaPessoa(tmp->dado);
      }
    }
    else if(fase==5){
      if(tmp->dado.fase==5){
      exibirDadosDaPessoa(tmp->dado);
      }
    }
  
    tmp = tmp->prox;
    
  }
}
#endif