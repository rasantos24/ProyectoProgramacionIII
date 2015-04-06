#include "personajes.h"
#include "disparos.h"
#include <allegro.h>
#include "menu.h"

#define ANCHO 600
#define ALTO  600

void NAVE::inicia(char* rutaNave , char* rutaBala, int AnchoBala, int AltoBala, int AnchoPersonaje,
                  int AltoPersonaje, int xEne, int yEne, int DirBala, int TipoNave, int Vida, char* musDisparo, char* musExplosion)
{
     x = xEne; y = yEne;
     nDisp = 0; maxDisp = 2;
     imgNave = load_bitmap(rutaNave,NULL);
     imgBala = load_bitmap(rutaBala,NULL);
     tick = 0;
     anchoBala = AnchoBala;
     altoBala = AltoBala;
     anchoPersonaje = AnchoPersonaje;
     altoPersonaje = AltoPersonaje;
     dirBala = DirBala;
     tipoNave = TipoNave;
     vida = Vida;
     ExplosionEnemigo = load_bitmap("Recursos/pum_enemigo1.bmp",NULL);
     dispa = load_wav(musDisparo);
     explo = load_wav(musExplosion);
}

bool NAVE::temporizador(int tiempo)
{
    tick++;
    if(tick > tiempo)
    {
        tick = 0;
        return true;
    }
    return false;
}

void NAVE::pinta(BITMAP* buffer, int equis, int ye)
{
    masked_blit(imgNave, buffer, equis*anchoPersonaje, ye*altoPersonaje, x, y, anchoPersonaje, altoPersonaje);
}

void NAVE::mueve()
{
    if(key[KEY_LEFT] && x>=50) x -= 5;
    if(key[KEY_RIGHT] && x<=516) x += 5;
}

void NAVE::disparo(struct Balas disparos[], BITMAP* buffer)
{
    if(tipoNave)
        crear_bala(nDisp , maxDisp , disparos , x , y, dirBala);
        pintar_bala(nDisp , maxDisp , disparos , buffer , imgBala, anchoBala, altoBala);
        elimina_bala(nDisp , maxDisp , disparos , ANCHO , ALTO);
}

void NAVE::vidas(BITMAP* buffer)
{
    for(int i = 0; i < vida; i++)
    {
        masked_blit(imgNave, buffer, 0, 0, 20+i*30, 50, 30, 20);
    }
}

void tropaEnemigos(struct NAVE Enemigos[])
{
    int indice = -1;
    int tipoEnemigo = 0;
    for(int i=0; i < 5; i++)
    {
        tipoEnemigo++;
        if(tipoEnemigo == 4)
            tipoEnemigo = 1;
        for(int j=0; j < 11; j++)
        {
            indice++;
            Enemigos[indice].inicia("Recursos/enemigos1.bmp", "Recursos/Bala_enem1.bmp", 6, 12, 25, 20, 140+j*30, 130+i*25, 8, tipoEnemigo, 1, "Recursos/10.wav", "Recursos/11.wav");
        }
    }
}

void pintarEnemigos(struct NAVE Enemigos[], BITMAP* buffer, int mover)
{
    int indice = -1;
    for(int i=0; i < 5; i++)
    {
        for(int j=0; j < 11; j++)
        {
            indice++;
            if(Enemigos[indice].vida > 0)
            {
                Enemigos[indice].pinta(buffer,mover,Enemigos[indice].tipoNave-1);
            }
        }
    }
}

void jefeFinal(struct NAVE Jefe[])
{
    int indice = -1;
    int tipoEnemigo = 0;
    for(int i=0; i < 5; i++)
    {
        tipoEnemigo++;
        if(tipoEnemigo == 4)
            tipoEnemigo = 1;
        for(int j=0; j < 11; j++)
        {
            indice++;
            Jefe[indice].inicia("Recursos/jefe.bmp", "Recursos/BalaE1.bmp", 12, 12, 39, 15, 140+j*30, 130+i*25, 8, tipoEnemigo, 1, "Recursos/10.wav", "Recursos/11.wav");
        }
    }
}

void pintarJefe(struct NAVE Jefe[], BITMAP* buffer, int mover)
{
    int indice = -1;
    for(int i=0; i < 5; i++)
    {
        for(int j=0; j < 11; j++)
        {
            indice++;
            if(Jefe[indice].vida > 0)
            {
                Jefe[indice].pinta(buffer,mover,Jefe[indice].tipoNave-1);
            }
        }
    }
}

void explosionEnemigo(struct NAVE Enemigo, BITMAP* buffer, int& numEnem)
{
    play_sample(Enemigo.explo, 100, 150, 1000, 0);
    BITMAP* parche = create_bitmap(25,20);
    clear_to_color(parche, 0x000000);
    blit(parche, buffer, 0, 0, Enemigo.x, Enemigo.y, 25, 20);
    masked_blit(Enemigo.ExplosionEnemigo, buffer, 0, 0, Enemigo.x-10, Enemigo.y, 41, 34);
    numEnem--;
}

void explosionJefe(struct NAVE Jefe, BITMAP* buffer, int& numJefe)
{
    play_sample(Jefe.explo, 100, 150, 1000, 0);
    BITMAP* parche = create_bitmap(25,20);
    clear_to_color(parche, 0x000000);
    blit(parche, buffer, 0, 0, Jefe.x, Jefe.y, 25, 20);
    masked_blit(Jefe.ExplosionEnemigo, buffer, 0, 0, Jefe.x-10, Jefe.y, 41, 34);
    numJefe--;
}

void explosionNave(struct NAVE Nave, BITMAP* buffer, BITMAP* fondo)
{
    play_sample(Nave.explo, 100, 150, 1000, 0);
    BITMAP* parche = create_bitmap(30,20);
    clear_to_color(parche, 0x000000);
    for(int j = 0; j < 6; j++)
    {
        for(int i = 1; i <= 2; i++)
        {
            blit(parche, buffer, 0, 0, Nave.x, Nave.y, 30, 20);
            masked_blit(Nave.imgNave, buffer, i*30, 0, Nave.x, Nave.y, 30, 20);
            imprimirFondo(fondo, buffer);
            blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
            rest(30);
        }
    }
}

void crearBalaEnemigo(struct NAVE Enemigo[], int &raza)
{
    if(Enemigo[raza].nDisp == 0)
    {
        raza = rand()%55;
        while(Enemigo[raza].vida == 0)
            raza = rand()%55;
    }
}

void crearBalaJefe(struct NAVE Jefe[], int &raza)
{
    if(Jefe[raza].nDisp == 0)
    {
        raza = rand()%55;
        while(Jefe[raza].vida == 0)
            raza = rand()%55;
    }
}

void crearBalaNave(struct NAVE& Nave, struct Balas disparos[])
{
    if(key[KEY_SPACE] && Nave.temporizador(6))
    {
        if(crear_bala(Nave.nDisp, Nave.maxDisp, disparos, Nave.x, Nave.y, Nave.dirBala))
            play_sample(Nave.dispa, 100, 150, 1000, 0);
    }
}

void iniciarEscudo(struct escudo muralla[])
{
    char posMuro[3][22] = { "AEC AEC AEC AEC", "B D B D B D B D", };
    int cont = 0;
    for(int i = 0; i < 21; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            if(posMuro[j][i] != ' ')
            {
                muralla[cont].x = 155+i*20;
                muralla[cont].y = 450+j*15;
                muralla[cont].dan = 0;
                if(posMuro[j][i] == 'A')
                    muralla[cont].tipo = 0;
                if(posMuro[j][i] == 'B')
                    muralla[cont].tipo = 1;
                if(posMuro[j][i] == 'C')
                    muralla[cont].tipo = 2;
                if(posMuro[j][i] == 'D')
                    muralla[cont].tipo = 3;
                if(posMuro[j][i] == 'E')
                    muralla[cont].tipo = 4;
                cont++;
            }
        }
    }
}

void pintarEscudo(struct escudo mura[], BITMAP* imgEscudo, BITMAP* buffer)
{
    for(int i = 0; i < 20; i++)
    {
        if(mura[i].dan != 3)
        {
            masked_blit(imgEscudo, buffer, mura[i].dan*20, mura[i].tipo*16, mura[i].x, mura[i].y, 20, 16);
        }
    }
}

void vicder(BITMAP* derro, BITMAP* buffer)
{
    blit(derro,screen,0,0,0,0,600,600);
    rest(30);
}
