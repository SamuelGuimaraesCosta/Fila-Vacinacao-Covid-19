#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fila_ponteiro.h"

int main(void) {

  int entrada = -1;

  do {
    entrada = menuOpcoes();

    printf("\nA opcao digitada foi: %d\n", entrada);

    switch(entrada) {
      case 1:
        processoDeInsercaoNaFila();
        break;
      case 0:
        break;
      default:
        printf("\nOpcao digitada invalida!\n");
        break;
    }
  } while(entrada != 0);

  if(entrada == 0) {
    printf("\nSistema de fila de vacinacao finalizado corretamente.  -  v1.0\n");
  } else {
    printf("\nParece que o sistema nao foi finalizado corretamente.\n");
  }
}