#include "feria.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Perry
const char PERRY = 'P';
const int MAX_VIDAS = 3;
const int MAX_ENERGIA = 100;
const char ARRIBA = 'W';
const char ABAJO = 'S';
const char DERECHA = 'D';
const char IZQUIERDA = 'A';
const char CAMUFLAJE = 'Q';

// Familiares
const char PHINEAS = 'H';
const char CANDACE = 'C';
const char FERB = 'F';

// Objetos

const char BOMBAS = 'B';
const int CANT_BOMBAS = 10;
const char GOLOSINAS = 'G';
const int CANT_GOLOSINAS = 5;
const char SOMBREROS = 'S';
const int CANT_SOMBREROS = 3;

// Terreno
const int MAX_FILAS = 20;
const int MAX_COLUMNAS = 20;

coordenada_t generar_posicion_aleatoria() {
  coordenada_t coordenada;
  coordenada.fil = rand() % MAX_FILAS;
  coordenada.col = rand() % MAX_COLUMNAS;

  return coordenada;
}

bool limites_terreno(coordenada_t coordenada) {
  return (coordenada.col < MAX_COLUMNAS && coordenada.col >= 0 &&
          coordenada.fil < MAX_FILAS && coordenada.fil >= 0);
}

void inicializar_perry(juego_t *juego) {
  juego->perry.posicion = generar_posicion_aleatoria();
  juego->perry.camuflado = false;
  juego->perry.energia = MAX_ENERGIA;
  juego->perry.vida = MAX_VIDAS;
}

void inicializar_bombas(juego_t *juego) {
  juego->tope_bombas = MAX_BOMBAS;

  for (int i = 0; i < juego->tope_bombas; i++) {
    juego->bombas[i].desactivada = false;
    juego->bombas[i].posicion = generar_posicion_aleatoria();
    juego->bombas[i].timer = 60;
  }
}

void inicializar_herramientas(juego_t *juego) {
  juego->tope_herramientas = 20;

  for (int i = 0; i < juego->tope_herramientas; i++) {
    if (i < CANT_GOLOSINAS) {
      juego->herramientas[i].posicion = generar_posicion_aleatoria();
      juego->herramientas[i].tipo = GOLOSINAS;
    }
    if (i < CANT_SOMBREROS) {
      juego->herramientas[i].posicion = generar_posicion_aleatoria();
      juego->herramientas[i].tipo = SOMBREROS;
    }
  }
}

void inicializar_familiares(juego_t *juego) {
  juego->tope_familiares = 3;
  char familiares[] = {PHINEAS, FERB, CANDACE};

  for (int i = 0; i < juego->tope_familiares; i++) {
    juego->familiares[i].posicion = generar_posicion_aleatoria();
    juego->familiares[i].inicial_nombre = familiares[i];
  }
}

void inicializar_juego(juego_t *juego) {
  inicializar_perry(juego);
  inicializar_familiares(juego);
  inicializar_herramientas(juego);
  inicializar_bombas(juego);
}

// void realizar_jugada(juego_t *juego, char accion) {
//
//   coordenada_t posicion_actual = juego->perry.posicion;
//   if (accion == ARRIBA) {
//     posicion_actual.col++;
//   } else if (accion == ABAJO) {
//     posicion_actual.col--;
//   } else if (accion == DERECHA) {
//     posicion_actual.fil++;
//   } else if (accion == IZQUIERDA) {
//     posicion_actual.fil--;
//   } else if (accion == CAMUFLAJE) {
//     if (!juego->perry.camuflado) {
//       juego->perry.camuflado = true;
//     }
//   } else {
//     printf("Jugada invalida");
//   }
// }

void cargar_perry(juego_t *juego, char terreno[MAX_FILAS][MAX_COLUMNAS]) {
  if (limites_terreno(juego->perry.posicion)) {
    terreno[juego->perry.posicion.fil][juego->perry.posicion.col] = PERRY;
  }
}

void cargar_bombas(juego_t *juego, char terreno[MAX_FILAS][MAX_COLUMNAS]) {
  for (int i = 0; i < CANT_BOMBAS; i++) {
    if (limites_terreno(juego->bombas[i].posicion)) {
      terreno[juego->bombas[i].posicion.fil][juego->bombas[i].posicion.col] =
          BOMBAS;
    }
  }
}

void cargar_familiares(juego_t *juego, char terreno[MAX_FILAS][MAX_COLUMNAS]) {
  for (int i = 0; i < juego->tope_familiares; i++) {
    if (limites_terreno(juego->familiares[i].posicion)) {
      terreno[juego->familiares[i].posicion.fil]
             [juego->familiares[i].posicion.col] =
                 juego->familiares[i].inicial_nombre;
    }
  }
}

void cargar_herramientas(juego_t *juego,
                         char terreno[MAX_FILAS][MAX_COLUMNAS]) {
  for (int i = 0; i < juego->tope_herramientas; i++) {
    if (limites_terreno(juego->herramientas[i].posicion)) {
      if (i < CANT_SOMBREROS) {
        terreno[juego->herramientas[i].posicion.fil]
               [juego->herramientas[i].posicion.col] = SOMBREROS;
      } else {
        terreno[juego->herramientas[i].posicion.fil]
               [juego->herramientas[i].posicion.col] = GOLOSINAS;
      }
    }
  }
}

void imprimir_terreno(juego_t juego) {

  char terreno[MAX_FILAS][MAX_COLUMNAS];

  for (int i = 0; i < MAX_FILAS; i++) {
    for (int j = 0; j < MAX_COLUMNAS; j++) {
      terreno[i][j] = ' ';
      cargar_perry(&juego, terreno);
      cargar_bombas(&juego, terreno);
      cargar_herramientas(&juego, terreno);
      cargar_familiares(&juego, terreno);
    }
  }

  for (int i = 0; i < MAX_FILAS; i++) {
    for (int j = 0; j < MAX_COLUMNAS; j++) {
      printf("|%c", terreno[i][j]);
    }
    printf("\n");
  }
}

int main() {
  srand((unsigned)time(NULL));
  juego_t juego;
  inicializar_juego(&juego);
  imprimir_terreno(juego);
}
