#include "feria.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char FIN = 'X';

int main() {
  srand((unsigned)time(NULL));
  juego_t juego;
  inicializar_juego(&juego);
  imprimir_terreno(juego);

  char accion;
  printf("Movimiento para Perry: ");
  scanf("%c", &accion);
  realizar_jugada(&juego, accion);
  system("clear");
  imprimir_terreno(juego);

  bool es_valida = true;
  while (es_valida) {

    imprimir_terreno(juego);
    printf("Movimiento para Perry: ");
    printf("\n");
    scanf("%c", &accion);
    realizar_jugada(&juego, accion);

    if (accion == 'X') {
      es_valida = false;
      printf("Juego terminado");
    }

    system("clear");
  }

  return 0;
}
