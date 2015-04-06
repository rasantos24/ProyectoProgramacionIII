#include <allegro.h>
#ifndef PERSONAJES_H_INCLUDED
#define PERSONAJES_H_INCLUDED

struct NAVE
{
     int x,y;
     int nDisp;
     int maxDisp;
     int tick, anchoBala, altoBala,;
     int anchoPersonaje, altoPersonaje;
     int dirBala;
     int tipoNave;
     int vida;

     BITMAP* imgNave;
     BITMAP* imgBala;
     BITMAP* ExplosionEnemigo;

     SAMPLE* dispa;
     SAMPLE* explo;

     void inicia(char* rutaNave , char* rutaBala, int AnchoBala, int AltoBala, int AnchoPersonaje,
                 int AltoPersonaje, int xEne, int yEne, int DirBala, int TipoNave, int Vida, char* musDisparo, char* musExplosion);
     bool temporizador(int tiempo);
     void pinta(BITMAP* buffer, int equis, int ye);
     void mueve();
     void disparo(struct Balas disparos[], BITMAP* buffer);
     void vidas(BITMAP* buffer);
     void victoria(BITMAP* ganar, BITMAP* buffer);
};

void tropaEnemigos(struct NAVE Enemigos[]);
void pintarEnemigos(struct NAVE Enemigos[], BITMAP* buffer, int mover);

void jefeFinal(struct NAVE Jefe[]);
void pintarJefe(struct NAVE Jefe[], BITMAP* buffer, int mover);

void explosionEnemigo(struct NAVE Enemigo, BITMAP* buffer, int& numEnem);
void explosionNave(struct NAVE Nave, BITMAP* buffer, BITMAP* fondo);

void crearBalaEnemigo(struct NAVE Enemigo[], int &raza);
void crearBalaNave(struct NAVE& Nave, struct Balas disparos[]);

void crearBalaJefe(struct NAVE Jefe[], int &raza);

void vicder(BITMAP* derro, BITMAP* buffer);
void explosionJefe(struct NAVE Jefe, BITMAP* buffer, int& numJef);

struct escudo
{
    int x,y;
    int dan;
    int tipo;
};

void iniciarEscudo(struct escudo muralla[]);
void pintarEscudo(struct escudo mura[], BITMAP* imgEscudo, BITMAP* buffer);

#endif // PERSONAJES_H_INCLUDED
