#include "disparos.h"
#include <allegro.h>
#include "personajes.h"

bool crear_bala(int& n_disparos, const int max_disparos, struct Balas disparos[], const int X, const int Y , const int dy)
{
    if(n_disparos < max_disparos-1)
    { // n -1 disparos permitidos
        n_disparos++;
        disparos[n_disparos].x  = X+11;
        disparos[n_disparos].y  = Y;
        disparos[n_disparos].dx = 0;
        disparos[n_disparos].dy = dy;
        return true;
    }
    return false;
}

void pintar_bala(int& n_disparos, const int max_disparos,struct Balas disparos[], BITMAP* buffer, BITMAP* bala, int ancho, int alto)
{
    if(n_disparos > 0 && n_disparos < max_disparos)
    {
        for(int cont = 1; cont <= n_disparos; cont++)
        {
            disparos[cont].x += disparos[cont].dx;
            disparos[cont].y += disparos[cont].dy;
            masked_blit( bala, buffer, 0, 0, disparos[cont].x, disparos[cont].y, ancho, alto);
        }
    }
}

void eliminar(struct Balas disparos[], int& n_disparos, int cont)
{
    Balas Btemp;
    Btemp = disparos[cont];
    disparos[cont] = disparos[n_disparos];
    disparos[n_disparos] = Btemp;
    n_disparos--;
    if ( n_disparos < 0 )
        n_disparos=0;
}

void elimina_bala(int& n_disparos, const int max_disparos,struct Balas disparos[], const int ANCHO, const int ALTO)
{

    if(n_disparos > 0 && n_disparos < max_disparos)
    {
        for(int cont = 1; cont <= n_disparos; cont++)
        {
            if(disparos[cont].y > ALTO || disparos[cont].y < 0 || disparos[cont].x > ANCHO|| disparos[cont].x < 0)
            {
                eliminar(disparos, n_disparos, cont);
            }
        }
    }
}

bool eliminarNave(struct NAVE& Nave, struct NAVE& Enemigo, struct Balas Bala[])
{
    if(Nave.nDisp > 0 && Nave.nDisp < Nave.maxDisp)
    {
        for(int cont = 1; cont <= Nave.nDisp; cont++)
        {
            if(choque(Enemigo.x, Enemigo.y, Enemigo.anchoPersonaje, Enemigo.altoPersonaje, Bala[cont].x, Bala[cont].y, Nave.anchoBala, Nave.altoBala) && Enemigo.vida > 0)
            {
                eliminar(Bala, Nave.nDisp, cont);
                Enemigo.vida --;
                return true;
            }
        }
    }
    return false;
}

bool choque(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    return((x1<x2 + w2) && (x2<x1 + w1) && (y1<y2 + h2) && (y2<y1 + h1));
}

void eliminarEscudo(struct NAVE &Nave, struct escudo es[], struct Balas bala[])
{
    if(Nave.nDisp > 0 && Nave.nDisp < Nave.maxDisp)
    {
        for(int cont = 1; cont <= Nave.nDisp; cont++)
        {
            for(int i = 0; i < 20; i++)
            {
                if(choque(es[i].x, es[i].y, 20, 16, bala[cont].x, bala[cont].y, Nave.anchoBala, Nave.altoBala) && es[i].dan < 3)
                {
                    eliminar(bala, Nave.nDisp, cont);
                    es[i].dan++;
                }
            }
        }
    }
}
