#include <allegro.h>
#include "personajes.h"
#ifndef DISPAROS_H_INCLUDED
#define DISPAROS_H_INCLUDED

struct Balas{
    int x , y;
    int dx , dy;
};

bool choque(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

bool crear_bala(int& n_disparos, const int max_disparos,struct Balas disparos[], const int X, const int Y ,const int dy);

void pintar_bala(int& n_disparos, const int max_disparos,struct Balas disparos[], BITMAP* buffer, BITMAP* bala, int ancho, int alto);

void eliminar(struct Balas disparos[], int& nDisp, int cont);

bool eliminarNave(struct NAVE& Nave, struct NAVE& Enemigo, struct Balas Bala[]);

void elimina_bala(int& n_disparos, const int max_disparos,struct Balas disparos[], const int ANCHO, const int ALTO);

void eliminarEscudo(struct NAVE &Nave, struct escudo es[], struct Balas bala[]);

#endif // DISPAROS_H_INCLUDED
